// clang++ -std=c++23 scaffold.cpp -o scaffold && ./scaffold && rm scaffold

#include <filesystem>
#include <fstream>
#include <format>
#include <print>
#include <ranges>
#include <string>
#include <string_view>

namespace fs = std::filesystem;

void write_file(fs::path const& path, std::string_view content) {
  std::ofstream ofs(path);
  // Note: libc++ currently does not support std::print for std::ostream fully.
  // Fallback to standard stream operator.
  ofs << content;
}

int main() {
  std::println("Scaffolding Advent of Code 2025 in current directory...");

  auto root_dir = fs::current_path();

  // Use Ranges views to generate a sequence from 1 to 25
  for (int day : std::views::iota(1, 26)) {
    // C++20: Use std::format instead of snprintf
    // {:02} means: width 2, pad with 0
    auto dir_name = std::format("day_{:02}", day);
    auto day_path = root_dir / dir_name;

    std::error_code ec;
    if (fs::create_directory(day_path, ec) || !ec) {}

    std::println("Creating files for {}...", dir_name);

    // 1. input.txt (0 bytes)
    std::ofstream(day_path / "input.txt");

    // Pre-generate the URL header
    auto header = std::format("// https://adventofcode.com/2025/day/{}", day);

    // 2. main.cpp
    auto cpp_body = R"(
//
// clang++ -std=gnu++23 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <iostream>

int main() {
  std::cout << "Hello, Advent of Code 2025!" << std::endl;
}
)";
    // Use std::format to concatenate header and body efficiently
    write_file(day_path / "main.cpp", std::format("{}{}", header, cpp_body));

    // 3. main.swift
    auto swift_body = R"(
//
// swiftc main.swift -o main && ./main && rm main
// -OR-
// swift main.swift

print("Hello, Advent of Code 2025!")
)";
    write_file(day_path / "main.swift", std::format("{}{}", header, swift_body));

    // 4. main.go
    // Continue using the raw string concatenation trick for the Tab character
    auto go_body = R"(
//
// go build -o main main.go && ./main && rm main
// -OR-
// go run main.go

package main

import "fmt"

func main() {
)" "\t" R"(fmt.Println("Hello, Advent of Code 2025!")
}
)";
    write_file(day_path / "main.go", std::format("{}{}", header, go_body));

    // 5. main.rs
    auto rs_body = R"(
//
// rustc main.rs && ./main && rm main

fn main() {
  println!("Hello, Advent of Code 2025!");
}
)";
    write_file(day_path / "main.rs", std::format("{}{}", header, rs_body));

    // 6. main.zig
    auto zig_body = R"(
//
// zig build-exe main.zig && ./main && rm main
// -OR-
// zig run main.zig

const std = @import("std");

pub fn main() !void {
    std.debug.print("Hello, Advent of Code 2025!\n", .{});
}
)";
    write_file(day_path / "main.zig", std::format("{}{}", header, zig_body));
  }

  std::println("Done! Happy coding!");
  return 0;
}
