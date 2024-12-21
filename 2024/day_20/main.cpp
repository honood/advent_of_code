// https://adventofcode.com/2024/day/20
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <vector>
#include <utility>
#include <fstream>
#include <string>
#include <numeric>
#include <algorithm>
#include <array>
#include <unordered_set>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <iostream>

#include "../aoc.h"

constexpr std::array<std::pair<int, int>, 4> directions{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

std::vector<std::string> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};

  std::vector<std::string> map{};
  std::string row{};
  while (std::getline(ifs, row)) {
    map.emplace_back(std::move(row));
  }

  return map;
}

std::vector<std::pair<int, int>> find_path_without_cheat(std::vector<std::string> const& map) {
  int const rows = map.size();
  int const cols = map[0].size();

  std::pair<int, int> start{-1, -1};
  for (int i = 0; i < rows; ++i) {
    auto found = map[i].find('S');
    if (found != std::string::npos) {
      start = {i, found};
      break;
    }
  }

  std::vector<std::pair<int, int>> path{start};
  std::unordered_set<int> visited{cols * start.first + start.second};

  bool reach_end = false;
  while (!reach_end) {
    for (auto const [dr, dc] : directions) {
      auto [r, c] = path.back();
      int nr = r + dr;
      int nc = c + dc;
      if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) { continue; }
      if (visited.contains(cols * nr + nc)) { continue; }

      char cell = map[nr][nc];
      if (cell == '.') {
        path.emplace_back(nr, nc);
        visited.emplace(cols * nr + nc);
        break;
      } else if (cell == 'E') {
        path.emplace_back(nr, nc);
        reach_end = true;
        break;
      }
    } // for
  } // while

  return path;
}

void solve_part1(std::vector<std::string> const& map, std::vector<std::pair<int, int>> const& path) {
  int res = 0;

  int bit_width = [](uint64_t n) {
    int width = 0;
    while (n > 0) {
      ++width;
      n >>= 1;
    }
    return width;
  }(map.size());
  std::unordered_set<uint64_t> visited{};

  for (int i = 0; i < path.size(); ++i) {
    for (int j = i + 3; j < path.size(); ++j) {
      auto [cheat_start_row, cheat_start_col] = path[i];
      auto [cheat_end_row, cheat_end_col] = path[j];
      if ((cheat_start_row == cheat_end_row && std::abs(cheat_start_col - cheat_end_col) == 2)
          || (cheat_start_col == cheat_end_col && std::abs(cheat_start_row - cheat_end_row) == 2)) {
        if (int save_steps = (j - i) - 2; save_steps >= 100) {
          uint64_t hash = (static_cast<uint64_t>(cheat_start_row) << (bit_width * 3)) +
                          (static_cast<uint64_t>(cheat_start_col) << (bit_width * 2)) +
                          (static_cast<uint64_t>(cheat_end_row) << bit_width) +
                          static_cast<uint64_t>(cheat_end_col);
          if (!visited.contains(hash)) {
            ++res;
            visited.emplace(hash);
          }
        }
      }
    } // for
  } // for

  assert(res == 1415);
  std::cout << "Part 1: How many cheats would save you at least 100 picoseconds? " << res << std::endl;
}

int main() {
  auto map = parse_input();
  auto path = find_path_without_cheat(map);
  solve_part1(map, path);
}
