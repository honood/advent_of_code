// clang++ -std=c++17 scaffold.cpp -o scaffold && ./scaffold && rm scaffold

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdio> // for snprintf

namespace fs = std::filesystem;

void write_file(fs::path const& path, std::string const& content) {
  std::ofstream ofs(path);
  ofs << content;
  ofs.close();
}

int main() {
  std::cout << "Scaffolding Advent of Code 2025 in current directory..." << std::endl;

  fs::path root_dir = fs::current_path();

  for (int day = 1; day <= 25; ++day) {
    char dir_buffer[10];
    std::snprintf(dir_buffer, sizeof(dir_buffer), "day_%02d", day);
    std::string dir_name(dir_buffer);

    fs::path day_path = root_dir / dir_name;

    // Create directory, ignore if exists
    std::error_code ec;
    if (fs::create_directory(day_path, ec) || ec.value() == 0) {}

    std::cout << "Creating files for " << dir_name << "..." << std::endl;

    // 1. input.txt (0 bytes)
    std::ofstream(day_path / "input.txt").close();

    std::string url_day = std::to_string(day);

    // 2. main.cpp (Template: 2 spaces)
    // Use R"(...)" syntax, no need to manually write \n and \"
    std::string cpp_content = R"(// https://adventofcode.com/2025/day/)" + url_day + R"(
//
// clang++ -std=gnu++23 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <iostream>

int main() {
  std::cout << "Hello, Advent of Code 2025!" << std::endl;
}
)";
    write_file(day_path / "main.cpp", cpp_content);

    // 3. main.swift (Template: Top level / 2 spaces align)
    std::string swift_content = R"(// https://adventofcode.com/2025/day/)" + url_day + R"(
//
// swiftc main.swift -o main && ./main && rm main
// -OR-
// swift main.swift

print("Hello, Advent of Code 2025!")
)";
    write_file(day_path / "main.swift", swift_content);

    // 4. main.go (Template: Hard Tab)
    // To ensure the generated file uses a Tab (\t) instead of spaces,
    // explicitly concatenate "\t" into the raw string.
    std::string go_content = R"(// https://adventofcode.com/2025/day/)" + url_day + R"(
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
    write_file(day_path / "main.go", go_content);

    // 5. main.rs (Template: 2 spaces)
    std::string rs_content = R"(// https://adventofcode.com/2025/day/)" + url_day + R"(
//
// rustc main.rs && ./main && rm main

fn main() {
  println!("Hello, Advent of Code 2025!");
}
)";
    write_file(day_path / "main.rs", rs_content);

    // 6. main.zig (Template: 4 spaces)
    // No double backslash escaping needed in Raw String, just write \n directly
    std::string zig_content = R"(// https://adventofcode.com/2025/day/)" + url_day + R"(
//
// zig build-exe main.zig && ./main && rm main
// -OR-
// zig run main.zig

const std = @import("std");

pub fn main() !void {
    std.debug.print("Hello, Advent of Code 2025!\n", .{});
}
)";
    write_file(day_path / "main.zig", zig_content);
  }

  std::cout << "Done! Happy coding!" << std::endl;
  return 0;
}
