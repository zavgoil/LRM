#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template <typename T>
class JsonFormat {
 public:
  /// @brief Преобразование объекта в json строку
  /// @param obj Шаблонная структура
  /// @return json строка
  static inline std::string to_json(const T& obj) {
    json json_data = obj;
    return json_data.dump();
  }

  /// @brief Преобразование json строки в структуру
  /// @param obj Шаблонная структура
  /// @param json_str json строка
  static inline void from_json(T& obj, const std::string& json_str) {
    json json_data = json::parse(json_str);
    obj = json_data.get<T>();
  }

  /// @brief Запись объекта в файл в формате json
  /// @param obj Шаблонная структура
  /// @param file_path путь к файлу
  static inline void to_json_file(const T& obj, const std::string& file_path) {
    std::ofstream file(file_path);
    json json_data = obj;
    file << json_data.dump(4);
    file.close();
  }

  /// @brief Чтение объекта из файла в формате json
  /// @param obj Шаблонная структура
  /// @param file_path путь к файлу
  static inline void from_json_file(T& obj, const std::string& file_path) {
    std::ifstream file(file_path);
    json json_data = json::parse(file);
    file.close();
    obj = json_data.get<T>();
  }

  virtual ~JsonFormat() = default;

  /// @brief Получить json строку
  inline std::string to_json() const {
    return to_json(dynamic_cast<const T&>(*this));
  }

  /// @brief Считать поля из json строки
  inline void from_json(const std::string& json) {
    return from_json(dynamic_cast<T&>(*this), json);
  }

  /// @brief Записать в формате json в файл
  inline void to_json_file(const std::string& file_path) const {
    return to_json_file(dynamic_cast<const T&>(*this), file_path);
  }

  /// @brief Считать поля из json файла
  inline void from_json_file(const std::string& file_path) {
    return from_json_file(dynamic_cast<T&>(*this), file_path);
  }
};