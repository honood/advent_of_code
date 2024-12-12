// https://adventofcode.com/2024/day/6
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <array>
#include <memory>
#include <cstring>
#include <cassert>
#include <iostream>

#include "../aoc.h"

constexpr std::array<std::pair<int, int>, 4> directions{{
  {-1, 0}, // up
  {0, 1},  // right
  {1, 0},  // down
  {0, -1}  // left
}};

std::vector<std::string> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};

  std::vector<std::string> map{};
  std::string row{};
  while (std::getline(ifs, row)) {
    map.emplace_back(std::move(row));
  }

  return map;
}

std::pair<std::pair<int, int>, int> find_initial_position_and_direction(std::vector<std::string>& map) {
  constexpr std::array<char, 4> indicators{'^', '>', 'v', '<'};

  int const rows = map.size();
  int const cols = map[0].size();
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      auto it = std::find(indicators.cbegin(), indicators.cend(), map[i][j]);
      if (it != indicators.cend()) {
        map[i][j] = '.';
        return {{i, j}, std::distance(indicators.cbegin(), it)};
      }
    }
  }

  throw std::runtime_error{"Cannot find initial position indicator (^)"};
}

auto compute_guard_exit_path(std::vector<std::string> const& map, std::pair<int, int> const& start_pos, int const start_dir) {
  int const rows = map.size();
  int const cols = map[0].size();

  int row = start_pos.first;
  int col = start_pos.second;
  int dir = start_dir;

  std::vector<std::pair<int, int>> exit_path{start_pos};
  std::vector<bool> visited(rows * cols, false);
  visited[cols * row + col] = true;

  while (true) {
    int next_row = row + directions[dir].first;
    int next_col = col + directions[dir].second;
    if (next_row < 0 || next_row >= rows || next_col < 0 || next_col >= cols) {
      break;
    }

    if (map[next_row][next_col] == '#') {
      dir = (dir + 1) % directions.size();
    } else {
      if (!visited[next_row * cols + next_col]) {
        exit_path.emplace_back(next_row, next_col);
        visited[next_row * cols + next_col] = true;
      }

      row = next_row;
      col = next_col;
    }
  }

  return exit_path;
}

bool will_guard_loop(std::vector<std::string> const& map, std::pair<int, int> const& start_pos, int const start_dir, bool* visited, int const visited_size) {
  std::memset(visited, 0, sizeof(bool) * visited_size);

  int const rows = map.size();
  int const cols = map[0].size();

  int row = start_pos.first;
  int col = start_pos.second;
  int dir = start_dir;

  while (true) {
    int hash = (cols * row + col) * directions.size() + dir;
    if (visited[hash]) {
      return true;
    }
    visited[hash] = true;

    int next_row = row + directions[dir].first;
    int next_col = col + directions[dir].second;
    if (next_row < 0 || next_row >= rows || next_col < 0 || next_col >= cols) {
      return false;
    }

    if (map[next_row][next_col] == '#') {
      dir = (dir + 1) % directions.size();
    } else {
      row = next_row;
      col = next_col;
    }
  }
}

int find_possible_obstructions(std::vector<std::string>& map, std::pair<int, int> const& start_pos, int const start_dir, std::vector<std::pair<int, int>> const& guard_exit_path) {
  int const rows = map.size();
  int const cols = map[0].size();

  int const size = rows * cols * directions.size();
  std::unique_ptr<bool[]> visited(new bool[size]{});

  int result = 0;
  for (auto const &pos : guard_exit_path) {
    if (pos != start_pos && map[pos.first][pos.second] != '#') {
      char backup = map[pos.first][pos.second];
      map[pos.first][pos.second] = '#';
      if (will_guard_loop(map, start_pos, start_dir, visited.get(), size)) {
        ++result;
      }
      map[pos.first][pos.second] = backup;
    }
  }

  return result;
}

int main() {
  auto map = parse_input();

  auto [start_pos, start_dir] = find_initial_position_and_direction(map);
  auto exit_path = compute_guard_exit_path(map, start_pos, start_dir);
  assert(exit_path.size() == 5409);
  std::cout << "How many distinct positions will the guard visit before leaving the mapped area? " << exit_path.size() << '\n';

  int obstructions_cnt = find_possible_obstructions(map, start_pos, start_dir, exit_path);
  assert(obstructions_cnt == 2022);
  std::cout << "How many different positions could you choose for this obstruction? " << obstructions_cnt << '\n';
}
