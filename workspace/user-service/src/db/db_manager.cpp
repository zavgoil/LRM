#include <db/db_manager.h>
#include <db/hash.h>

#include <stdexcept>

#include "util/log.hpp"

DbManager::DbManager() : conn_{DB_CONNECT_OPTIONS} {
  if (!conn_.is_open()) throw std::runtime_error{"Connection failed"};

  conn_.prepare(
      "insert_user",
      "INSERT INTO " + DB_USER_TABLE +
          " (uuid, login, password) VALUES (gen_random_uuid(), $1, $2);");

  conn_.prepare("get_uuid",
                "SELECT * FROM " + DB_USER_TABLE + " WHERE login=$1");
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
  } catch (pqxx::unexpected_rows const& e) {
    throw UserNotFound{"User not found"};
  }

  query.commit();

  if (query_result.empty()) throw UserNotFound{"User not found"};

  auto query_password =
      query_result.at(query_result.column_number("password")).as<std::string>();

  // TODO: вынести шифрование на уровень клиента
  if (query_password != Hash::sha256(password))
    throw WrongPassword{"Wrong password"};

  return query_result.at(query_result.column_number("uuid")).as<std::string>();
}