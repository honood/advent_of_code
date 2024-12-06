// https://adventofcode.com/2024/day/1
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <cassert>

#include "../aoc.h"

std::pair<std::vector<int>, std::vector<int>> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};

  std::vector<int> left_list{};
  std::vector<int> right_list{};
  int location_id;
  bool push_left = true;
  while (ifs >> location_id) {
    if (push_left) {
      left_list.emplace_back(location_id);
    } else {
      right_list.emplace_back(location_id);
    }

    push_left = !push_left;
  }

  return {left_list, right_list};
}

int calculate_total_distance(std::vector<int>& left_list, std::vector<int>& right_list) {
  std::sort(left_list.begin(), left_list.end());
  std::sort(right_list.begin(), right_list.end());

  int total_distance = 0;
  for (auto left_it = left_list.cbegin(), right_it = right_list.cbegin();
       left_it != left_list.cend() && right_it != right_list.cend();
       ++left_it, ++right_it) {
    total_distance += std::abs(*left_it - *right_it);
  }

  return total_distance;
}

int calculate_similarity_score(std::vector<int>& left_list, std::vector<int>& right_list) {
  std::unordered_map<int, int> right_list_freq{};
  for (auto elem : right_list) {
    ++right_list_freq[elem];
  }

  int similarity_score = 0;
  for (auto elem : left_list) {
    similarity_score += elem * right_list_freq[elem];
  }

  return similarity_score;
}

int main() {
  auto [left_list, right_list] = parse_input();

  int total_distance = calculate_total_distance(left_list, right_list);
  assert(total_distance == 1603498);
  std::cout << "Total distance: "<< total_distance << '\n';

  int similarity_score = calculate_similarity_score(left_list, right_list);
  assert(similarity_score == 25574739);
  std::cout << "Similarity score: " << similarity_score << '\n';
}
