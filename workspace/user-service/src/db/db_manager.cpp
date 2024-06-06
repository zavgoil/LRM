#include <db/db_manager.h>
#include <db/hash.h>

#include <stdexcept>
#include "db/db_exception.h"
#include "util/log.hpp"

DbManager::DbManager(const DbOption& db_option)
    : conn_{db_option.uri + "/" + db_option.name} {
  if (!conn_.is_open()) throw std::runtime_error{"Connection failed"};
  prepareQuery(db_option.schema + "." + db_option.user_table_name);
}

void DbManager::prepareQuery(std::string table_name) {
  conn_.prepare(
      "insert_user",
      "INSERT INTO " + table_name +
          " (uuid, login, password) VALUES (gen_random_uuid(), $1, $2);");

  conn_.prepare("get_uuid", "SELECT * FROM " + table_name + " WHERE login=$1");

  conn_.prepare("set_clients", "UPDATE " + table_name +
                                   " SET clients = $2::json WHERE uuid=$1;");

  conn_.prepare("get_clients",
                "SELECT clients FROM " + table_name + " WHERE uuid=$1;");
}

DbManager::~DbManager() {
  if (conn_.is_open()) conn_.close();
}

std::string DbManager::addUser(const std::string login,
                               const std::string password) {
  if (!conn_.is_open()) {
    throw std::runtime_error{"Connection failed"};
  }
  pqxx::work query(conn_);

  try {
    // TODO: вынести шифрование на уровень клиента
    auto query_result =
        query.exec_prepared0("insert_user", login, Hash::sha256(password));
    query.commit();
  } catch (std::runtime_error const& e) {
    if (std::string(e.what()).find("user_login_key") != std::string::npos)
      throw LoginAlreadyExists{e.what()};
    if (std::string(e.what()).find("user_uuid_key") != std::string::npos)
      throw TokenAlreadyExists{e.what()};
    throw;
  }

  return getUuid(login, password);
}

std::string DbManager::getUuid(const std::string login,
                               const std::string password) {
  if (!conn_.is_open()) {
    throw std::runtime_error{"Connection failed"};
  }

  pqxx::work query(conn_);
  pqxx::row query_result;
  try {
    query_result = query.exec_prepared1("get_uuid", login);
    query.commit();
  } catch (pqxx::unexpected_rows const& e) {
    throw UserNotFound{"User not found"};
  }

  if (query_result.empty()) throw UserNotFound{"User not found"};

  auto query_password =
      query_result.at(query_result.column_number("password")).as<std::string>();
  rtrim(query_password);

  // TODO: вынести шифрование на уровень клиента
  if (query_password != Hash::sha256(password))
    throw WrongPassword{"Wrong password"};

  return query_result.at(query_result.column_number("uuid")).as<std::string>();
}

void DbManager::setClients(const std::string& token,
                           const ::google::protobuf::RepeatedPtrField<::user_service::NotificationClient>& clients) {
  if (!conn_.is_open()) {
    throw std::runtime_error{"Connection failed"};
  }

  pqxx::work query(conn_);
  pqxx::result query_result;

  json clients_json;
  to_json(clients_json, clients);

  try {

    query_result =
        query.exec_prepared0("set_clients", token, clients_json.is_null() ? "{}" : clients_json.dump());
    query.commit();
  } catch (std::runtime_error& e) {
    throw UserNotFound{"User not found"};
  }
}

void DbManager::getClients(const std::string& token, ::google::protobuf::RepeatedPtrField<::user_service::NotificationClient>* clients) {
  if (!conn_.is_open()) {
    throw std::runtime_error{"Connection failed"};
  }

  pqxx::work query(conn_);
  pqxx::row query_result;
//  auto clients = new ::google::protobuf::RepeatedPtrField<::user_service::NotificationClient>{};

  try {
    query_result = query.exec_prepared1("get_clients", token);
    query.commit();
  } catch (std::runtime_error& e) {
    throw UserNotFound{"User not found"};
  }

  if (query_result.empty()) throw UserNotFound{"User not found"};

  auto query_clients =
      query_result.at(query_result.column_number("clients")).as<std::string>();

  json clients_json = json::parse(query_clients);
  from_json(clients_json, *clients);
}
