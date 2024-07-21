#pragma once

#include "for_each_macro.hpp"

// Вспомогательные макросы для сериализаторов/десериализаторов для YAML

#define YAML_FORMAT_TO(field) yaml_node[#field] = obj.field;
#define YAML_FORMAT_FROM(field) \
  obj.field = yaml_node[#field].as<decltype(obj.field)>();

#define DEFINE_YAML(Type, ...)                             \
  template <>                                              \
  struct YAML::convert<Type> {                             \
    static Node encode(const Type& obj) {                  \
      Node yaml_node;                                      \
      FOR_EACH(YAML_FORMAT_TO, __VA_ARGS__)                \
      return yaml_node;                                    \
    }                                                      \
    static bool decode(const Node& yaml_node, Type& obj) { \
      FOR_EACH(YAML_FORMAT_FROM, __VA_ARGS__)              \
      return true;                                         \
    }                                                      \
  };
