// swift scaffold.swift

import Foundation

let fileManager = FileManager.default
let currentDir = fileManager.currentDirectoryPath

print("Scaffolding Advent of Code 2025 in current directory...")

func writeFile(at path: String, content: String) {
  try? content.write(toFile: path, atomically: true, encoding: .utf8)
}

for day in 1...25 {
  let dirName = String(format: "day_%02d", day)
  let dirPath = (currentDir as NSString).appendingPathComponent(dirName)

  try? fileManager.createDirectory(atPath: dirPath, withIntermediateDirectories: true, attributes: nil)

  print("Creating files for \(dirName)...")

  // 1. input.txt (0 bytes)
  fileManager.createFile(atPath: (dirPath as NSString).appendingPathComponent("input.txt"), contents: Data(), attributes: nil)

  let urlDay = String(day)

  // 2. main.cpp (Template: 2 spaces)
  let cppContent = """
  // https://adventofcode.com/2025/day/\(urlDay)
  //
  // clang++ -std=gnu++23 -stdlib=libc++ main.cpp -o main && ./main && rm main

  #include <iostream>

  int main() {
    std::cout << "Hello, Advent of Code 2025!" << std::endl;
  }

  """
  writeFile(at: (dirPath as NSString).appendingPathComponent("main.cpp"), content: cppContent)

  // 3. main.swift (Template: Top level)
  let swiftContent = """
  // https://adventofcode.com/2025/day/\(urlDay)
  //
  // swiftc main.swift -o main && ./main && rm main
  // -OR-
  // swift main.swift

  print("Hello, Advent of Code 2025!")

  """
  writeFile(at: (dirPath as NSString).appendingPathComponent("main.swift"), content: swiftContent)

  // 4. main.go (Template: Hard Tab)
  // Swift multi-line strings strip common indentation, so we explicitly use \t
  let goContent = """
  // https://adventofcode.com/2025/day/\(urlDay)
  //
  // go build -o main main.go && ./main && rm main
  // -OR-
  // go run main.go

  package main

  import "fmt"

  func main() {
  \tfmt.Println("Hello, Advent of Code 2025!")
  }

  """
  writeFile(at: (dirPath as NSString).appendingPathComponent("main.go"), content: goContent)

  // 5. main.rs (Template: 2 spaces)
  let rsContent = """
  // https://adventofcode.com/2025/day/\(urlDay)
  //
  // rustc main.rs && ./main && rm main

  fn main() {
    println!("Hello, Advent of Code 2025!");
  }

  """
  writeFile(at: (dirPath as NSString).appendingPathComponent("main.rs"), content: rsContent)

  // 6. main.zig (Template: 4 spaces)
  let zigContent = """
  // https://adventofcode.com/2025/day/\(urlDay)
  //
  // zig build-exe main.zig && ./main && rm main
  // -OR-
  // zig run main.zig

  const std = @import("std");

  pub fn main() !void {
      std.debug.print("Hello, Advent of Code 2025!\\n", .{});
  }

  """
  writeFile(at: (dirPath as NSString).appendingPathComponent("main.zig"), content: zigContent)
}

print("Done! Happy coding!")
