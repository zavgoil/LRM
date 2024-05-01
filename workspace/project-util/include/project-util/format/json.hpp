#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template <typename T>
class JsonFormat {
 public:
  static inline std::string to_json(const T& obj) {
    json json_data = obj;
    return json_data.dump();
  }
  static inline void from_json(T& obj, const std::string& json_str) {
    json json_data = json::parse(json_str);
    obj = json_data.get<T>();
  }
  static inline void to_json_file(const T& obj, const std::string& file_path) {
    std::ofstream file(file_path);
    json json_data = obj;
    file << json_data.dump(4);
    file.close();
  }
  static inline void from_json_file(T& obj, const std::string& file_path) {
    std::ifstream file(file_path);
    json json_data = json::parse(file);
    file.close();
    obj = json_data.get<T>();
  }

  virtual ~JsonFormat() = default;
  inline std::string to_json() const {
    return to_json(dynamic_cast<const T&>(*this));
  }
  inline void from_json(const std::string& json) {
    return from_json(dynamic_cast<T&>(*this), json);
  }
  inline void to_json_file(const std::string& file_path) const {
    return to_json_file(dynamic_cast<const T&>(*this), file_path);
  }
  inline void from_json_file(const std::string& file_path) {
    return from_json_file(dynamic_cast<T&>(*this), file_path);
  }
};