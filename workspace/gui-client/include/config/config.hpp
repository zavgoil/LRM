#pragma once

#include "rpc_map.hpp"

struct Config {
  RpcMap rpc_map;

  void read(int argc, char *argv[]) {
    static auto getEnv = [](const std::string &env_name) {
      const char *result = std::getenv(env_name.c_str());
      if (!result)
        throw std::runtime_error("Config::read: " + env_name +
                                 " env not found");
      return result;
    };
    rpc_map.from_yaml_file(getEnv("RPC_MAP_PATH"));
  }
};
