#pragma once

#include <sstream>
#include <string>

namespace util {
class Log {
 public:
  using Output = std::string;
  static void info(const Output &o);
  static void warn(const Output &o);
  static void debug(const Output &o);
  static void error(const Output &o);

  template <typename... Ts>
  static void info(const Ts &...os) {
    std::stringstream ss;
    ([&] { ss << os; }(), ...);
    info(ss.str());
  }
  template <typename... Ts>
  static void warn(const Ts &...os) {
    std::stringstream ss;
    ([&] { ss << os; }(), ...);
    warn(ss.str());
  }
  template <typename... Ts>
  static void error(const Ts &...os) {
    std::stringstream ss;
    ([&] { ss << os; }(), ...);
    error(ss.str());
  }
  template <typename... Ts>
  static void debug(const Ts &...os) {
    std::stringstream ss;
    ([&] { ss << os; }(), ...);
    debug(ss.str());
  }

 private:
  Log();
  ~Log() = default;

  static Log &getInstance() {
    static Log instance;
    return instance;
  }

  Log(const Log &) = delete;
  Log &operator=(const Log &) = delete;
  Log(Log &&) = delete;
  Log &operator=(Log &&) = delete;
};
}  // namespace util