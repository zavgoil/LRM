#pragma once

#include <config/db_option.hpp>
#include <memory>
#include <notification-client/notification-client-json.hpp>
#include <pqxx/pqxx>
#include <string>

/// @brief Класс менеджера БД, инкапсулирует взаимодействие с хранилищем,
/// предоставляя верхнеуровневые интерфейсы
class DbManager {
 public:
  DbManager(const DbOption& db_option);
  ~DbManager();

  /// @brief Добавление пользователя в БД. Исключения см. в db_exception.h
  /// @param login Логин пользователя
  /// @param password Пароль пользователя
  /// @return uuid пользователя
  std::string addUser(const std::string login, const std::string password);

  /// @brief Получение uuid пользователя в БД. Исключения см. в db_exception.h
  /// @param login Логин пользователя
  /// @param password Пароль пользователя
  /// @return uuid пользователя
  std::string getUuid(const std::string login, const std::string password);

  /// @brief Установить клиентов пользователю. Исключения см. в db_exception.h
  /// @param token uuid пользователя
  /// @param clients Список клиентов
  void setClients(const std::string& token,
                  const ::google::protobuf::RepeatedPtrField<
                      ::user_service::NotificationClient>& clients);

  /// @brief Получить клиентов пользователя. Исключения см. в db_exception.h
  /// @param token uuid пользователя
  /// @param clients Список клиентов
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
