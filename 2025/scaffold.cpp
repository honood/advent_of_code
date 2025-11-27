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
    std::string cpp_content =
      "// https://adventofcode.com/2025/day/" + url_day + "\n"
      "//\n"
      "// clang++ -std=gnu++23 -stdlib=libc++ main.cpp -o main && ./main && rm main\n"
      "\n"
      "#include <iostream>\n"
      "\n"
      "int main() {\n"
      "  std::cout << \"Hello, Advent of Code 2025!\" << std::endl;\n"
      "}\n";
    write_file(day_path / "main.cpp", cpp_content);

    // 3. main.swift (Template: Top level / 2 spaces align)
    std::string swift_content =
      "// https://adventofcode.com/2025/day/" + url_day + "\n"
      "//\n"
      "// swiftc main.swift -o main && ./main && rm main\n"
      "// -OR-\n"
      "// swift main.swift\n"
      "\n"
      "print(\"Hello, Advent of Code 2025!\")\n";
    write_file(day_path / "main.swift", swift_content);

    // 4. main.go (Template: Hard Tab)
    std::string go_content =
      "// https://adventofcode.com/2025/day/" + url_day + "\n"
      "//\n"
      "// go build -o main main.go && ./main && rm main\n"
      "// -OR-\n"
      "// go run main.go\n"
      "\n"
      "package main\n"
      "\n"
      "import \"fmt\"\n"
      "\n"
      "func main() {\n"
      "\tfmt.Println(\"Hello, Advent of Code 2025!\")\n"
      "}\n";
    write_file(day_path / "main.go", go_content);

    // 5. main.rs (Template: 2 spaces)
    std::string rs_content =
      "// https://adventofcode.com/2025/day/" + url_day + "\n"
      "//\n"
      "// rustc main.rs && ./main && rm main\n"
      "\n"
      "fn main() {\n"
      "  println!(\"Hello, Advent of Code 2025!\");\n"
      "}\n";
    write_file(day_path / "main.rs", rs_content);

    // 6. main.zig (Template: 4 spaces)
    std::string zig_content =
      "// https://adventofcode.com/2025/day/" + url_day + "\n"
      "//\n"
      "// zig build-exe main.zig && ./main && rm main\n"
      "// -OR-\n"
      "// zig run main.zig\n"
      "\n"
      "const std = @import(\"std\");\n"
      "\n"
      "pub fn main() !void {\n"
      "    std.debug.print(\"Hello, Advent of Code 2025!\\n\", .{});\n"
      "}\n";
    write_file(day_path / "main.zig", zig_content);
  }

  std::cout << "Done! Happy coding!" << std::endl;
  return 0;
}
