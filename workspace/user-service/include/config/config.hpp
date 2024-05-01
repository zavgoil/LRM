#pragma once

#include "db_option.hpp"
#include "rpc_map.hpp"
struct Config {
  RpcMap rpc_map;
  DbOption db_option;
};
