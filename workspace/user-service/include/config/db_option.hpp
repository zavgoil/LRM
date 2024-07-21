#pragma once

#include <project-util/format/yaml.hpp>
#include <project-util/format/yaml_macro.hpp>
#include <string>

struct DbOption : public YamlFormat<DbOption> {
  std::string db_name = "";
  std::string user = "";
  std::string password = "";
  std::string host = "";
  int port = 0;
  std::string user_table_name = "";
};
DEFINE_YAML(DbOption, db_name, user, password, host, port, user_table_name)
