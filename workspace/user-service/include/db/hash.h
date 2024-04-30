#pragma once

#include <openssl/sha.h>

#include <iomanip>
#include <sstream>
#include <string>

class Hash {
 public:
  static std::string sha256(const std::string& str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.length());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
      ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
  }

 private:
  Hash() = default;
  Hash(Hash const&) = delete;
  Hash(Hash&&) = delete;
  Hash& operator=(Hash const&) = delete;
  Hash& operator=(Hash&&) = delete;
};