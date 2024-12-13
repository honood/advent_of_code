// https://adventofcode.com/2024/day/7
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <cstdint>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <functional>
#include <cassert>
#include <cmath>
#include <iostream>

#include "../aoc.h"

using u64 = uint64_t;

std::vector<std::pair<u64, std::vector<u64>>> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};
  std::istringstream iss{};

  std::vector<std::pair<u64, std::vector<u64>>> res{};

  std::string line{};
  while (std::getline(ifs, line)) {
    auto colon_pos = line.find(':');
    u64 test_val = std::stol(line.substr(0, colon_pos));

    iss.str(line.substr(colon_pos + 1));
    iss.clear();
    u64 operand = 0;
    std::vector<u64> operands{};
    while (iss >> operand) {
      operands.emplace_back(operand);
    }

    res.emplace_back(test_val, std::move(operands));
  }

  return res;
}

u64 concat_nums(u64 high, u64 low) {
  if (high == 0) { return low; }
  if (low == 0) { return high * 10; }
  
  u64 temp = low;
  int low_digits = 0;
  do {
    ++low_digits;
    temp /= 10;
  } while (temp > 0);
  
  while (low_digits-- > 0) { high *= 10; }
  
  return high + low;
};

std::vector<std::string> gen_all_op_seq(int const seq_len, bool for_part2 = false) {
  std::vector<std::string> res{};
  res.reserve(std::pow(for_part2 ? 3 : 2, seq_len));
  std::string curr{};

  std::function<void()> backtrack = [&] {
    if (curr.size() == seq_len) {
      res.emplace_back(curr);
      return;
    }

    curr.push_back('+');
    backtrack();
    curr.pop_back();

    curr.push_back('*');
    backtrack();
    curr.pop_back();

    if (for_part2) {
      curr.push_back('|');
      backtrack();
      curr.pop_back();
    }
  };

  backtrack();

  return res;
}

u64 calc_total_calibration(std::vector<std::pair<u64, std::vector<u64>>> const& input_data, bool for_part2 = false) {
  u64 sum = 0;

  for (auto const& [test_val, operands] : input_data) {
    bool found = false;
    for (auto const& op_seq : gen_all_op_seq(operands.size() - 1, for_part2)) {
      u64 temp = operands[0];
      for (int i = 1; i < operands.size(); ++i) {
        switch (op_seq[i - 1]) {
          case '+': temp += operands[i]; break;
          case '*': temp *= operands[i]; break;
          case '|': temp = concat_nums(temp, operands[i]); break;
          default: assert(false);
        }
      }

      if (temp == test_val) {
        found = true;
        break;
      }
    }

    if (found) {
      sum += test_val;
    }
  }

  return sum;
}

int main() {
  auto input_data = parse_input();

  u64 part1_total_calibration = calc_total_calibration(input_data);
  assert(2501605301465 == part1_total_calibration);
  std::cout << "Part 1: What is their total calibration result? " << part1_total_calibration << '\n';

  u64 part2_total_calibration = calc_total_calibration(input_data, true);
  assert(44841372855953 == part2_total_calibration);
  std::cout << "Part 2: What is their total calibration result? " << part2_total_calibration << '\n';
}
