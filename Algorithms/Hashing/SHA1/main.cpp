#include <fmt/core.h>

#include "sha1.hpp"

int main() {
  auto hash = sha1<64>("Hello, world!");
  for (auto byte : hash) {
    fmt::print("{:02x}", byte);
  }
  fmt::print("\n");
  return 0;
}
