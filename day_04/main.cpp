// https://adventofcode.com/2024/day/4
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <cassert>
#include <iostream>

#include "../aoc.h"

std::vector<std::string> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};

  std::vector<std::string> result{};
  std::string line{};
  while (std::getline(ifs, line)) {
    result.push_back(std::move(line));
  }

  return result;
}

bool is_xmas_start_at(std::vector<std::string> const& board,
                      std::string const& xmas,
                      int start_row, int start_col,
                      int dir_row, int dir_col) {
  int rows = board.size();
  int cols = board[0].size();
  for (int i = 1; i < xmas.length(); ++i) {
    int row = start_row + dir_row * i;
    int col = start_col + dir_col * i;
    if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != xmas[i]) {
      return false;
    }
  }

  return true;
}

int search_xmas(std::vector<std::string> const& board) {
  constexpr std::array<std::pair<int, int>, 8> directions{{
    {-1, 0}, // N
    {-1, 1}, // NE
    {0, 1},  // E
    {1, 1},  // SE
    {1, 0},  // S
    {1, -1}, // SW
    {0, -1}, // W
    {-1, -1} // NW
  }};

  int count = 0;
  int rows = board.size();
  int cols = board[0].size();
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (board[i][j] != 'X') {
        continue;
      }

      for (auto const& [dir_row, dir_col] : directions) {
        if (is_xmas_start_at(board, "XMAS", i, j, dir_row, dir_col)) {
          ++count;
        }
      }
    } // j
  } // i

  return count;
}

int search_x_mas(std::vector<std::string> const& board) {
  int count = 0;

  int rows = board.size();
  int cols = board[0].size();
  std::string candidate(3, 'A');
  for (int i = 1; i < rows - 1; ++i) {
    for (int j = 1; j < cols - 1; ++j) {
      if (board[i][j] != 'A') {
        continue;
      }

      candidate[0] = board[i - 1][j - 1];
      candidate[2] = board[i + 1][j + 1];
      if (candidate != "MAS" && candidate != "SAM") {
        continue;
      }

      candidate[0] = board[i - 1][j + 1];
      candidate[2] = board[i + 1][j - 1];
      if (candidate == "MAS" || candidate == "SAM") {
        ++count;
      }
    }
  }

  return count;
}

int main() {
  auto board = parse_input();
  int res = search_xmas(board);
  assert(res == 2297);
  std::cout << "How many times does XMAS appear? " << res << std::endl;

  res = search_x_mas(board);
  assert(res == 1745);
  std::cout << "How many times does an X-MAS appear? " << res << std::endl;
}

