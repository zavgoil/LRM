#pragma once

#include <config/db_option.hpp>
#include <memory>
#include <notification-client/notification-client-json.hpp>
#include <pqxx/pqxx>
#include <string>

class DbManager {
 public:
  DbManager(const DbOption& db_option);
  ~DbManager();

  std::string addUser(const std::string login, const std::string password);
  std::string getUuid(const std::string login, const std::string password);

  void setClients(const std::string& token,
                  const ::google::protobuf::RepeatedPtrField<
                      ::user_service::NotificationClient>& clients);
  void getClients(
      const std::string& token,
      ::google::protobuf::RepeatedPtrField<::user_service::NotificationClient>*
          clients);

 private:
  std::unique_ptr<pqxx::connection> conn_;
  void prepareQuery(std::string table_name);

  void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
  }
};
