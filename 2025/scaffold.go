// go run scaffold.go

package main

import (
	"fmt"
	"os"
	"path/filepath"
)

func writeFile(path string, content string) {
	_ = os.WriteFile(path, []byte(content), 0644)
}

func main() {
	fmt.Println("Scaffolding Advent of Code 2025 in current directory...")
	rootDir, _ := os.Getwd()

	for day := 1; day <= 25; day++ {
		dirName := fmt.Sprintf("day_%02d", day)
		dirPath := filepath.Join(rootDir, dirName)
		_ = os.MkdirAll(dirPath, 0755)

		fmt.Printf("Creating files for %s...\n", dirName)

		// 1. input.txt (0 bytes)
		f, _ := os.Create(filepath.Join(dirPath, "input.txt"))
		f.Close()

		urlDay := fmt.Sprintf("%d", day)

		// 2. main.cpp (Template: 2 spaces)
		cppContent := fmt.Sprintf(`// https://adventofcode.com/2025/day/%[1]s
//
// clang++ -std=gnu++23 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <iostream>

int main() {
  std::cout << "Hello, Advent of Code 2025!" << std::endl;
}
`, urlDay)
		writeFile(filepath.Join(dirPath, "main.cpp"), cppContent)

		// 3. main.swift (Template: Top level)
		swiftContent := fmt.Sprintf(`// https://adventofcode.com/2025/day/%[1]s
//
// swiftc main.swift -o main && ./main && rm main
// -OR-
// swift main.swift

print("Hello, Advent of Code 2025!")
`, urlDay)
		writeFile(filepath.Join(dirPath, "main.swift"), swiftContent)

		// 4. main.go (Template: Hard Tab)
		// Raw string literal in Go preserves the Tab
		goContent := fmt.Sprintf(`// https://adventofcode.com/2025/day/%[1]s
//
// go build -o main main.go && ./main && rm main
// -OR-
// go run main.go

package main

import "fmt"

func main() {
	fmt.Println("Hello, Advent of Code 2025!")
}
`, urlDay)
		writeFile(filepath.Join(dirPath, "main.go"), goContent)

		// 5. main.rs (Template: 2 spaces)
		rsContent := fmt.Sprintf(`// https://adventofcode.com/2025/day/%[1]s
//
// rustc main.rs && ./main && rm main

fn main() {
  println!("Hello, Advent of Code 2025!");
}
`, urlDay)
		writeFile(filepath.Join(dirPath, "main.rs"), rsContent)

		// 6. main.zig (Template: 4 spaces)
		zigContent := fmt.Sprintf(`// https://adventofcode.com/2025/day/%[1]s
//
// zig build-exe main.zig && ./main && rm main
// -OR-
// zig run main.zig

const std = @import("std");

pub fn main() !void {
    std.debug.print("Hello, Advent of Code 2025!\n", .{});
}
`, urlDay)
		writeFile(filepath.Join(dirPath, "main.zig"), zigContent)
	}

	fmt.Println("Done! Happy coding!")
}
