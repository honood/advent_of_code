// https://adventofcode.com/2024/day/17
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <iostream>

using u64 = uint64_t;

void solve_part1() {
  std::vector<u64> const prog{2, 4, 1, 2, 7, 5, 4, 5, 1, 3, 5, 5, 0, 3, 3, 0};
  u64 ar = 64751475;
  u64 br = 0;
  u64 cr = 0;
  u64 ip = 0;

  auto combo_operand = [&](u64 operand) {
    if (operand <= 3u) { return operand; }
    if (operand == 4u) { return ar; }
    if (operand == 5u) { return br; }
    if (operand == 6u) { return cr; }
    throw std::invalid_argument("Invalid operand: " + std::to_string(operand));
  };

  std::vector<u64> res{};
  std::unordered_map<u64, std::function<void(u64)>> opcode2insts{
    {0u, [&](u64 operand) { ar >>= combo_operand(operand); }},
    {1u, [&](u64 operand) { br ^= operand; }},
    {2u, [&](u64 operand) { br = combo_operand(operand) & 7; }},
    {3u, [&](u64 operand) { if (ar != 0) { ip = operand; } }},
    {4u, [&](u64 operand) { br ^= cr; }},
    {5u, [&](u64 operand) { res.emplace_back(combo_operand(operand) & 7); }},
    {6u, [&](u64 operand) { br = ar >> combo_operand(operand); }},
    {7u, [&](u64 operand) { cr = ar >> combo_operand(operand); }},
  };

  while (ip < prog.size() - 1) { opcode2insts[prog[ip++]](prog[ip++]); }

  // assert((res == std::vector<u64>{3, 1, 4, 3, 1, 7, 1, 6, 3}));
  std::cout << "Part 1: What do you get if you use commas to join the values it output into a single string? ";
  for (int i = 0; i < res.size(); ++i) {
    std::cout << res[i] << (i == res.size() - 1 ? '\n' : ',');
  }
}

void solve_part2() {
  std::vector<u64> const prog{2, 4, 1, 2, 7, 5, 4, 5, 1, 3, 5, 5, 0, 3, 3, 0};
  // For the input `prog`, the following instructions will be executed one by one:
  //
  // 1) 2,4: br = ar & 7
  // 2) 1,2: br = br ^ 2
  // 3) 7,5: cr = ar >> br
  // 4) 4,5: br = br ^ cr
  // 5) 1,3: br = br ^ 3
  // 6) 5,5: OUTPUT br & 7
  // 7) 0,3: ar = ar >> 3
  // 8) 3,0: if ar == 0 then EXIT else GOTO prog[0]
  //
  // which are equivalent to:
  //
  // 1) 5:5: OUTPUT ((ar & 7 ^ 2) ^ (ar >> (ar & 7 ^ 2)) ^ 3) & 7
  // 2) 0,3: ar = ar >> 3
  // 3) 3,0: if ar == 0 then EXIT else GOTO [0]

  u64 lowest_init_ar = -1;

  auto output = [](u64 ar) { return ((ar & 7 ^ 2) ^ (ar >> (ar & 7 ^ 2)) ^ 3) & 7; };

  std::function<void(int, u64)> backtrack = [&](int index, u64 ar) {
    if (index == -1) {
      lowest_init_ar = std::min(lowest_init_ar, ar);
      return;
    }

    for (u64 delta = 0b000; delta <= 0b111; ++delta) {
      // Register A must be non-zero before outputting the final value. Otherwise,
      // the last jump instruction will fail to return to the start, and the final
      // value will not be output.
      if (index == prog.size() - 1 && delta == 0b000) { continue; }

      u64 ar_before_output = (ar << 3) + delta;
      if (prog[index] == output(ar_before_output)) {
        backtrack(index - 1, ar_before_output);
      }
    }
  };

  backtrack(prog.size() - 1, 0);
  assert(37221270076916 == lowest_init_ar);
  std::cout << "Part 2: What is the lowest positive initial value for register A that causes the program to output a copy of itself? " << lowest_init_ar << '\n';
}

int main() {
  solve_part1();
  solve_part2();
}
