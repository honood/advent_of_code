// rustc scaffold.rs && ./scaffold && rm scaffold

use std::fs;
use std::io::Write;

fn write_file(path: std::path::PathBuf, content: &str) -> std::io::Result<()> {
  let mut file = fs::File::create(path)?;
  file.write_all(content.as_bytes())?;
  Ok(())
}

fn main() -> std::io::Result<()> {
  println!("Scaffolding Advent of Code 2025 in current directory...");
  let root_dir = std::env::current_dir()?;

  for day in 1..=25 {
    let dir_name = format!("day_{:02}", day);
    let dir_path = root_dir.join(&dir_name);

    // Ignore error if exists
    let _ = fs::create_dir(&dir_path);
    println!("Creating files for {}...", dir_name);

    // 1. input.txt (0 bytes)
    fs::File::create(dir_path.join("input.txt"))?;

    let d = day.to_string();

    // 2. main.cpp (Template: 2 spaces)
    let cpp_content = format!(
r#"// https://adventofcode.com/2025/day/{d}
//
// clang++ -std=gnu++23 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <iostream>

int main() {{
  std::cout << "Hello, Advent of Code 2025!" << std::endl;
}}
"#);
    write_file(dir_path.join("main.cpp"), &cpp_content)?;

    // 3. main.swift (Template: Top level)
    let swift_content = format!(
r#"// https://adventofcode.com/2025/day/{d}
//
// swiftc main.swift -o main && ./main && rm main
// -OR-
// swift main.swift

print("Hello, Advent of Code 2025!")
"#);
    write_file(dir_path.join("main.swift"), &swift_content)?;

    // 4. main.go (Template: Hard Tab)
    // Raw string preserves the Tab character literally
    let go_content = format!(
r#"// https://adventofcode.com/2025/day/{d}
//
// go build -o main main.go && ./main && rm main
// -OR-
// go run main.go

package main

import "fmt"

func main() {{
	fmt.Println("Hello, Advent of Code 2025!")
}}
"#);
    write_file(dir_path.join("main.go"), &go_content)?;

    // 5. main.rs (Template: 2 spaces)
    let rs_content = format!(
r#"// https://adventofcode.com/2025/day/{d}
//
// rustc main.rs && ./main && rm main

fn main() {{
  println!("Hello, Advent of Code 2025!");
}}
"#);
    write_file(dir_path.join("main.rs"), &rs_content)?;

    // 6. main.zig (Template: 4 spaces)
    let zig_content = format!(
r#"// https://adventofcode.com/2025/day/{d}
//
// zig build-exe main.zig && ./main && rm main
// -OR-
// zig run main.zig

const std = @import("std");

pub fn main() !void {{
    std.debug.print("Hello, Advent of Code 2025!\n", .{{}});
}}
"#);
    write_file(dir_path.join("main.zig"), &zig_content)?;
  }

  println!("Done! Happy coding!");
  Ok(())
}
