#pragma once

#include <functional>

class Guard {
 public:
  Guard(std::function<void()> fn) : fn_(fn) {}
  ~Guard() { fn_(); };

 private:
  std::function<void()> fn_;
};