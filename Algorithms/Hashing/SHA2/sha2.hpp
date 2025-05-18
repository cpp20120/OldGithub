#ifndef SHA2_HPP
#define SHA2_HPP

#include <fmt/core.h>

#include <array>
#include <cstdint>
#include <string_view>

namespace sha256 {

constexpr uint32_t right_rotate(uint32_t value, std::size_t count) {
  return (value >> count) | (value << (32 - count));
}

template <std::size_t N>
constexpr std::array<uint8_t, 32> sha256(std::string_view input) {
  constexpr std::array<uint32_t, 64> k{
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
      0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
      0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
      0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
      0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
      0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

  auto preprocess = [](std::string_view input) {
    constexpr std::size_t chunk_size = 64;
    std::array<uint8_t, chunk_size*((N + chunk_size) / chunk_size)>
        padded_input{};
    std::copy(input.begin(), input.end(), padded_input.begin());
    padded_input[input.size()] = 0x80;

    uint64_t bit_length = input.size() * 8;
    for (std::size_t i = 0; i < 8; ++i) {
      padded_input[padded_input.size() - 1 - i] =
          (bit_length >> (i * 8)) & 0xFF;
    }

    return padded_input;
  };

  auto padded_input = preprocess(input);

  std::array<uint32_t, 8> h{0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                            0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  for (std::size_t chunk_start = 0; chunk_start < padded_input.size();
       chunk_start += 64) {
    std::array<uint32_t, 64> w{};
    for (std::size_t i = 0; i < 16; ++i) {
      w[i] = (padded_input[chunk_start + i * 4 + 0] << 24) |
             (padded_input[chunk_start + i * 4 + 1] << 16) |
             (padded_input[chunk_start + i * 4 + 2] << 8) |
             (padded_input[chunk_start + i * 4 + 3]);
    }

    for (std::size_t i = 16; i < 64; ++i) {
      uint32_t s0 = right_rotate(w[i - 15], 7) ^ right_rotate(w[i - 15], 18) ^
                    (w[i - 15] >> 3);
      uint32_t s1 = right_rotate(w[i - 2], 17) ^ right_rotate(w[i - 2], 19) ^
                    (w[i - 2] >> 10);
      w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    uint32_t a = h[0];
    uint32_t b = h[1];
    uint32_t c = h[2];
    uint32_t d = h[3];
    uint32_t e = h[4];
    uint32_t f = h[5];
    uint32_t g = h[6];
    uint32_t h0 = h[7];

    for (std::size_t i = 0; i < 64; ++i) {
      uint32_t S1 =
          right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25);
      uint32_t ch = (e & f) ^ (~e & g);
      uint32_t temp1 = h0 + S1 + ch + k[i] + w[i];
      uint32_t S0 =
          right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22);
      uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
      uint32_t temp2 = S0 + maj;

      h0 = g;
      g = f;
      f = e;
      e = d + temp1;
      d = c;
      c = b;
      b = a;
      a = temp1 + temp2;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += h0;
  }

  std::array<uint8_t, 32> result{};
  for (std::size_t i = 0; i < 8; ++i) {
    result[i * 4 + 0] = (h[i] >> 24) & 0xFF;
    result[i * 4 + 1] = (h[i] >> 16) & 0xFF;
    result[i * 4 + 2] = (h[i] >> 8) & 0xFF;
    result[i * 4 + 3] = h[i] & 0xFF;
  }

  return result;
}
}  // namespace sha256
#endif
