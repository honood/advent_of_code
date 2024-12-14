// https://adventofcode.com/2024/day/9
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <cstdint>
#include <string>
#include <utility>
#include <cassert>
#include <iostream>

#include "../aoc.h"

using u64 = uint64_t;

std::vector<u64> parse_disk_map(std::string const &disk_map) {
  std::vector<u64> blocks{};
  u64 file_id = 0;
  for (u64 i = 0; i < disk_map.size(); ++i) {
    char c = disk_map[i];
    if (c <= '0' || c > '9') { continue; }
    blocks.resize(blocks.size() + c - '0', i & 0x1 ? -1 : file_id++);
  }

  return blocks;
}

void compact_files(std::vector<u64>& blocks) {
  for (u64 i = 0, j = blocks.size() - 1; i < j;) {
    if (blocks[i] == -1 && blocks[j] != -1) {
      std::swap(blocks[i++], blocks[j--]);
    } else {
      if (blocks[i] != -1) { ++i; }
      if (blocks[j] == -1) { --j; }
    }
  }
}

u64 calculate_checksum(std::vector<u64> const& compacted_blocks) {
  u64 filesystem_checksum = 0;
  for (u64 i = 1; i < compacted_blocks.size(); ++i) {
    if (compacted_blocks[i] == -1) { continue; }
    filesystem_checksum += i * compacted_blocks[i];
  }

  return filesystem_checksum;
}

int main() {
  std::string const disk_map = helper::read_file_as_string("input.txt");
  std::vector<u64> blocks = parse_disk_map(disk_map);

  compact_files(blocks);
  u64 filesystem_checksum = calculate_checksum(blocks);
  assert(filesystem_checksum == 6216544403458);
  std::cout << "Part 1: What is the resulting filesystem checksum? " << filesystem_checksum << std::endl;
}
