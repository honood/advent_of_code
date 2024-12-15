// https://adventofcode.com/2024/day/10
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>

#include "../aoc.h"

// up, right, down, left
constexpr std::array<std::pair<int, int>, 4> directions{{{-1, 0}, {0, 1}, {1, 0}, {0, -1}}};

std::vector<std::vector<int>> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};

  std::vector<std::vector<int>> map{};
  std::string line{};
  while (std::getline(ifs, line)) {
    std::vector<int> row{};
    for (auto const& c : line) {
      row.emplace_back(c - '0');
    }
    map.emplace_back(std::move(row));
  }

  return map;
}

int calc_trailhead_scores_sum(std::vector<std::vector<int>> const& map) {
  int const rows = map.size();
  int const cols = map[0].size();

  int score = 0;
  int visit_id = 0;
  std::vector<int> visited(rows * cols, 0);
  std::function<void(int, int)> dfs = [&](int row, int col) {
    if (map[row][col] == 9) {
      if (visited[cols * row + col] != visit_id) {
        score += 1;
        visited[cols * row + col] = visit_id;
      }
      return;
    }

    for (auto const& [drow, dcol] : directions) {
      int next_row = row + drow;
      int next_col = col + dcol;
      if (next_row >= 0 && next_row < rows && next_col >= 0 && next_col < cols
        && map[next_row][next_col] == map[row][col] + 1) {
        dfs(next_row, next_col);
      }
    }
  }; // dfs

  int sum = 0;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (map[i][j] != 0) { continue; }
      ++visit_id;
      score = 0;
      dfs(i, j);
      sum += score;
    }
  }

  return sum;
}

int main() {
  auto map = parse_input();

  int scores_sum = calc_trailhead_scores_sum(map);
  assert(607 == scores_sum);
  std::cout << "What is the sum of the scores of all trailheads on your topographic map? " << scores_sum << '\n';
}
