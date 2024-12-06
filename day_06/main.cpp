// https://adventofcode.com/2024/day/6
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <array>
#include <cassert>
#include <iostream>

#include "../aoc.h"

std::vector<std::string> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};

  std::vector<std::string> grid{};
  std::string row{};
  while (std::getline(ifs, row)) {
    grid.emplace_back(std::move(row));
  }

  return grid;
}

std::pair<int, int> find_initial_position(std::vector<std::string> const& grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] == '^') {
        return {i, j};
      }
    }
  }

  throw std::runtime_error{"Cannot find initial position indicator (^)"};
}

int solve_part1(std::vector<std::string>& grid) {
  constexpr std::array<std::pair<int, int>, 4> directions{{
    {-1, 0}, // up
    {0, 1},  // right
    {1, 0},  // down
    {0, -1}  // left
  }};

  int res = 1;

  auto [row, col] = find_initial_position(grid);
  grid[row][col] = 'X';

  int rows = grid.size();
  int cols = grid[0].size();
  int dir_index = 0;
  for (;;) {
    auto [drow, dcol] = directions[dir_index];
    int next_row = row + drow;
    int next_col = col + dcol;
    if ((next_row == 0 || next_row == rows - 1 || next_col == 0 || next_col == cols - 1)
        && grid[next_row][next_col] != '#') {
      grid[next_row][next_col] = 'X';
      ++res;
      break;
    }

    if (grid[next_row][next_col] == '#') {
      dir_index = (dir_index + 1) % directions.size();
    } else {
      if (grid[next_row][next_col] != 'X') {
        grid[next_row][next_col] = 'X';
        ++res;
      }

      row = next_row;
      col = next_col;
    }
  }

  return res;
}

int main() {
  auto grid = parse_input();
  int part1_answer = solve_part1(grid);
  assert(part1_answer == 5409);
  std::cout << "How many distinct positions will the guard visit before leaving the mapped area? " << part1_answer << '\n';
}
