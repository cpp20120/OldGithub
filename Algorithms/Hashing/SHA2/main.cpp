#include <fmt/core.h>

#include "sha2.hpp"

int main() {
  auto hash = sha256::sha256<64>("Hello, world!");
  for (auto byte : hash) {
    fmt::print("{:02x}", byte);
  }
  fmt::print("\n");
  return 0;
}
