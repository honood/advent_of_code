// https://adventofcode.com/2024/day/21
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <iostream>

#include "../aoc.h"

std::vector<std::pair<std::string, std::string>> parse_input() {
  std::vector<std::pair<std::string, std::string>> edges{};
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};
  std::string line{};
  while (std::getline(ifs, line)) {
    auto pos = line.find('-');
    edges.emplace_back(line.substr(0, pos), line.substr(pos + 1));
  }
  return edges;
}

void solve_part1(std::vector<std::pair<std::string, std::string>> const& edges) {
  std::unordered_map<std::string, std::unordered_set<std::string>> adj_list{};
  for (auto const& [u, v] : edges) {
    adj_list[u].emplace(v);
    adj_list[v].emplace(u);
  }

  int count = 0;
  for (auto const& [u, neighbors] : adj_list) {
    for (auto const& v : neighbors) {
      for (auto const& w : neighbors) {
        if ((u < v && v < w)
            && (u.starts_with('t') || v.starts_with('t') || w.starts_with('t'))
            && adj_list[v].contains(w)) {
          ++count;
        }
      }
    }
  }

  assert(1419 == count);
  std::cout << "Part 1: How many contain at least one computer with a name that starts with t? " << count << '\n';
}

int main() {
  solve_part1(parse_input());
}
