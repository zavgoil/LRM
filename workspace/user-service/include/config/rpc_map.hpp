#pragma once

#include <project-util/format/yaml.hpp>
#include <project-util/format/yaml_macro.hpp>
#include <string>

struct RpcAddress : public YamlFormat<RpcAddress> {
  std::string uri = "";
  int port = 0;
};
DEFINE_YAML(RpcAddress, uri, port)

struct RpcMap : public YamlFormat<RpcMap> {
  RpcAddress user_service;
};
DEFINE_YAML(RpcMap, user_service)
