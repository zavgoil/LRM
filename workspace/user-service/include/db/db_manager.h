#pragma once
#include <pqxx/pqxx>
#include <string>

#include "db_exception.h"

class DbManager {
 public:
  DbManager();
  ~DbManager();

  std::string addUser(const std::string login, const std::string password);
  std::string getUuid(const std::string login, const std::string password);

 private:
  pqxx::connection conn_;

  inline const static std::string DB_NAME = "danger-signal";
  inline const static std::string DB_CONNECT_OPTIONS =
      "postgresql://root:root@172.21.0.10/" + DB_NAME;
  inline const static std::string DB_SCHEMA = "app";
  inline const static std::string DB_USER_TABLE = DB_SCHEMA + ".user";
  // Струтура БД:

  // clang-format off
  //                                                       Table "app.user"
  //   Column  |          Type          | Collation | Nullable | Default | Storage  | Compression | Stats target | Description 
  // ----------+------------------------+-----------+----------+---------+----------+-------------+--------------+-------------
  //  uuid     | uuid                   |           | not null |         | plain    |             |              | 
  //  login    | character varying(255) |           | not null |         | extended |             |              | 
  //  password | character varying(255) |           | not null |         | extended |             |              | 
  // Indexes:
  //     "user_pkey" PRIMARY KEY, btree (uuid, login)
  //     "user_login_key" UNIQUE CONSTRAINT, btree (login)
  //     "user_uuid_key" UNIQUE CONSTRAINT, btree (uuid)
  // clang-format on
};