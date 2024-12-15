// https://adventofcode.com/2024/day/9
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <cassert>
#include <iostream>

#include "../aoc.h"

using u64 = uint64_t;

std::pair<std::vector<u64>, std::vector<std::pair<u64, u64>>> parse_disk_map(std::string const &disk_map) {
  std::vector<u64> blocks{};
  std::vector<std::pair<u64, u64>> free_space_index{};

  u64 file_id = 0;
  for (u64 i = 0; i < disk_map.size(); ++i) {
    char c = disk_map[i];
    if (c <= '0' || c > '9') { continue; }

    u64 cnt = c - '0';
    bool is_space = (i & 0x1) == 1;
    if (is_space) {
      free_space_index.emplace_back(blocks.size(), cnt);
    }
    blocks.resize(blocks.size() + cnt, is_space ? -1 : file_id++);
  }

  return {blocks, free_space_index};
}

void part1_compact_files(std::vector<u64>& blocks) {
  for (u64 i = 0, j = blocks.size() - 1; i < j;) {
    if (blocks[i] == -1 && blocks[j] != -1) {
      std::swap(blocks[i++], blocks[j--]);
    } else {
      if (blocks[i] != -1) { ++i; }
      if (blocks[j] == -1) { --j; }
    }
  }
}

void part2_compact_files(std::vector<u64>& blocks, std::string const &disk_map, std::vector<std::pair<u64, u64>>& free_space_index) {
  auto calc_file_size = [&disk_map](u64 file_id) -> u64 {
    return disk_map[file_id * 2] - '0';
  };

  auto find_fit_space = [&free_space_index](u64 size, u64 before) -> u64 {
    for (u64 j = 0; j < free_space_index.size(); ++j) {
      auto& p = free_space_index[j];
      if (p.second >= size && p.first + p.second <= before) {
        int i = p.first;
        p.first += size;
        p.second -= size;
        return i;
      }
    }

    return -1;
  };

  using diff_t = std::iterator_traits<decltype(blocks.begin())>::difference_type;

  u64 last_try_move_id = -1; // -1: max of u64
  for (u64 i = blocks.size() - 1; blocks[i] > 0;) {
    if (blocks[i] == -1) {
      --i;
      continue;
    }

    if (blocks[i] >= last_try_move_id) {
      i -= calc_file_size(blocks[i]);
      continue;
    }

    last_try_move_id = blocks[i];

    u64 file_size = calc_file_size(blocks[i]);
    u64 file_start = i - file_size + 1;
    u64 fit_space_start = find_fit_space(file_size, file_start);
    if (fit_space_start != -1) {
      std::swap_ranges(std::next(blocks.begin(), static_cast<diff_t>(file_start)),
                       std::next(blocks.begin(), static_cast<diff_t>(file_start + file_size)),
                       std::next(blocks.begin(), static_cast<diff_t>(fit_space_start)));
    }

    i = file_start - 1;
  } // for
}

u64 calculate_checksum(std::vector<u64> const& compacted_files) {
  u64 filesystem_checksum = 0;
  for (u64 i = 1; i < compacted_files.size(); ++i) {
    if (compacted_files[i] == -1) { continue; }
    filesystem_checksum += i * compacted_files[i];
  }

  return filesystem_checksum;
}

int main() {
  std::string const disk_map = helper::read_file_as_string("input.txt");
  auto [blocks, free_space_index] = parse_disk_map(disk_map);

  auto blocks_part1{blocks};
  part1_compact_files(blocks_part1);
  u64 filesystem_checksum = calculate_checksum(blocks_part1);
  assert(filesystem_checksum == 6216544403458);
  std::cout << "Part 1: What is the resulting filesystem checksum? " << filesystem_checksum << '\n';

  auto blocks_part2{blocks};
  part2_compact_files(blocks_part2, disk_map, free_space_index);
  filesystem_checksum = calculate_checksum(blocks_part2);
  assert(filesystem_checksum == 6237075041489);
  std::cout << "Part 2: What is the resulting filesystem checksum? " << filesystem_checksum << '\n';
}
