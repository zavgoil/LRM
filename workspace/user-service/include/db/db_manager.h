#pragma once

#include <config/db_option.hpp>
#include <notification-clients/notification-clients.hpp>
#include <pqxx/pqxx>
#include <string>

#include "db_exception.h"

class DbManager {
 public:
  DbManager(const DbOption& db_option);
  ~DbManager();

  std::string addUser(const std::string login, const std::string password);
  std::string getUuid(const std::string login, const std::string password);

  void setClients(const std::string& token, const NotificationClients& clients);
  NotificationClients getClients(const std::string& token);

 private:
  pqxx::connection conn_;
  void prepareQuery(std::string table_name);

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
  //
  // clang-format on

  //  DROP TABLE IF EXISTS app."user";

  // CREATE TABLE IF NOT EXISTS app."user"
  // (
  //     uuid uuid NOT NULL,
  //     login character(255) COLLATE pg_catalog."default" NOT NULL,
  //     password character(255) COLLATE pg_catalog."default" NOT NULL,
  //     clients json DEFAULT '{}'::json,
  //     CONSTRAINT user_pkey PRIMARY KEY (uuid, login),
  //     CONSTRAINT user_login_key UNIQUE (login),
  //     CONSTRAINT user_uuid_key UNIQUE (uuid)
  // )

  // TABLESPACE pg_default;

  // ALTER TABLE IF EXISTS app."user"
  //     OWNER to root;

  void rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch) { return !std::isspace(ch); })
                .base(),
            s.end());
  }
};