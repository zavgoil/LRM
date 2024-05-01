#pragma once

#include <project-util/format/yaml.hpp>
#include <project-util/format/yaml_macro.hpp>
#include <string>

#ifndef DB_OPTION_PATH
#define DB_OPTION_PATH ""
#endif

struct DbOption : public YamlFormat<DbOption> {
  std::string name = "";
  std::string uri = "";
  std::string schema = "";
  std::string user_table_name = "";
};
DEFINE_YAML(DbOption, name, uri, schema, user_table_name)
