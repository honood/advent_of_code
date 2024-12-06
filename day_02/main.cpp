// https://adventofcode.com/2024/day/2
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>
#include <cassert>

#include "../aoc.h"

std::vector<std::vector<int>> parse_input() {
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};

  std::vector<std::vector<int>> reports;
  std::string report_str;
  while (std::getline(ifs, report_str)) {
    std::vector<int> report;
    std::istringstream iss2(report_str);
    int level;
    while (iss2 >> level) {
      report.emplace_back(level);
    }

    if (!report.empty()) {
      reports.push_back(std::move(report));
    }
  }

  return reports;
}

bool is_sequence_safe(std::vector<int> const& report, int skip_index = -1) {
  if (report.size() - (skip_index != -1 ? 1 : 0) < 2) {
    return false;
  }

  int prev = -1;
  bool is_asc = true;
  bool order_set = false;
  for (size_t i = 0; i < report.size(); ++i) {
    if (i == skip_index) {
      continue;
    }

    if (prev != -1) {
      int diff = report[i] - report[prev];
      if (diff == 0) {
        return false;
      }

      if (!order_set) {
        is_asc = diff > 0;
        order_set = true;
      }

      if (is_asc && (diff < 1 || diff > 3)) {
        return false;
      }
      if (!is_asc && (diff > -1 || diff < -3)) {
        return false;
      }
    }

    prev = i;
  }

  return true;
}

bool is_report_safe_with_dampener(std::vector<int> const& report) {
  if (is_sequence_safe(report)) {
    return true;
  }

  for (size_t i = 0; i < report.size(); ++i) {
    if (is_sequence_safe(report, i)) {
      return true;
    }
  }

  return false;
}

int calculate_safe_reports_num(std::vector<std::vector<int>> const& reports) {
  return std::transform_reduce(reports.cbegin(), reports.cend(), 0, std::plus<int>{}, [](auto const& report) {
    return is_report_safe_with_dampener(report) ? 1 : 0;
  });
}

int main() {
  auto reports = parse_input();
  int safe_reports_num = calculate_safe_reports_num(reports);
  assert(safe_reports_num == 536);
  std::cout << "How many reports are safe? " << safe_reports_num << std::endl;
}
