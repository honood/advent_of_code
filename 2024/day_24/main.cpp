// https://adventofcode.com/2024/day/24
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <fstream>
#include <string>
#include <unordered_map>
#include <regex>
#include <tuple>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstdint>
#include <cctype>
#include <cassert>
#include <iostream>

#include "../aoc.h"

auto parse_input() {
  std::regex const sec1_pat(R"((\w+)\s*:\s*(0|1))");
  std::regex const sec2_pat(R"((\w+)\s+(AND|OR|XOR)\s+(\w+)\s*->\s*(\w+))");

  std::ifstream ifs(helper::read_file_as_stream("input.txt"));
  std::string line{};
  std::smatch match{};

  std::unordered_map<std::string, int> wires{};
  std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> gates{};
  while (std::getline(ifs, line)) {
    if (line.empty()) { continue; }
    if (std::regex_match(line, match, sec1_pat)) {
      wires.emplace(match[1], std::stoi(match[2]));
    } else if (std::regex_match(line, match, sec2_pat)) {
      gates.emplace(match[4], std::make_tuple(match[2], match[1], match[3]));
    }
  }

  return std::make_pair(wires, gates);
}

int calc_wire_val(std::string const& wire_name,
                  std::unordered_map<std::string, int>& wires,
                  std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> const& gates) {
  if (wires.contains(wire_name)) {
    return wires.at(wire_name);
  }

  auto const& [opcode, lhs, rhs] = gates.at(wire_name);
  if (!wires.contains(lhs)) {
    wires.emplace(lhs, calc_wire_val(lhs, wires, gates));
  }
  if (!wires.contains(rhs)) {
    wires.emplace(rhs, calc_wire_val(rhs, wires, gates));
  }

  int val;
  if (opcode == "AND") {
    val = wires[lhs] & wires[rhs];
  } else if (opcode == "OR") {
    val = wires[lhs] | wires[rhs];
  } else if (opcode == "XOR") {
    val = wires[lhs] ^ wires[rhs];
  } else {
    throw std::runtime_error("Unknown opcode: " + opcode);
  }
  wires[wire_name] = val;
  return val;
}

void solve_part1(std::unordered_map<std::string, int> wires,
                 std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> const& gates) {
  std::vector<std::pair<std::string, int>> z_wires{};
  for (auto const& [out, _] : gates) {
    if (out.size() >= 2 && out[0] == 'z' && std::isdigit(out[1])) {
      z_wires.emplace_back(out, -1);
    }
  }
  std::sort(z_wires.begin(), z_wires.end(), [](auto const& a, auto const& b) {
    return a.first < b.first;
  });

  for (auto& [name, val] : z_wires) {
    val = calc_wire_val(name, wires, gates);
  }

  uint64_t dec_z = std::reduce(z_wires.crbegin(), z_wires.crend(), uint64_t{0}, [](uint64_t acc, auto const& wire) {
    return acc * 2 + wire.second;
  });

  assert(53325321422566 == dec_z);
  std::cout << "Part 1: What decimal number does it output on the wires starting with z? " << dec_z << '\n';
}

int main() {
  auto [wires, gates] = parse_input();
  solve_part1(wires, gates);
}
