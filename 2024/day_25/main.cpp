// https://adventofcode.com/2024/day/25
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <fstream>
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
#include <cstdint>
#include <cassert>
#include <iostream>

#include "../aoc.h"

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};

  // `locks` and `keys` will store their respective schematic representations.
  // Each vector's first element represents the maximum height of the schematic.
  std::vector<std::vector<int>> locks{};
  std::vector<std::vector<int>> keys{};

  std::string line{};
  bool is_lock = false;
  int schematic_row_index = 0;

  while (std::getline(ifs, line)) {
    if (line.empty()) {
      schematic_row_index = 0;
      continue;
    }

    if (schematic_row_index == 0) {
      is_lock = line[0] == '#';
      (is_lock ? locks : keys).emplace_back(line.size() + 1, is_lock ? 0 : -1);
    } else {
      auto& target = is_lock ? locks.back() : keys.back();
      target[0] = schematic_row_index - 1; // Update the maximum height
      std::transform(line.cbegin(), line.cend(), std::next(target.cbegin()), std::next(target.begin()), [](char c, int i) {
        return i + (c == '#' ? 1 : 0);
      });
    }

    ++schematic_row_index;
  } // while

  return {locks, keys};
}

void solve_part1(std::vector<std::vector<int>> const& locks, std::vector<std::vector<int>> const& keys) {
  std::set<std::vector<int>> unique_locks{locks.cbegin(), locks.cend()};
  std::set<std::vector<int>> unique_keys{keys.cbegin(), keys.cend()};

  uint64_t unique_lock_key_pair_count = unique_locks.size() * unique_keys.size();
  for (auto const& lock : unique_locks) {
    for (auto const& key : unique_keys) {
      std::size_t width = std::min(lock.size(), key.size());
      int max_height = std::max(lock[0], key[0]);

      for (std::size_t i = 1; i < width; ++i) {
        if (lock[i] + key[i] > max_height) {
          --unique_lock_key_pair_count;
          break;
        }
      }
    }
  }

  assert(3249 == unique_lock_key_pair_count);
  std::cout << "Part 1: How many unique lock/key pairs fit together without overlapping in any column? " << unique_lock_key_pair_count << '\n';
}

int main() {
  auto [locks, keys] = parse_input();
  solve_part1(locks, keys);
  // No part2 to solve.
}
