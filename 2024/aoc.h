#pragma once

#include <string>
#include <fstream>
#include <iterator>
#include <ios>

namespace helper {

inline std::string read_file_as_string(std::string const& file_path) {
  std::ifstream ifs{file_path};
  if (!ifs.is_open()) {
    throw std::ios_base::failure("Failed to open file: " + file_path);
  }
  return {std::istreambuf_iterator<char>{ifs}, std::istreambuf_iterator<char>{}};
}

inline std::ifstream read_file_as_stream(std::string const& file_path) {
  std::ifstream ifs{file_path};
  if (!ifs.is_open()) {
    throw std::ios_base::failure("Failed to open file: " + file_path);
  }
  return ifs;
}

} // namespace helper
