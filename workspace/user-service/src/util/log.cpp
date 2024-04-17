#include "util/log.hpp"

#include <iostream>

using namespace util;
Log::Log() {
#ifndef NDEBUG
#endif
}

void Log::info(const Output& o) { std::cout << o << std::endl; }
void Log::warn(const Output& o) { std::cout << o << std::endl; }
void Log::debug(const Output& o) { std::cout << o << std::endl; }
void Log::error(const Output& o) { std::cout << o << std::endl; }
