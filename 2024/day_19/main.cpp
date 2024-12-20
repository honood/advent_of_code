// https://adventofcode.com/2024/day/19
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <unordered_set>
#include <string>
#include <limits>
#include <numeric>
#include <cassert>
#include <iostream>

#include "../aoc.h"

using namespace std;

pair<unordered_set<string>, vector<string>> parse_input() {
  auto ifs{helper::read_file_as_stream("input.txt")};

  string line{};
  getline(ifs, line);
  istringstream iss{std::move(line)};
  unordered_set<string> patterns{};
  string pattern{};
  while (getline(iss, pattern, ',')) {
    patterns.emplace(std::move(pattern));
    iss.ignore(numeric_limits<streamsize>::max(), ' ');
  }

  ifs.ignore(numeric_limits<streamsize>::max(), '\n');

  vector<string> designs{};
  while (getline(ifs, line)) {
    designs.emplace_back(std::move(line));
  }

  return {patterns, designs};
}

bool is_design_possible(unordered_set<string> const& patterns, string const& design) {
  vector<bool> dp(design.size() + 1, false);
  dp[0] = true;

  for (int i = 1; i < dp.size(); ++i) {
    for (auto const& pattern : patterns) {
      int len = pattern.size();
      if (i >= len && dp[i - len] && pattern == design.substr(i - len, len)) {
        dp[i] = true;
        break;
      }
    }
  }

  return dp[design.size()];
}

void solve_part1(unordered_set<string> const& patterns, vector<string> const& designs) {
  int res = reduce(designs.cbegin(), designs.cend(), 0, [&patterns](int acc, string const& design) {
    return acc + (is_design_possible(patterns, design) ? 1 : 0);
  });
  assert(313 == res);
  cout << "Part 1: How many designs are possible? " << res << '\n';
}

uint64_t count_possible_options(unordered_set<string> const& patterns, string const& design) {
  vector<uint64_t> dp(design.size() + 1, 0);
  dp[0] = 1;

  for (int i = 1; i < dp.size(); ++i) {
    for (auto const& pattern : patterns) {
      int len = pattern.size();
      if (i >= len && pattern == design.substr(i - len, len)) {
        dp[i] += dp[i - len];
      }
    }
  }

  return dp[design.size()];
}

void solve_part2(unordered_set<string> const& patterns, vector<string> const& designs) {
  // Note: Make sure the initial value in `std::reduce` has the correct 
  // type (`uint64_t`), or else it will overflow and yield incorrect results.
  uint64_t res = reduce(designs.cbegin(), designs.cend(), uint64_t{0}, [&patterns](uint64_t acc, string const& design) {
    return acc + count_possible_options(patterns, design);
  });
  assert(666491493769758 == res);
  cout << "Part 2: What do you get if you add up the number of different ways you could make each design? " << res << '\n';
}

int main() {
  auto [patterns, designs] = parse_input();
  solve_part1(patterns, designs);
  solve_part2(patterns, designs);
}
