#pragma once

#include <stdexcept>

class LoginAlreadyExists : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

class TokenAlreadyExists : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

class UserNotFound : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};

class WrongPassword : public std::runtime_error {
 public:
  using std::runtime_error::runtime_error;
};