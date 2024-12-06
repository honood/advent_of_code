// https://adventofcode.com/2024/day/5
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <iostream>

#include "../aoc.h"

auto parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};

  std::unordered_map<int, std::unordered_set<int>> rules{};
  std::string line{};
  while (std::getline(ifs, line) && !line.empty()) {
    size_t pos = line.find('|');
    int first = std::stoi(line.substr(0, pos));
    int second = std::stoi(line.substr(pos + 1));
    rules[first].emplace(second);
  }

  std::vector<std::vector<int>> updates{};
  while (std::getline(ifs, line)) {
    std::istringstream line_iss{line};
    std::vector<int> update{};
    std::string page{};
    while (std::getline(line_iss, page, ',')) {
      update.emplace_back(std::stoi(page));
    }
    if (!update.empty()) {
      updates.emplace_back(std::move(update));
    }
  }

  return std::pair{rules, updates};
}

bool is_correct_update(std::vector<int> const& update,
                       std::unordered_map<int, std::unordered_set<int>> const& rules) {
  return std::is_sorted(update.begin(), update.end(), [&rules](int lhs, int rhs) {
    return rules.contains(lhs) && rules.at(lhs).contains(rhs);
  });
}

void sort_update(std::vector<int>& update,
                 std::unordered_map<int, std::unordered_set<int>> const& rules) {
  std::sort(update.begin(), update.end(), [&rules](int lhs, int rhs) {
    return rules.contains(lhs) && rules.at(lhs).contains(rhs);
  });
}

int add_up_middle_page_nums(std::vector<int> mid_pages) {
  return std::reduce(mid_pages.cbegin(), mid_pages.cend());
}

int main() {
  auto [rules, updates] = parse_input();

  std::vector<int> part1_mid_pages{};
  std::vector<int> part2_mid_pages{};
  for (auto& update : updates) {
    if (is_correct_update(update, rules)) {
      part1_mid_pages.emplace_back(update[update.size() / 2]);
    } else {
      sort_update(update, rules);
      part2_mid_pages.emplace_back(update[update.size() / 2]);
    }
  }

  int part1_sum = add_up_middle_page_nums(part1_mid_pages);
  assert(part1_sum == 4569);
  std::cout << "What do you get if you add up the middle page number from those correctly-ordered updates? " << part1_sum << '\n';

  int part2_sum = add_up_middle_page_nums(part2_mid_pages);
  assert(part2_sum == 6456);
  std::cout << "What do you get if you add up the middle page numbers after correctly ordering just those updates? " << part2_sum << '\n';
}
