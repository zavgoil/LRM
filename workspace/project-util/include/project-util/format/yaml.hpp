#pragma once

#include <yaml-cpp/yaml.h>

#include <fstream>

template <typename T>
class YamlFormat {
 public:
  static inline std::string to_yaml(const T& obj) {
    YAML::Emitter emitter;
    emitter << YAML::Node(obj);
    return emitter.c_str();
  }
  static inline void from_yaml(T& obj, const std::string& yaml) {
    YAML::Node node = YAML::Load(yaml);
    YAML::convert<T>::decode(node, obj);
  }
  static inline void to_yaml_file(const T& obj, const std::string& file_path) {
    std::ofstream fout(file_path);
    fout << to_yaml(obj);
    fout.close();
  }
  static inline void from_yaml_file(T& obj, const std::string& file_path) {
    YAML::Node node = YAML::LoadFile(file_path);
    YAML::convert<T>::decode(node, obj);
  }

  virtual ~YamlFormat() = default;
  inline std::string to_yaml() {
    return to_yaml(dynamic_cast<const T&>(*this));
  }
  inline void from_yaml(const std::string& yaml) {
    return from_yaml(dynamic_cast<T&>(*this), yaml);
  }
  inline void to_yaml_file(const std::string& file_path) {
    return to_yaml_file(dynamic_cast<const T&>(*this), file_path);
  }
  inline void from_yaml_file(const std::string& file_path) {
    return from_yaml_file(dynamic_cast<T&>(*this), file_path);
  }
};