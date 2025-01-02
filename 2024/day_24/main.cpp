// https://adventofcode.com/2024/day/24
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

// https://en.wikipedia.org/wiki/Double_factorial
constexpr uint64_t semifactorial(uint64_t n) {
  if (n == 0 || n == 1) { return 1; }

  uint64_t res = 1;
  do {
    res *= n;
    n -= 2;
  } while (n > 1);
  return res;
}

// C(n, 2m) * ((2m - 1)!!)
//
// For n = 222, m = 4, the result is 13523504751481725, which is very large.
constexpr uint64_t calc_num_of_unique_pairs(uint64_t n, uint64_t m) {
  if (n < m * 2) {
    throw std::invalid_argument("`n` must be greater than or equal to 2m");
  }

  uint64_t k = std::min(m * 2, n - m * 2);
  uint64_t p = 1;
  uint64_t q = 1;
  for (int i = 0; i < k; ++i) {
    p *= n - i;
    q *= i + 1;
  }

  return (p / q) * semifactorial(m * 2 - 1);;
}

template<typename Callback>
void find_all_pairs(std::vector<std::pair<std::string, std::string>>& curr_pairs,
                    std::vector<bool>& used,
                    std::vector<std::string> const& elements,
                    int m,
                    int start_idx,
                    Callback const& callback) {
  if (curr_pairs.size() == m) {
    callback(curr_pairs);
    return;
  }

  for (int i = start_idx; i < elements.size(); ++i) {
    if (used[i]) { continue; }

    for (int j = i + 1; j < elements.size(); ++j) {
      if (used[j]) { continue; }

      curr_pairs.emplace_back(elements[i], elements[j]);
      used[i] = used[j] = true;

      find_all_pairs(curr_pairs, used, elements, m, i + 1, callback);

      curr_pairs.pop_back();
      used[i] = used[j] = false;
    }
  }
}

template<typename Callback>
void traverse_all_pairs(std::unordered_set<std::string> const& elements_set, int m, Callback const& callback) {
  if (elements_set.size() < 2 * m) { return; }

  std::vector<std::string> elements{elements_set.cbegin(), elements_set.cend()};
  std::sort(elements.begin(), elements.end());

  std::vector<bool> used(elements.size(), false);
  std::vector<std::pair<std::string, std::string>> curr_pairs{};
  find_all_pairs(curr_pairs, used, elements, m, 0, callback);
}

int main() {
  auto [wires, gates] = parse_input();
  solve_part1(wires, gates);

  // Debug: It's impossible to swap back and check all possible 4-pair gates.
  {
    std::cout << calc_num_of_unique_pairs(gates.size(), 4) << '\n';

    std::unordered_set<std::string> all_gate_outputs{};
    all_gate_outputs.reserve(gates.size());
    for (auto const& [output, _] : gates) {
      all_gate_outputs.emplace(output);
    }
    int count = 0;
    traverse_all_pairs(all_gate_outputs, 4, [&count] (std::vector<std::pair<std::string, std::string>> const& pairs) {
      ++count;
      std::cout << count << '\n';
    });
  }
}
