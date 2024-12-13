// https://adventofcode.com/2024/day/8
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <numeric>
#include <cassert>
#include <iostream>

#include "../aoc.h"

using pos_t = std::pair<int, int>;

std::vector<std::string> parse_input() {
  std::ifstream ifs("input.txt");
  std::vector<std::string> res{};
  std::string row{};
  while (std::getline(ifs, row)) {
    res.emplace_back(std::move(row));
  }

  return res;
}

std::unordered_map<char, std::vector<pos_t>> find_antennas(std::vector<std::string> const& map) {
  std::unordered_map<char, std::vector<pos_t>> res{};
  for (int i = 0; i < map.size(); i++) {
    for (int j = 0; j < map[0].size(); ++j) {
      if (map[i][j] == '.') { continue; }
      res[map[i][j]].emplace_back(i, j); 
    }
  }

  return res;
}

inline bool pos_in_bounds(pos_t const& p, int const rows, int const cols) {
  return p.first >= 0 && p.first < rows && p.second >= 0 && p.second < cols;
}

template<bool ForPart2 = false>
void mark_antinodes(pos_t const& antenna1, pos_t const& antenna2,
                    int const rows, int const cols,
                    std::vector<bool>& marked) {
  pos_t antinode1{2 * antenna1.first - antenna2.first, 2 * antenna1.second - antenna2.second};
  pos_t antinode2{2 * antenna2.first - antenna1.first, 2 * antenna2.second - antenna1.second};

  if (pos_in_bounds(antinode1, rows, cols) && !marked[antinode1.first * cols + antinode1.second]) {
    marked[antinode1.first * cols + antinode1.second] = true;
  }
  if (pos_in_bounds(antinode2, rows, cols) && !marked[antinode2.first * cols + antinode2.second]) {
    marked[antinode2.first * cols + antinode2.second] = true;
  }
}

template<>
void mark_antinodes<true>(pos_t const& p1, pos_t const& p2, int const rows, int const cols, std::vector<bool>& marked) {
  auto helper = [rows, cols, &marked](pos_t p1, pos_t p2) {
    while (pos_in_bounds(p1, rows, cols)) {
      if (int i = cols * p1.first + p1.second; !marked[i]) { marked[i] = true; }

      pos_t temp{2 * p1.first - p2.first, 2 * p1.second - p2.second};
      p2 = p1;
      p1 = temp;
    }
  };

  helper(p1, p2);
  helper(p2, p1);
}

template<bool ForPart2>
int find_all_antinodes(std::vector<std::string> const& map) {
  int rows = map.size();
  int cols = map[0].size();

  std::vector<bool> marked(rows * cols, false);

  for (auto& [freq, antennas] : find_antennas(map)) {
    if (antennas.size() < 2) { continue; }

    for (int i = 0; i < antennas.size(); ++i) {
      for (int j = i + 1; j < antennas.size(); ++j) {
        mark_antinodes<ForPart2>(antennas[i], antennas[j], rows, cols, marked);
      }
    }
  }

  return std::reduce(marked.cbegin(), marked.cend(), 0, [](int acc, bool marked) {
    return acc + (marked ? 1 : 0);
  });
}

int main() {
  auto map = parse_input();

  int unique_antinodes_cnt = find_all_antinodes<false>(map);
  assert(unique_antinodes_cnt == 276);
  std::cout << "Part 1: How many unique locations within the bounds of the map contain an antinode? " << unique_antinodes_cnt << '\n';

  unique_antinodes_cnt = find_all_antinodes<true>(map);
  assert(unique_antinodes_cnt == 991);
  std::cout << "Part 2: How many unique locations within the bounds of the map contain an antinode? " << unique_antinodes_cnt << '\n';
}
