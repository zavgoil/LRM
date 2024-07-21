#pragma once

#include <yaml-cpp/yaml.h>

#include <fstream>

template <typename T>
class YamlFormat {
 public:
  /// @brief Преобразование объекта в yaml строку
  /// @param obj Шаблонная структура
  /// @return yaml строка
  static inline std::string to_yaml(const T& obj) {
    YAML::Emitter emitter;
    emitter << YAML::Node(obj);
    return emitter.c_str();
  }

  /// @brief Преобразование yaml строки в структуру
  /// @param obj Шаблонная структура
  /// @param yaml yaml строка
  static inline void from_yaml(T& obj, const std::string& yaml) {
    YAML::Node node = YAML::Load(yaml);
    YAML::convert<T>::decode(node, obj);
  }

  /// @brief Запись объекта в файл в формате yaml
  /// @param obj Шаблонная структура
  /// @param file_path путь к файлу
  static inline void to_yaml_file(const T& obj, const std::string& file_path) {
    std::ofstream fout(file_path);
    fout << to_yaml(obj);
    fout.close();
  }

  /// @brief Чтение объекта из файла в формате yaml
  /// @param obj Шаблонная структура
  /// @param file_path путь к файлу
  static inline void from_yaml_file(T& obj, const std::string& file_path) {
    YAML::Node node = YAML::LoadFile(file_path);
    YAML::convert<T>::decode(node, obj);
  }

  virtual ~YamlFormat() = default;

  /// @brief Получить yaml строку
  inline std::string to_yaml() {
    return to_yaml(dynamic_cast<const T&>(*this));
  }

  /// @brief Запись объекта в файл в формате yaml
  inline void from_yaml(const std::string& yaml) {
    return from_yaml(dynamic_cast<T&>(*this), yaml);
  }

  /// @brief Запись объекта в файл в формате yaml
  inline void to_yaml_file(const std::string& file_path) {
    return to_yaml_file(dynamic_cast<const T&>(*this), file_path);
  }

  /// @brief Запись объекта в файл в формате yaml
  inline void from_yaml_file(const std::string& file_path) {
    return from_yaml_file(dynamic_cast<T&>(*this), file_path);
  }
};