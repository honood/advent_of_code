// zig run scaffold.zig

const std = @import("std");

pub fn main() !void {
    // 1. Initialize allocator
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    // 2. Set root directory to current working directory
    var root_dir = std.fs.cwd();
    // Note: std.fs.cwd() handle does not need to be closed, so no defer root_dir.close() here.

    std.debug.print("Scaffolding Advent of Code 2025 in current directory...\n", .{});

    // 3. Iterate Day 01 - 25
    var day: u8 = 1;
    while (day <= 25) : (day += 1) {
        // Create directory name day_xx
        const dir_name = try std.fmt.allocPrint(allocator, "day_{d:0>2}", .{day});
        defer allocator.free(dir_name);

        // Create subdirectory
        root_dir.makeDir(dir_name) catch |err| {
            if (err != error.PathAlreadyExists) return err;
        };

        // Open subdirectory
        var day_dir = try root_dir.openDir(dir_name, .{});
        defer day_dir.close();

        std.debug.print("Creating files for {s}...\n", .{dir_name});

        // 4. Create and write files
        try createInputFile(day_dir);
        try createCppFile(allocator, day_dir, day);
        try createSwiftFile(allocator, day_dir, day);
        try createGoFile(allocator, day_dir, day);
        try createRsFile(allocator, day_dir, day);
        try createZigFile(allocator, day_dir, day);
    }

    std.debug.print("Done! Happy coding!\n", .{});
}

// ---------------------------------------------------------
// File generation helper functions
// ---------------------------------------------------------

fn createInputFile(dir: std.fs.Dir) !void {
    const file = try dir.createFile("input.txt", .{});
    defer file.close();
    // 0-byte empty file
}

fn createCppFile(allocator: std.mem.Allocator, dir: std.fs.Dir, day: u8) !void {
    const template =
        \\// https://adventofcode.com/2025/day/{d}
        \\//
        \\// clang++ -std=gnu++23 -stdlib=libc++ main.cpp -o main && ./main && rm main
        \\
        \\#include <iostream>
        \\
        \\int main() {{
        \\  std::cout << "Hello, Advent of Code 2025!" << std::endl;
        \\}}
        \\
    ;
    try writeTemplateFile(allocator, dir, "main.cpp", template, .{day});
}

fn createSwiftFile(allocator: std.mem.Allocator, dir: std.fs.Dir, day: u8) !void {
    const template =
        \\// https://adventofcode.com/2025/day/{d}
        \\//
        \\// swiftc main.swift -o main && ./main && rm main
        \\// -OR-
        \\// swift main.swift
        \\
        \\print("Hello, Advent of Code 2025!")
        \\
    ;
    try writeTemplateFile(allocator, dir, "main.swift", template, .{day});
}

fn createGoFile(allocator: std.mem.Allocator, dir: std.fs.Dir, day: u8) !void {
    // Use {s} placeholder + "\t" argument to inject a real Tab key
    const template =
        \\// https://adventofcode.com/2025/day/{d}
        \\//
        \\// go build -o main main.go && ./main && rm main
        \\// -OR-
        \\// go run main.go
        \\
        \\package main
        \\
        \\import "fmt"
        \\
        \\func main() {{
        \\{s}fmt.Println("Hello, Advent of Code 2025!")
        \\}}
        \\
    ;
    // Arguments: day maps to {d}, "\t" maps to {s}
    // \t inside double quotes is a valid escape sequence, zig fmt won't complain
    try writeTemplateFile(allocator, dir, "main.go", template, .{ day, "\t" });
}

fn createRsFile(allocator: std.mem.Allocator, dir: std.fs.Dir, day: u8) !void {
    const template =
        \\// https://adventofcode.com/2025/day/{d}
        \\//
        \\// rustc main.rs && ./main && rm main
        \\
        \\fn main() {{
        \\  println!("Hello, Advent of Code 2025!");
        \\}}
        \\
    ;
    try writeTemplateFile(allocator, dir, "main.rs", template, .{day});
}

fn createZigFile(allocator: std.mem.Allocator, dir: std.fs.Dir, day: u8) !void {
    const template =
        \\// https://adventofcode.com/2025/day/{d}
        \\//
        \\// zig build-exe main.zig && ./main && rm main
        \\// -OR-
        \\// zig run main.zig
        \\
        \\const std = @import("std");
        \\
        \\pub fn main() !void {{
        \\    std.debug.print("Hello, Advent of Code 2025!\n", .{{}});
        \\}}
        \\
    ;
    try writeTemplateFile(allocator, dir, "main.zig", template, .{day});
}

fn writeTemplateFile(
    allocator: std.mem.Allocator,
    dir: std.fs.Dir,
    filename: []const u8,
    comptime fmt: []const u8,
    args: anytype, // The trailing comma ensures `zig fmt` keeps the multi-line arguments as is, instead of collapsing them into one line!
) !void {
    const file = try dir.createFile(filename, .{});
    defer file.close();

    // Render template content
    const content = try std.fmt.allocPrint(allocator, fmt, args);
    defer allocator.free(content);

    // Write to file
    try file.writeAll(content);
}
