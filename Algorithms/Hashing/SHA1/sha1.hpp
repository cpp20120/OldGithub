#ifndef SHA1_HPP
#define SHA1_HPP

#include <array>
#include <cstdint>
#include <string_view>

constexpr uint32_t left_rotate(uint32_t value, std::size_t count) {
  return (value << count) | (value >> (32 - count));
}

template <std::size_t N>
constexpr std::array<uint8_t, 20> sha1(std::string_view input) {
  constexpr std::array<uint32_t, 88> k{
      0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999,
      0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999,
      0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999,
      0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999,
      0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999, 0x5A827999,
      0x5A827999, 0x5A827999, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1,
      0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1,
      0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1,
      0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1, 0x6ED9EBA1,
      0x6ED9EBA1, 0x6ED9EBA1, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC,
      0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC,
      0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC, 0x8F1BBCDC,
      0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6,
      0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6,
      0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6, 0xCA62C1D6,
  };

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

  std::array<uint32_t, 5> h{0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476,
                            0xC3D2E1F0};

  for (std::size_t chunk_start = 0; chunk_start < padded_input.size();
       chunk_start += 64) {
    std::array<uint32_t, 80> w{};
    for (std::size_t i = 0; i < 16; ++i) {
      w[i] = (padded_input[chunk_start + i * 4 + 0] << 24) |
             (padded_input[chunk_start + i * 4 + 1] << 16) |
             (padded_input[chunk_start + i * 4 + 2] << 8) |
             (padded_input[chunk_start + i * 4 + 3]);
    }

    for (std::size_t i = 16; i < 80; ++i) {
      w[i] = left_rotate(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
    }

    uint32_t a = h[0];
    uint32_t b = h[1];
    uint32_t c = h[2];
    uint32_t d = h[3];
    uint32_t e = h[4];

    for (std::size_t i = 0; i < 80; ++i) {
      uint32_t f, k_t;
      if (i < 20) {
        f = (b & c) | (~b & d);
        k_t = k[i];
      } else if (i < 40) {
        f = b ^ c ^ d;
        k_t = k[i];
      } else if (i < 60) {
        f = (b & c) | (b & d) | (c & d);
        k_t = k[i];
      } else {
        f = b ^ c ^ d;
        k_t = k[i];
      }

      uint32_t temp = left_rotate(a, 5) + f + e + k_t + w[i];
      e = d;
      d = c;
      c = left_rotate(b, 30);
      b = a;
      a = temp;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
  }

  std::array<uint8_t, 20> result{};
  for (std::size_t i = 0; i < 5; ++i) {
    result[i * 4 + 0] = (h[i] >> 24) & 0xFF;
    result[i * 4 + 1] = (h[i] >> 16) & 0xFF;
    result[i * 4 + 2] = (h[i] >> 8) & 0xFF;
    result[i * 4 + 3] = h[i] & 0xFF;
  }

  return result;
}
#endif
