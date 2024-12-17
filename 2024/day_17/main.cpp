// https://adventofcode.com/2024/day/17
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <vector>
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <cassert>

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

  while (ip < prog.size() - 1) {
    opcode2insts[prog[ip++]](prog[ip++]);
  }

  for (int i = 0; i < res.size(); ++i) {
    if (i > 0) { std::cout << ','; }
    std::cout << res[i];
  }
  std::cout << '\n';
  assert((res == std::vector<u64>{3,1,4,3,1,7,1,6,3}));
}

int main() {
  solve_part1();
}
