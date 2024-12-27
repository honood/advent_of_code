// https://adventofcode.com/2024/day/23
//
// clang++ -std=gnu++20 -stdlib=libc++ main.cpp -o main && ./main && rm main

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include <iostream>

#include "../aoc.h"

namespace {

std::unordered_set<std::string> set_intersection(std::unordered_set<std::string> const& a, std::unordered_set<std::string> const& b) {
  auto const& smaller = a.size() < b.size() ? a : b;
  auto const& larger = a.size() < b.size() ? b : a;

  std::unordered_set<std::string> res{};
  for (auto const& e : smaller) {
    if (larger.contains(e)) { res.emplace(e); }
  }
  return res;
}

std::unordered_set<std::string> set_union(std::unordered_set<std::string> const& a, std::unordered_set<std::string> const& b) {
  std::unordered_set<std::string> res{a};
  for (auto const& e : b) {
    res.emplace(e);
  }
  return res;
}

std::unordered_set<std::string> set_difference(std::unordered_set<std::string> const& in, std::unordered_set<std::string> const& notin) {
  std::unordered_set<std::string> res{};
  for (auto const& e : in) {
    if (!notin.contains(e)) { res.emplace(e); }
  }
  return res;
}

} // namespace

std::vector<std::pair<std::string, std::string>> parse_input() {
  std::vector<std::pair<std::string, std::string>> edges{};
  std::ifstream ifs{helper::read_file_as_stream("input.txt")};
  std::string line{};
  while (std::getline(ifs, line)) {
    auto pos = line.find('-');
    edges.emplace_back(line.substr(0, pos), line.substr(pos + 1));
  }
  return edges;
}

std::unordered_map<std::string, std::unordered_set<std::string>>
build_graph(std::vector<std::pair<std::string, std::string>> const& edges) {
  std::unordered_map<std::string, std::unordered_set<std::string>> adj_list{};
  for (auto const& [u, v] : edges) {
    adj_list[u].emplace(v);
    adj_list[v].emplace(u);
  }
  return adj_list;
}

void solve_part1(std::unordered_map<std::string, std::unordered_set<std::string>> const& graph) {
  int count = 0;
  for (auto const& [u, neighbors] : graph) {
    for (auto const& v : neighbors) {
      for (auto const& w : neighbors) {
        if ((u < v && v < w)
            && (u.starts_with('t') || v.starts_with('t') || w.starts_with('t'))
            && graph.at(v).contains(w)) {
          ++count;
        }
      }
    }
  }

  assert(1419 == count);
  std::cout << "Part 1: How many contain at least one computer with a name that starts with t? " << count << '\n';
}

// Find a maximum clique
// https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
//
// Note: While a maximum (i.e., largest) clique is necessarily maximal, the converse does not hold.
void bron_kerbosch_no_pivot(std::unordered_set<std::string> clique,
                            std::unordered_set<std::string> potential,
                            std::unordered_set<std::string> excluded,
                            std::unordered_map<std::string, std::unordered_set<std::string>> const& graph,
                            std::unordered_set<std::string>& maximum_clique) {
  if (potential.empty() && excluded.empty()) {
    if (clique.size() > maximum_clique.size()) {
      maximum_clique.swap(clique);
    }
    return;
  }

  auto candidates{potential};
  for (auto const& node : candidates) {
    bron_kerbosch_no_pivot(set_union(clique, {node}), 
                           set_intersection(potential, graph.at(node)),
                           set_intersection(excluded, graph.at(node)), 
                           graph, 
                           maximum_clique);
    potential.erase(node);
    excluded.emplace(node);
  }
}

void bron_kerbosch(std::unordered_set<std::string> clique,
                   std::unordered_set<std::string> potential,
                   std::unordered_set<std::string> excluded,
                   std::unordered_map<std::string, std::unordered_set<std::string>> const& graph,
                   std::unordered_set<std::string>& maximum_clique) {
  if (potential.empty() && excluded.empty()) {
    if (clique.size() > maximum_clique.size()) {
      maximum_clique.swap(clique);
    }
    return;
  }

  std::string pivot{};
  if (!potential.empty()) {
    pivot = *potential.begin();
  } else if (!excluded.empty()) {
    pivot = *excluded.begin();
  } else {
    return;
  }

  auto candidates{set_difference(potential, graph.at(pivot))};
  for (auto const& node : candidates) {
    bron_kerbosch(set_union(clique, {node}),
                  set_intersection(potential, graph.at(node)),
                  set_intersection(excluded, graph.at(node)),
                  graph,
                  maximum_clique);
    potential.erase(node);
    excluded.emplace(node);
  }
}

void solve_part2(std::unordered_map<std::string, std::unordered_set<std::string>> const& graph) {
  std::unordered_set<std::string> maximum_clique{};
  std::unordered_set<std::string> potential{};
  for (auto const& [u, _] : graph) { potential.emplace(u); }

  // bron_kerbosch_no_pivot({}, potential, {}, graph, maximum_clique);
  bron_kerbosch({}, potential, {}, graph, maximum_clique);

  std::vector<std::string> temp{maximum_clique.cbegin(), maximum_clique.cend()};
  std::sort(temp.begin(), temp.end());
  std::string password{};
  for (int i = 0; i < temp.size(); ++i) {
    password += temp[i];
    if (i != temp.size() - 1) { password += ','; }
  }

  assert("af,aq,ck,ee,fb,it,kg,of,ol,rt,sc,vk,zh" == password);
  std::cout << "Part 2: What is the password to get into the LAN party? " << password << '\n';
}

int main() {
  auto graph = build_graph(parse_input());
  solve_part1(graph);
  solve_part2(graph);
}
