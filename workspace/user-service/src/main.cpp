#include "user-service/user-service.hpp"

int main(int argc, char const *argv[]) {
  UserService user_service{};
  return user_service.run(argc, argv);
}
