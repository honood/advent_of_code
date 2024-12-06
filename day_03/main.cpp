// https://adventofcode.com/2024/day/3
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <string>
#include <regex>
#include <cassert>
#include <iostream>
#include <cctype>

#include "../aoc.h"

[[maybe_unused]] int parse_input_data_with_regex() {
  std::string input{helper::read_file_as_string("input.txt")};

  int res = 0;
  std::regex pattern{R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))"};
  std::sregex_iterator it{input.cbegin(), input.cend(), pattern};
  std::sregex_iterator end{};
  bool skip = false;
  for (; it != end; ++it) {
    auto const& match = *it;
    if (match.empty()) {
      continue;
    }

    if (match[0] == "don't()") {
      skip = true;
    } else if (match[0] == "do()") {
      skip = false;
    } else if (!skip) {
      res += std::stoi(match[1]) * std::stoi(match[2]);
    }
  }

  return res;
}

int parse_input() {
  std::string input{helper::read_file_as_string("input.txt")};

  int res = 0;
  bool skip = false;
  size_t pos = 0;
  while (pos < input.size()) {
    if (skip && (input.size() - pos < 4 || input.compare(pos, 4, "do()") != 0)) {
      ++pos;
    } else if (input.compare(pos, 7, "don't()") == 0) {
      pos += 7;
      skip = true;
    } else if (input.compare(pos, 4, "do()") == 0) {
      pos += 4; // skip `do()`
      skip = false;
    } else if (input.compare(pos, 4, "mul(") == 0) {
      pos += 4; // skip `mul(`

      int x = 0;
      int digit_count = 0;
      while (pos < input.size() && std::isdigit(input[pos]) && digit_count < 3) {
        x = x * 10 + (input[pos] - '0');
        ++pos;
        ++digit_count;
      }

      if (digit_count == 0 || pos >= input.size() || input[pos] != ',') {
        continue;
      }

      ++pos; // skip `,`

      int y = 0;
      digit_count = 0;
      while (pos < input.size() && std::isdigit(input[pos]) && digit_count < 3) {
        y = y * 10 + (input[pos] - '0');
        ++pos;
        ++digit_count;
      }

      if (digit_count == 0 || pos >= input.size() || input[pos] != ')') {
        continue;
      }

      ++pos; // skip `)`

      if (!skip) {
        res += x * y;
      }
    } else {
      ++pos;
    }
  }

  return res;
}

int main() {
  int res = parse_input();
  assert(res == 75920122);
  std::cout << "What do you get if you add up all of the results of the multiplications? " << res << std::endl;
}
