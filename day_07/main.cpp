// https://adventofcode.com/2024/day/7
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <functional>
#include <cassert>
#include <iostream>

#include "../aoc.h"

std::vector<std::pair<long, std::vector<long>>> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};
  std::istringstream iss{};

  std::vector<std::pair<long, std::vector<long>>> res{};

  std::string line{};
  while (std::getline(ifs, line)) {
    auto colon_pos = line.find(':');
    long test_val = std::stol(line.substr(0, colon_pos));

    iss.str(line.substr(colon_pos + 1));
    iss.clear();
    long operand = 0;
    std::vector<long> operands{};
    while (iss >> operand) {
      operands.emplace_back(operand);
    }

    res.emplace_back(test_val, std::move(operands));
  }

  return res;
}

using op_t = std::function<long(long, long)>;

std::vector<std::vector<op_t>> gen_all_op_seq(int const seq_len) {
  std::vector<std::vector<op_t>> res{};
  res.reserve(1 << seq_len);
  std::vector<op_t> curr{};

  std::function<void()> backtrack = [&] {
    if (curr.size() == seq_len) {
      res.emplace_back(curr);
      return;
    }

    curr.emplace_back(std::plus<long>{});
    backtrack();
    curr.pop_back();

    curr.emplace_back(std::multiplies<long>{});
    backtrack();
    curr.pop_back();
  };

  backtrack();

  return res;
}

long calc_part1_total_calibration(std::vector<std::pair<long, std::vector<long>>> const& input_data) {
  long sum = 0;

  for (auto const& [test_val, operands] : input_data) {
    bool found = false;
    for (auto const& op_seq : gen_all_op_seq(operands.size() - 1)) {
      long temp = operands[0];
      for (int i = 1; i < operands.size(); ++i) {
        temp = op_seq[i - 1](temp, operands[i]);
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

  long part1_total_calibration = calc_part1_total_calibration(input_data);
  assert(2501605301465 == part1_total_calibration);
  std::cout << "Part 1: What is their total calibration result? " << part1_total_calibration << '\n';
}
