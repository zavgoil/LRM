#pragma once

#include "rpc_map.hpp"

struct Config {
  RpcMap rpc_map;

  void read(int argc, char *argv[]) {
    rpc_map.from_yaml_file(RPC_MAP_PATH);
  }
};
