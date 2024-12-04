// https://adventofcode.com/2024/day/4
//
// clang++ -std=gnu++20 -stdlib=libc++ day_4.cpp -o day_4 && ./day_4 && rm day_4

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <cassert>
#include <iostream>

std::string raw_input();

std::vector<std::string> parse_input_data(std::string const& input) {
  std::vector<std::string> result{};

  std::istringstream iss{input};
  std::string line{};
  while (std::getline(iss, line)) {
    if (!line.empty()) {
      result.push_back(std::move(line));
    }
  }

  return result;
}

bool is_word_start_at(std::vector<std::string> const& board,
                      std::string const& target,
                      int start_row, int start_col,
                      int dir_row, int dir_col) {
  int rows = board.size();
  int cols = board[0].size();
  for (int i = 1; i < target.length(); ++i) {
    int row = start_row + dir_row * i;
    int col = start_col + dir_col * i;
    if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != target[i]) {
      return false;
    }
  }

  return true;
}

int search_word(std::vector<std::string> const& board, std::string const& target) {
  constexpr std::array<std::pair<int, int>, 8> directions{{
    {-1, 0}, // N
    {-1, 1}, // NE
    {0, 1},  // E
    {1, 1},  // SE
    {1, 0},  // S
    {1, -1}, // SW
    {0, -1}, // W
    {-1, -1} // NW
  }};

  int count = 0;
  int rows = board.size();
  int cols = board[0].size();
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (board[i][j] != target[0]) {
        continue;
      }

      for (auto const& [dir_row, dir_col] : directions) {
        if (is_word_start_at(board, target, i, j, dir_row, dir_col)) {
          ++count;
        }
      }
    } // j
  } // i

  return count;
}

int main() {
  auto board = parse_input_data(raw_input());
  int res = search_word(board, "XMAS");
  assert(res == 2297);
  std::cout << "How many times does XMAS appear? " << res << std::endl;
}

std::string raw_input() {
  return R"(
XMMMSMMXMSXMXMAXSMMAXXXXSXXASXSASAMSXMAXAAMSMMMSXSAMXMMXMASMMMSXMXSAMXSASAMXXXXMMMMMMXMXSMXSMSMSMSXSSXSMSSMSAMMXXSAMXMXMXSMSMMASMXMAASMSMMMM
MSMXAASXMSASAAAXSASMSAMXMMMXAAMMMASMMXSXMXSAMAAMXSMMASXSSXMAAAAAMAMAXASAXMMSMMMXSAAASMMAMSAMASAAASXMAMAAAAXMAMAASAMSAMXMAAMAMAASMMMSXMAAMAAM
AAMMXXMXASAMXSSMSAMAXAMMSAXMMSMSSXMXSAXASXSASMXMAXASMMSAAASXMSSMMASMMMMMMAAAAXXAXMXMXAMAXMMSAMSMXMAXMXMMMSMSAMMXSAASASMMAXSASMMXAAAMMMSMSMXX
SSSSXASMMMSMAXXAMXMXMXMASXSAAAAXMXXXMASAMMSAMASMMSAMAXXMSMMMMAMASAXAAXASAMXSSMMMSMSSSMMSSMXMAXMMSSMMXMMAMAASXSXMSMMSAMXSAXAMMASXMMMSAXAAAASX
XAAMAMXAAAAMXMMMAAMAAAMMSXXMSSSMMSMAMAMAMAMXMAMAMAMMXMSXXMASMAXAMXSXMXMXXSAMAMAAAAAAXXAAAXXMMMMAAAAMMXSASMXMXMMMXMAMMMAMXSMAXAMAAMASXSMSXMAA
MMMMAXSMMSSMSXAASXSASXSMMASAAAAMAAAMMMSXMXMAMXSAMSASAMXAXSMMSSMMXMAXMSMMAMXMAASXMSMMMMXSAMSMSMMMSXXMAASXXXAXAAAMAMSSMMXSASXSMAXMMMAXAXAMMSMA
MXSSMMMSMMMAAMMMXAMXMXAAXAMMMSMMSMSXAXMAMAMASASASAASMAMSMSMAAMAXXMAXMAMMSSMSSXMMAXXXAAAXAASASMAAXASMMMSXMXMSMSMMASMXMAAMMSAXSAMSMMXSSMXMASXX
MAMAMMAAXSMSMSASXSAMMSSMMXSXAAXMAXAMXXSMMSSMMXMXMMMMMAXMAXMMSSMASMMXMASXAAAAMAMMSAMSMSMMMMMXMMMMMXMASAMXAMXMAAXSMXMASMMSAMAMMXXXASMAXMASXSSM
MXSSMMSMXSAAASASMMAMAAAAXXXAMMMMSASXMXAMAXAXXSMSXSMASMSMAMXMAAXAMASASAMMSMMMMXMAXAMXXXXAXMXMSXSXSXSXMASAMSSSXMXAAXAMXAXMXMMMSSMSAMMMMMMMAMAM
SMMMXMAMXXMMXMAMMSAMMSXMSMSMMXAAAMXAXSAMMMSMMMAAAXMAXAAMAMAMMSMXSAMMMASAXAXXXAMAMAMMMSSSMSAMSSMASAASMXMXMXMASXSMMSMMMSMAAXMAXAAMAXASAXXMASAM
AAAAXMMSASMXXMXMXSXSMXMASASAASMSSXMAMSXMAAAAAMMMMMMXSSMSASMSAMXXMXMXMAAMXSMSXSMMSXMAAXAAAXAMXAMAMAMMMAXAXXMMMXAXAAMAAAMSMMMMSMXMXSASAXMSASAS
SSMSXSAMXAAAXSSMAMXXAXMAMXMXXMAXXMMXMMSSMSSSSSXSMXSAAXAMMSAMXSAXAAMAMMSAMMASAMXMAXSASMMMMSSMSAMSSXMAXMSMSXXXXMSMSSSMSSXXASXXAMMMAMXMMMAMASMM
XMAXAMMMMMMMAXSMASXMMMMASXMXSMSMMMXAXSAXMAAXXAAXXAMMSMSMMMAMSSMSXMSSSMAXAMAMAMAMSXSAMXMAMAAXMAMMAASMMMAAMMMAXAAAXMXXXMASAMMSXSAASMSAAMXMAMXM
SMSMSMAASXMMXMMSMMAAAAMXMXMAMAAXAXSXMMAXMSSSSMSMMMSMMAMAASAMAMXSAXXAAXAMSMASXSXSXMMAMMMMMSSSSMSMMMMMASMSMSMASMMSMSMMSMXMXMAXXMASMAMXMXAMAXAX
AAXSXMSMXAXXAXXAMMSSMMSASAMASMMSXXAMXSMSAMAAXAAMAXAAXAMSMSASMMASXMMSSMXSXSXXAAXMASMMMXAAMAMXAAAAXAASXMXMASAASMAMMXMAXXXXSXMMAMSAMXMASXSSMMSS
MAMSXMAXSMMSXMSASAXAMASXSASASAXAMXXAMAAMXMMMMSMSSSSSMSAAMSAMXMASAMXAXMXMXMSMMMAXAMASASXMMAXSMMMSSSMSAMSMAXMASMAMXXMMMSAAXAAMSMAAXMMXSAMAXAAA
SMAMASAXAAAXMASAMMSAMXSASXMASMMSSMSSSMMMSXAAAMXXAAXAAXMSMMXSAMXXAXMSMMXMXMMMSAMMSSMMASAASXMMXMAAAMASAMXMXSMMXMAMSASAASMSMXMAMASMMASAMAMAMMXM
MXSXMMMXMMMSAMMXMXMMMAXXXMMMMAAXAASAXAXSXMSMSSSMMMMASXAAAXSXMMAXMMMAASMMAMAXASMAAAMMXMXMXAMXAMMSSMXSSMXSXMAAXXAMSAMMXMXXMMSAMAMSAMMASMMSSMSS
AAAXSASMXSXMMMMSMXMAMSMXMMAMMMMSMMMMSAMXAMXMAAAAAXAMXMSSSMMASMSSMAMSSMASASASMMMSSMMSMSSXSMMSMSAMXXXMAMXXASAMSMMXMXMXAXMAMXMASXXMSXSXMMAMAMAS
MXXMSAMAASXSAXAAMASMSAAAMSASXMAMMAMXSMSSXMAMXSSMMMSXXAAAAAMXMAAXMMMXMAXSMSXMXMAAAAMXMASXXAXAAMASMSSSMSMSAMXMMASXMMMSMSXAAAMXMMAMMMMXXMAAAMMS
MMSMMSMMMSASMMSXSAMXSMSMXAASXMAMSMSMXMAAASXSAXMAAAXAXSAMSSMSMXMXAMSAXMMSXXMSAMXXSMMAMMSMXAMXXSAMXAAAAAAMAMMMSAMAAMASXXXMXXMAXXSMAAMSSSSSSSXS
XAAMAMXASMAMXAAAMXSAMXMXMMXMMMSMXAAXAMSSMMASASXSSSMXMMAMXAAAMSMXXXMAXSAMXMASMMSMMASASXMASXXSAMAMMMSMMMMSAMSAMXMSMMMMMMAXASXXSAAXXXMAAXAXAAAX
MMXMAMAMXMAMXMAMXXAMXASMXXMAXAMXMSMSXMMAXMAMMMXXAAAASMMSSMMMMAMASMMMMMASXXAXMAMAMAMASAMXMXASXSAMMXAMAMMSASMXXSAXAMXAAXMAXSAASXMASXMMSMMMSMMM
MSSSXSAMXAMMAMSMSMMXMMSAASXSMMSAAAXMMMSMMMMSAAXSMSMMMAXAAAMSSMSAAMAAXSAMMMMMMMSAMAMXMMMSMMAMAXAXSXMSASAXMMASAMMSMMSSXSXSXMMMMAXAAAAAMAXXMAMX
AAAAMSMMSMMMSSMAMXMSASMMMSAMAXSXSMXMXAAAAXAMXSMSXMMXXSMSMMMAAXMMSSSSMMASXMSAXMAXSMSXMAXAASXMSMSXSAASMMMSAXASXMXAMMAMMSAXASXXMAMXSXMMSMMMSSMA
AMMMMXXAXXMAXAMXMSAMXXSAMXMSAMXAXXXXMMSSMSSMMXASAMXSXXAMASMSSMSAMXAXXSXMAAXMXMSXSXXAMSXSMMSAAAMASMMMMAASXMAMAXSXSMAMXMAXAMAMSXMAMMSAMAXAAAXM
SMMSXXMASXMSSMMAMAMMMASMXAXXMXMSMSMXSAAAMAXAXMXMMSAMXMMMASAMXXMAXSAMXMSMMMMSMAAASMSSMXXXAAMSMMMMMMSSMMMSAXXXMMXMMMSSXSMMMMMXAAMAMXMAXXMMSSMM
AMAMXXAMXAMXAXSXSAMAMXMASMMMMSMMXMAXMASMMSSMMMXSAMXSMSAMXSAMXXMAMXASMAAXAMAAMXMMMAXAAXAXMMMAXAAMXAAAXSXMXMMMSAXAAAAAASXSXAXSMXXASMXSMXAMAMXX
MMAXSASMSSMMMMAXMASXMSAAAAAAAAXMASXMMXMAAMXMAMAMASASASMSASAMXMSMSSMMMSMMMSSXSSXSMSMMSMSMSAMMSSSSSMSSMAAMXAXAAAXSMSMMMMAMMSMAAASMMMSXMMAAMMMM
XSASXAAAMMSAMXMMSMMMSSMMSSMMSXSSMSASXSMMMMMXMMAXAMXMAMAMXSAMXAAAXASAMXASMAMMMXAXAAXXAAXASMMXMAAAMAAMXXAMAMMASAMXAMASXMAMAMSMMMSXAXMAMMMMXAAA
MMSSMMMXMASMSASAAXAXXXXMAXMXMAMXASAMAMSMAAMXSMMSXSMMSMMMMMXMXSMMMAMXSSXAMXXMMAMMSMSMMSMMMMSMMMMSMMMMSXSASXXAXMXMXMASXMAMAMSXSXSMSMMAMASMSSSS
AXAMXSXSMAXXSAMSMMMSMSXSAMXAMAMAAMMMXMAXMXSASAAAAMAMAMXAASAMXXXSMSXXMASMAASXMMXAXAXXMXMSXMAMAMXMAMAXSAXAXSMSMMAMAMASASXSSSMAMAXAXSSMMMSAXAMX
SMXXMSASAMXAMAMMXMMAMXAAXAMXSAMXSXXAMSSSXAMASMMMSMASASXSXSASAXAXAMMSMXMXMSMMASMMSAMSMAMXASMSMSAMXMXSMAMAMMXMASASAMASAMAAXSMAMSMSMAXAASMXMAMA
AAMXMMMMAMSAMSMSAMSSMMMMMSAMXMSXXMMMXAAXMAMXMMMAMXAMMSAXAXAMAMSAAMASMXMXMXASAMXAMAAAMXMXMMXAAAMAMMSMMXMXMSASXMAMASMSAMMMMMSXSAMXMMMMMMAXSXMM
MXAAXAMXSXSAMMASMMAXXSXSAAXAASAMAMASMMSMAAXAAXMASMSSMMAMXMMXSSXMMMXMASXMMSXMASMSSXSMXSMSMAMMSMMAAXMXSXMASXASAMSMMAMSMMAXMAMXSAXXAXSMSMSMMMMM
XSSMMASXMASAMMAMAMMXXXASXMASXSASXSASAAAAMSSMSMSMSXXAMMMMXASAMMMSMMMMXMAAASASASMAMAMXAXAAAXMXAXMSSXSAMAMXSMMMMAXASMMSXSXSMXXASAMSAMXXAAAAMAAX
XAAASXMASASAMMSSSMXXMMXMAXAMXSAMXXASAMXSAMAMAAAMSMMXMAMXMAMXSAAAAAMAMSMMMSXMAXMASAMMSSSMSMMSMSMAXAMMSXSAMXXASAMAMXXSAMAMMMSMMMMASMSSMSMSSSSS
XMXMAMSAMAMXMAAMAAXSXSAXMMMMXMMSSMXMASAMMSAMMSMSXAXSSMSSMXMASMXSSXSAXXMSXMXMXMMMSXXAXMAXXAXAAXMAMMMXAXXMSSSXSAMSXSSMAMAMAAAMASMAMXMAMXAMXXAX
ASASMMMSMMMSMSMXMMMAASXSSXSXXXAAAMAMXMMSMMAXXMXSMMMAAMAMAAAXMSXMAMSMMAMMAMXMMMSAMXMSSSMMSMSSMMMSSXSMMMSAAAXMMXMMAMXMXMASMSSSSSMASASMMSSMSMSM
AXAMSASASASXAAXSXSMMASAMXAMXMMMSXSAMSAMXMSSMASAMAAAXMMXSSSSMAMSMAMSMSSMSAMXSAAMMMMAAAAXMAMXMAASXMASMAAAMMXMMMXMMMMAMASXXAXXXAXMASMMMAXXAXAXX
SMSMSMSASXMMMMMXASXXMXXAMAMMSXMXAAAXMAXXAAASAMMSSMMSXMAMAMXMAAAXAXMXAAXSXSAMMSSXSXMMMASMXMAXMMMAMSMMMSSMSMXSMAAAAXASAMMMSMMMMMMMMAAMSSSMMSMM
XAAASMMXMAMMMMAMSMAXMAXMSXMASXAXMASMMXSAMSXMSSXAXAAAAMMMSMXXMSSSSSMMMSMMSMMSAAMXMASXSMMAMSSSMSSXMAMMMAAAXXAASXMSSXAMAXSAMAAAAMASXMXSAAAASXMS
MMMMMAMXSMMSAMXMXAMXMASMXAMSMMMXSMXAXASMXXAAAMMASMMSXMMAMMMXAMAMXAMAXAASAMXMMXXAMAMXAAMSMAMMMAASXMSMASMMMMMXAXAAXMAMSMMASXSSXSMXAXMMMSMMMAMS
SASMSXMAMAASXSMSMXMAMXXXASMMXAXMMSSXMASAASXMMAAMXMMMMMMAXASXMMSMSSMSASMSAMMSMSSSSMMSAMMAMAXAMXSMSMAXMMAMMSXMMSAMSSSXXASXMAAXMMMSMMAXMAMASMMS
SASAMXMASMMXMMAAAMSMMSXXXMAXSXMXAAMAAASMMSXXXXMMAMAAAAMSMMMAMAXMAXAXMMMXAMAAAAXAAAAMASMXMSSMSXMAXSAXXXXMASXAMMAXXAXXXXMSMMMMXAAXXXXMSSSXMMAS
MAMAXASXSXSMSMSMSMAAAXMSAMXMSXMMMSSSMXMAXXXMMSXSASXSMXSAAXSSMXSAMMSMXAMSMMSMSMAMMMMMASAAAMAMSAMAMMMSSMAMAMSMMSSMMXMMMSAXMSMMMSXSMMSAAMXAXMAS
MASXMMAXMASAMAMAMXMMMMAAAMAMMASAMXAXXMSSMMSXAAXSASAMASMMSMAAAXMMXMAXMAMAAAXAAMSXXSSMAXMMMSAMSAMXSAMAAMAMMMXSAAAAMASAAMSMSASXAXAXAAAMMSSSMMXS
MASXMAAMMAMXMXMAMAXAAAMMXXSXSASAMMSMXXAAAAMMMMXMMMMMMMAAXMMMMMSXMXSSSSSSSMXSASXXMAXMMMXMASMMMAXXXAXMMSXMSASMMSSMSAMXMXXXSASMMSASMMSSXMAMXMAM
MAMAXAMXMXMXMXMAMAXSSSMXMXXASASXMAXMSMSSMASMXSXXMAMASMMMXMSMSAMASAXAAAXAAAXXXXMMSXXAMXMXMXMASMMMSXMSMSMASMMAAAMMMXSSMMMMMXMAXMAMAMXMAMMMAXAX
MSSMXASMXMSMAMSMSAXAMXAAAMMAMAMXMXXAAMXAXXMXAMXASMSXMAMSSMAAMXSAMMMMMMMSMMSXMAMXASMMSMSAMXSASMAMAXAAAMMAMXSSMSMAMXSXSAAXMASXMSMSASASAMASMSSS
MAAXSSMXAAAMAAAXXMAMMMSMSMMAMAMXXAMMMSSMMMAMXMAXAMXAMMMMASMXMMMASMXMAXXXXAXAXAMMASXAAMXAXAMMXXMAXXMMSMMMSAMXAAXAXXMAMSSMSASAMAMAAAXXASMSAAAX
MMSMMAASMSSSSSSSMSMSMAXXXXMAMAXMMMXSAAAAASXSASXSXXSAXSASMMSAMAMXMAAASMMMMSSMMMMMXMMMSSXSMMMXMSSMSMXMAXMAMAXMSMSSSMMSMAXXMASAMASMSMASMMXMMMSM
XXAAXMXMXMXAXAAXAAMAMMSMXSMSSXMAAASMMMSSMSASXXAMXMAAXSAMSAMXSSMMSMMMAAAAAAAASXMXAAAXAMAMASAASASAAAASMSAMXMAXMMXMAMAMMAMMAMXXSXMXAAAXAAXXAAXX
SSMSXXAXAAMMMMMMSMSXSASXAAAAAAXMMMSXAMMMMMMMXMAMSXMXMMAMMMSAMAAAXAXXMSMMSMSMMAASMMSMMSMSAMXMMAMSMSMSAMXXAAMSAMXSMMAMMAXXMXSAMXMSXMMSMSSXMSSX
AMXMXSSSSSSXAAMXMXMASASMSMMMSMXSAMXMAXAMXXAAXSAMXAXAMXAMAAMXSMMMMMSSXMXAAMAXMMMMMAAXMAMMXMXXMSMMXMAMAMMSSSMMMMMXXSSSSXSAAAMSAMXXSXAXAAAMSAMX
MSXMAAXAXAMXSMXAMASXMAMXXXMXMAASAMAMSSSSSSMSMMASMXMMXMAXMSMASXASMAAMASMSSXMMMAAMXSMSSMSMMMSAAMAMSMASAMMMAMXAAAAAAXMAMAAXMMXAMMMMSMAMXSMSMAMM
XMAMXMMMSMMMMSMXSXMAMMMMXMSMMAMSAMXSAXXAXMAXXSSMASMAMSAMSXMASXMMMMXXXMAMAASXSSMSAMXXAXXAAASMMMAMSXMSMSXSASMSSSSMSSXAMXMAMXXAXAAAXMXMAAXSMSXS
SSSMSXAXAAXXAMXMAMSAMXASAMMASXXXMASAMSMXMSAMMMAMAMMAXAMXAAMXXASXMSSSMMMMMMMAAAAXMAMSAMXMMXSXMMXMXAXXMAAMASAAMAXAAXMMXAXSSSMSSXSXMMAMASMMAXAA
XAMAMMSMMSMMSMMMSXMAMSAAMASAMMXMAMAMMAMAMMAAAMAMAXMXMAXXMSMXSSMMXAAAXXAAAXMMMMMMXAXMXMMSMXXMXASMSSMAMSSMSMMMMSMMMSASXMSMAAAAAXXAMMXSAMAMAMSM
MMMAMMAMXAMAAAAAMMMSAMMMXAMSSXXXMASXMASAMXASMSXXXSMMSSMSMAAMSXMXMSMMMSMSMSAAXMAAMSSSMSMAMMXSMMSXAAXXMAAMXMXAAMAMAMXMAMXMSMMMXASASAMMASMMMMAA
XSSMSMAXSAMXSSMXSAAAXXAXAAXAMMMSXMMASMSASMAMMMMMSAAMAMAAXMXMXAMMMXAAAXXAAMMMSMMMSAAMAAMMMMASAMMMSMMSXMASAMXMXXAMMXSSMMSMMXXXMMSAMXXSAMXMXAMS
MMAAXMAXMAMMXMASMMMSASMSXMMAXAAXMASAMAMAMMMMMAAXASMMAMSMXSAMSAMAAMSMMSXMSMSASAMSMMSMSMMSAMAXMMAAAAMXAXASXMAXSSMMMAXAXAAMMSSMAXMXSAXMXSASASXA
AMMXMASXSAMSAMXMAMAXXAXXASXSSMSSMAMSMXMMMMASMSSSMXSSSXXAAMAXAASMSMMAMXAAXMMASAMAAXMMXAAXSMSMMSXSMSSSSMXSASMXMASXSMMAMSMSAAAXSXAAMASMXSASMAMM
SASXMAMXMAASASXSMMAMSXSMXMAMMXMAMSAXMAXMASMSAAAXAXXXMAMMMSSMSMMAMMMMXSXMXSMAMASMSAMXXMXXMMXAAMAMAMAAMMMMAAXASAMXSAMXMXAMMSSMMMMMSMXMAXXXXMAX
AAXSMXMAMSMMXMXAAMMMMMMXAMXMMAMXMMAMSSMSXSMMMMSMMMMAMXMMXXAAXAMXMAASMMXMAMMXXXMMXXAXXXSASAXMMMAMAMMMMMSMSMXMMASXSAMSMMXMAMMXAAAXXMAXMMXSAXAM
MMMMSSMSMAAXMSXMSMMAMAXASMSSSMSAXMAMXXASAMXMAXAMSAMAMASXMSMMMXMASMMSAAAMMXSAXSAMXMMSMMXAMAXSXMASAMXMAAMAXXSSSMMASXMAMAXSXSASMXSXSSSXSAASAMSS
MSAMXMAXSMMMAXAXAAMXSMSMMAAMAMSXXXASAMXMAMAMMMXMMAXXSASAMXAAMXSXMMXSMMXSAAMAXSAMSAAMAAMXMAMMASMSAMMSMSMXMXAASXMAMMSXSMASAMMMMMMAMAMAMXMSAMAM
XSMSAMSMSMSSSSMSSSMAMAMXMMMXXMMMMSAMAXMXAMXMSAMXSMMXMMSXMMMMSASMSMXMMMAMMSMMMSAAMMMSSMSMMXXSAMMXAMAXMMMSXMSAMXAMMMMAAMAMXMMXSAMAMAMXMSMMAMMS
MXAMXMAAXAXAAXXMAMAASMMXMAMSMSXAAMAMMMXSASAAXMXMAXSAMASASXSMMAMMAMAAAMXSAMAMASMMSXMAMXXAAAMMMMSSMMSMXMASXAXASXMAMAMSMMMSMXSAMMSMMXMXAAXSXMXX
AMSMSSMSMSMMMMMMAMSAMAMMXAMAAMMMMSAMAAMSAMMSMMMMMASASMSAMAAXMSMSMXSSMSAMMSAMXSXAAMMASXXMMMSAMMXAAXAAXMAMMMSAMXMASMXXAMXMAAMASAAXSSMMSMXASMXM
SAAAAAAMAMXAAAXSAMMXSMMASXSMSMAXXSXSMSXMSSMMMMXAXMSAMXMXMSXMAMXAAAXMMMASXXAMXSMXSAMASMSMSMSAMAXAXSXSSMSSMAMXMAMMSMAMSMSXMASAMXXSAAXAAXAMMMAM
XSMXMMXMAMSMMSAAMSMAAMMMXAAAMXXXAMXMXXAMAXMAXMSMSXMASXAXXMASASMMMXSAMXAMMMSMAXAMXXMXMAAAAXSAMASMMSXAAXXAMSSSSXSMXMAMAXMASAMAMXXXMSMXSSMAAXAS
MXSXXMMSAMMASXMXMAMXSMSXSSMMMASMAMXXAMAMMSSMSXMAMMMSAMXXMSAMXSAAXAMXMMSXSAXMMMSMAMSSMSMSMMSAMAAAAXMSMMSSMXMASAAASXSSXSSXMXSAMSAMXXXAMAXSSSMS
SASMAMASMSXXMAXXSXSMAASAMXAXMASMAMMMMXAMXMAAXMMXMAXMASXMMMASASXMMXSMXMAAMAXAAAAMXMAAAAMAMAMMMMXMMMXAMXMMMAMMMSMSMAAMAXXASAMAXXAMMSMXMAMXAAAS
MAMMAMMMXAASXSMAMASMMMMMMSMMAAXMAXXAXXXXASMSMXSSSMMAXXMMASAMXXAXXMAXAMMSMMSXMSMXMSSMMMMAMXXSASXMAXXAXXMAMAMXAMXMMMMMXMXXMXSXMSAMAXMMMSMXSMMM
MAMSMSXSMSXSAAMXMAMAMSSMMAMXMSXMSMSASXXSXSMMMAXXAASMSMMSASAMSSMMXAMSMXAAAAAXXAMAAAXXMAMMSMMSASXMSSMMMXXAXAXMASAXAMXSAAXMSMXAXSXMMMAAAAAAXASM
MAMAASASAMAMXMASMSSSMAAXXXMSXMAAAAMAMAASAMXAMMMMSMMAAAMAASMMAAAXMSXMAMSSSMMSAASMMMMMMSXSAXAMXMASASAMXAXSSXMSAMASXMASMSAXAAMSMMASAMSMSSMXSAMX
SMSMSMAMXMAMXXXXAXMAMMMMMSMMASXMMSMMMMXMAMMSXSAXXXMXMXMMMMMMSSMMSAMASAXXAMXXMMMMSAAXAAXSAMSSMSMMASXMMXSAAXXMASXSAMASAMXXMSMAAAXMAMXAAMXXAMXM
SMMMAMXMAMXMXMXMMMMASMMSXSAMAMMAAXAXSSSMMSMMASXSMMSMSMSAXXXAXAMXXAMAMXMSMMMXXXAASMMXMXMMAMAMXAXAMMXSAXXMXMMXMAXXAMASASXSMAXXSMXSXMMMMSXMMSAS
MAXSASXMXMAMXAXAAXAAXMASASXMXXAMXSAMAAAMXSAMAMAMAAXAXASMSAMXSAMMSMMSMMXAMAMXMMMMMASASAMMAMAXMMSSSSXMMSMXMMXXMXMSMMMSXMAASXSXMMMMAMAAAXAMXSAS
SAMXMXMMASASXXSAMMMMMMMMAMXSMMSMXMXMMSMMAMAMSMMSMMSXMMMMSAXAMAMMAMMAASMSSXSAMXAXMXMAXASMSSMSAAAAMXMAAAMMMXAXMAMAASAMXMSMMMAXMAMSAAMSMSMMAMXM
MMSMMAMXAMAXAASASXXMXSXMXMAXAMXXAMAMAMAMASAMXSXAAXAMXMAMSAMSXSMSASMMXMAXXMMASMMSAMMSMXMAXAAMMMMMMAXSXMSAMAXXMXXAMXMASXMASMMAXAMXMSMAMMAMMSAM
XAAAMASMMSXMMMMAMMMSAMASXMSSSMSAMXASAXMXMSMSMASXSMAMMSAXMAMAAXASXSASMMSMAMSMMXAMXXAXMXSXMMMSSSSSSSXXAAXASMMSASMSXMSAXAMASMSASMSMAAMAXSASXSAS
MSSSMASXXAAMXSMAMAAMASAMAXMAXXMASMMMMSXMXMMAMMAMXMSMASMMSAMMSMAMMMAMMAMXXMAXXXMSSMMSMAMAMMXMAASXAXAMMMSMAAAMAMAXMAMMSSMAMXXAAMAASXMSXSASAMSM
MAAXMXMMMMMSAMMSXMMSXMASMMSAXMMXMMAAXMASAAXASXAXAMXMXSAMSXSAMXXXSMAMMXMASMSSSMAAAAAAMAXAMMMMMMMMAMXMXMAMMMMMXMAMMSMXAMMAXMMMMSSMXSAXAMAMMMAS
MMSMSAMXAAAMXMAXSMMMMXMMXAMXSMSMMSMMMMMSSSMMSMMXAMAMAXAMXAMASMMMASMSMXMAMAAAMAMMXMMXSSSMMXAAAAXMXMAMXXXSXMXAAMXMMMMMMMMSAAXXMAMXAAMMMMMMMSAS
AXMMXXSSMXSAAMXMAXSASAASMXSASAAAASXMXXAMAMAASAMXSSMSSSSMMXMXMAAAMMMAMMMAMSMSMSMSSSXMAXAXSSSSMXSXAMSXSXAMAMXSXXAASAMASAAXSSMSMSSMSXSASAXAXXAM
SAMXSMMASAXMASAMMMSASXSMMASAMXXSMMMMXSXSXSMMMAMAMAXAAXAASXMMMSSSXASASXSAXMAXXXAAAAMMMMMMMAMXAXXMXSAASMMMSSMXMMSXSASASMSMMXAMXAAXXMSASASMSMAM
XMAXAASAMMXAMXMMXMMAMXMAMAMAMAXMAMASXSAXAXMAXAMSMSMMSSSMMMAAAAMXMASMMASXSMAMSMMMSMAAXSMMMAMASMAXXMMMMAAAXAMXMMXASAMASXAMMMSMMSMMMMMXMXMAMXAM
MMMMMXMMSXXASAXXMAMAMXXAMXSAMXMXAMXSAMXMXMXMMXMXAXXXAAXXSSSMSMSAMXSXMAMMXMMSMSAMXXMXSAAASASAASXMASMSMXMSMXMSMAMMMXMAMXXXSAMMAXAXXMSSMSMSMMMS
AAAXXAAMXAASMMSXMASXSASMMMMXSAMSSMXMXMAXXMSMXSAMMMMMMSMXXAXAMXMXSASXMASXMASAMMSMAMASXXSMSMMAXMXAXXAAAASMXMAAMASXMASXMMXAMASMSSSMAXAAMAAXSXAX
XXMXSMSMMMMMAMXMSMSAMASXAMAAXXMAAXXSXMSMSAXAAXMXMAAAMXASMMMSMAMAMASMSAMMSMMMSAAXAMXXAXMXXAXMASMMMMMMSMSAAMSMSAMXSMSAMAXASAMAXAASAMSMMMMMMMMS
ASMMSXXASMMXAMAMAMMAMXMXSMMMSSMXXMMSAMMASXMMMSXSXMMSMXSXSAAAXXMASMXAXMAXAAAAMMMSMSSMMMMMSMMXASASXSMAMAMXMMMAMMMXSASAMMSXMASMMSMMXMAAAXAAMAMM
XXAAXAXXMAXSASXSASXSMXSAMXMSAMSAASAMAMMXMAMXMAAXXSAXMXMASMSSSSSMSASMSMSSSSMSSMXAMAAAMMAAAAXMMMMXAAMAMAMXSASMMXSAMXMMMAAXMAMXAXMSSMSMMSSSSMSS
SSMMMSMMSAMSASAXXXXAMAMAMXMMAAXSSMASXMMMXSMSMMSMAMMXAAMAMAMAMXAAXXMXAAAAXAXAAXAAMSSMAMSSSSSMASXMXMMMSMSAMXSAMMXMMXMAMMXMXAMXMMXAAMAXXAXMAXAM
XAAXAMAMAMAMAMMSSXSMMAMMMSXSXMAMXMMMMAMSAXASXAXMXMAMXXSAMXMAMSMMXXMXMMMSMMMSSMMSMXXXXXAAXAAMAMAXSXMXAMMASASMMSASAXMAMXASXSMSMSMSSMSMMMMSAMSS
SSMMMSSMMXSMSMSAAMSXSMSMAMASMSXMXXAAMAMSAMAMMXSAAMASMASMSMSSXXAMMXSAMXXAAAAMAAXAMXMMMMMMMSMMSSSMAASMMMSMMMSAXSASMXSASMAMAMAXAAAXAAAAAAXMAXAM
AAAXXAAAXMXAAXMMSMMAXAAMAMMMMMAMSSSMMAMMXMAMAMMXMSASMAMAAAXMAMAMMAMASMSASMMSSMMMMASAMAXAMXAAAAAMSMMAMXSAXXSXMMAMXMMASMXMAMMMMMSMMMMSMSSMSMMX
XSMSMSSMMSMSMSXSAAMXMSSMSASXXSAMMAAASXMMXMXXAAMAXMASMAMSMSXMXSXMMAMMMAMMMAAAAXMXSASMSAXSSSXMMMMMAAAMMAXMAMMSMMMMAXMMMMMMXSAMXAMXSMXXMXMXAAXA
MXASAMMAXXXMXMMMSSMXAXAAAMAAASXSSSMXMAASASXSXSXSXMAMXAXMXMASAAASXSSXMMSAMMMMSMAMMXSAMXXXAMXMAAXXMAMXMXSMMSAAXASXMSAMAMSMMSMSMMSAMXSXMASMSSMX
SMAMSMXAMSMSASAMAMXXXMMSMXMMMMAAAAXXMSMMAMXAXMAXSXXXMMXSASAMMSMMAAAXMMSASXXXXAMMSAMXMMXMAXSXMSSSMASMXXMASMXMMMMAXMMSAAAXXXMAXAMAMASAMAMAAAXX
XMSMXMMXMXAXAMSAMMMSXAXMASXXMMXMXMMSXMXMAMMXMMMMASXAMAASAMXSMXAMAMXMSASXMMXMMXSAMMSAMXASMXSAAAAMSAMXMAMXMAASMSSSMXMSMSMXAAMMSMXMMXSXMMSMSSMM
ASXAAXAASMSMSMXMAAAMSSMSSSXSXAXXXSASMXAXASMSMXXMAAMMMMMSAMXXMASMMSAMXXXMAMXAAMMMSASMSMASMASMMMSMMMMSXSAAMSMXXMAMXAAXAAXSSMMXAMAAXAMXAXAMAXAA
MMAXMSSMAAMAXAXXXMXMXMASAXAMXSAXSMASMSSSMSAAXMAMMSMXXMAMAMSMXAMXXMXMMXSMXMAXXXAXMASMAAAXMAMSMMAMAMSMAAMXMAMAXMMMSSSMSMXXAAXXAMSSMASXMMXMMSSX
MSAMXXMXMAMAMMMXSAMSMMSMXMMMAMMMMMMMAAXXMMXMMAAMAXMAMXMXAXSAMSSMSXAXSASMASMSSSXXMAMXXSMXMXXXMSAXAXAMXMMXSXSMXMAAXMAMXMXSXMMMSMAMMMAMXMAXXAMM
MMASXAXXXAMSSMAXMAMXASAMXMASMSAAXAXMMMSSMAXXAMXSAMXASAMMMMMAMAAAAMXMMAXSMMAMXAMMMMSMMAMXMSMAMSMSMSMMSXXMAAAMSSMXSSSMXMAMSMAAXAMXSSSSSSSSMXSA
XMSMMMMASAMXAMSXSAMSMMASXSASMMXMSXMASAAAMASMSMMMXSXMSASASMSSMSMMMAAMMSMAMMSMSAMSAXAAXAXAAXXMMMXAAAAXAAXSMSMAAAXAXAXAAMAXAXMASAXAASAAAAAXAASM
SMMAXXMXSASMMMMASMXMASMMAMASMSXXXAXAMMMSMASAAASXAMXAMXSASAAXMAAAMMXSAAXXMMMASAAXMSSSSMSMSMASXSSSSSSMMMMXXAXMSSMSMSASMSSSXSSXSXMXSMMMMMSMMASX
MASAMXMASAMXXAMXMXASMMASAMXMMXMASMMMSMSMMASMSAMMMSAMSMSMMMMMMSSMSSMMXSMMMSMMMMXAMXMXAAXMAMMAAAXAMXAXXAMAAMXMAMAAXMAXXAASXXMASASXMAMXXAXMAXSA
SAMASAMXSAMXSMMMXXMSASAMAMMMSXSAXAAAAMAAXXMXMAMAAMMXAAXAXASMMAXAAXXXAXMAMAMSASMXMASXMMMXAXXMMMMMAMSASASXMXMXAMMMXMXMMMMMSMMMMAMASAMSMMMMSMMM
MMSASASMSMSMXMSMMXXSAMMSSMAMSXMASMMSSSSSMSXXMAXMXSXSMSMXMMAMXAMMMSXMAXAASAMSASXASASXASASMSSXXMXXSAAASAXMMASMMSMAXXMSAAAAAMAAMMMXXXSXAAXAXAAX
SXMMSMMMSASMAMAAMAMMXMAAMXMXMXMAMXAXMAXAAXXAXMSSMSAMXXMASMSMSMMMXXAAMSSMSMXMMMMMMASXMMAXXAMSMMMMMMSAXMMAXAMXMAMMSXAAXSMSSSMSSSMMMMMMXMMXSMMS
AAXAXAASMAMSASXXMAAMMMMMMAMMMXSASMSMMSSMMMXMASAMXXASASMAMMAXAAAXMMASXAMMXXMASXAXMAMXMMSMMXMAXAAXMAMXASMXMSSMSASASMSMXMAMAXAXAXAASASXSMMMMXAA
SMMMMMMXMXMMMMXXSXXSAMXASXMSAAXXSAMXAMSAAXAMSMASXMMMASMSSSMSMMMSXMAXMXSAMXSAMSSXSMMASAAXSASXMSSSMXSXMMMXXMAMXXMAMXXXXSAMAMSMSMSMMAMAAMXAMMSS
MXMXXAAASASMSXSASAMXXXMAMMAMMSMMMMMMAXXXMSMSASXMMAXMSMAAXAMMMSMXAMAXASXXAXMAXAMMSAAAMXSASASAAMAXXXSXMAMMXMMSXMMAMMSAXMAMMXXAAAASMAMSMMMXSAAM
SAMXSMMSAMXSAAMMMMMXXMASXMMMAXXAAAAXMXSMMAMSASXASMMMMMMMXSAMSASXXMAXSXMASXXMMMXAMAMXSAMXMAMXMMAMXXMASXMMASASMXSASAXMASXMMAMXMMASMMXMASXAMMSS
SAMXSMMMXXXMMMMMAAMMXMAMSSXMXSMSSSMMSAAMSAXMAMMMMAMSASAAAAAMSASMXMSMMASAMASMSSMSSXSAMXSSMXMASMMMSMSAMAASASXSAMXAMMSMMAXXMASXMMMXAMAXAMMXSAAX
MXMAMAXAMXXSAMASXSSMAMXMASXSXSAMMXAAMMMMSXSMAMAMSAMSAXMMXXMMMAMAXMMAMAMAMXMAAXAAXMMXSASMMSSMAAAAXXAMAXXMAXAMXXXAXMAMXMAMXASAXXMSAMSMASAMXMAS
MAMSXMMSSMXXASASAAAXSMSMMMMSAMXMAMMMMMSXMMMMXXSMXXXMSMSSXSAMAMMMSASAMAXXAMXMMMMMSMXAMXMAAXAMSSMMSSSSSMXMXMSMAMXMMSXSAMMSMMSMSAASAAAXMAMXXMAM
SASMASAMAXASAMXSMSMAMASMMAAMXMXMAMAXAAXAXXMASXMMSMSAXXAAASMMASAXMASMMSXMAMMXXXAAAMMMSXSMMMXMXXXXAAMAXXAXXAAMXSAAXAAXXSASAXXAMMMMMMMXSAMXMMAM
MSXXXMAXSMMAMXXSMMXMMAMASMMSASAMXMSSMSSSMAMAMAAAAAMMMMMSMMASASXMSXSAAAXSAMXMMSMMSSMSAAAMAXSSSMSMMSMMMMMMMSXMASMSMMSMMXASMMMMSMSXSAAXSSMAXSAS
SXXAXSSMMXSXSXXMASMXMASAMAXSXMAMXXAAMAAAXXMMSSMMXSAMSAMAMXXMAMAMXASMMSMXAMXXAAAXXAMXMMMMAXXAAAXMXXAXAXXAXMMSMSXMMAMXXMXMAXXXAXMASXMMMXXAMXXX
AMXMMAMXMXMASMXMAMAMMAMMSMMMMXAMXMSSMMSMSMMMAXAXMMAMMAMASXMXMSAMMMMXXAAMSMSMSSSMMMMMMXXXMSMAMSMSAMXSMSSXSAASMMAMMAMAXAMSMMMXMXMXMMSSXMXSXMSM
MXAMMXMASXMAMAXMXXSXSAMMAXAXASMSSMMAAXMASXAMAMXMXSAMSSMASAXAXSMMSXMMSMSMXASAMAMAASAMXMMAXAAAXXAMASAAAAAASMMMASXMSSXMXMAAMASAMXSAMXXMASMXAMXA
XMSMMASAMAMXXSASMMMAMASXMSAAXAAAMXXMMMMAMMXMAXMAMXXXAAMAMMMMMXMAMASAMXAAMAMSMAMSMSAMSAMAXMSAMMASAMMSMXSMMSXSXMAMMXAXASMXSASXMASASMXSAMXSAMMS
MXAXSAMXSAMXXAMAAXSAMSMXASASXMMMMMMAAAAXMASMMSAAAAXMSSMMMXAXXAMMSMMASXMXMAMMMXMAASAMMAXXMXAMXSXMASAXXMMXMAXSMMXSASXMMSAAMXMAMASMMXAMAMAXAMAM
SMMMMASXSASMMSXSMMMAMXASMMAMXXMSASMSMSXAMXMAAXMXSXSAMXXMSSXSSMMAAASXMAASMXSAASMSMXXXSSMMMAASXSASMMMMSAMXMSMSAAAMXMAMXMMMMMSMXAXMSSSMXMSSSMSS
AAXAMXMASAMMAMAAAASMMMAMASXMXMMMASAMAMXXMAMMMSMMMASASASAAMXAMXAMXMMSAMSMSAMMXSAXAXSMMAAASMAMAMAMXAXAXSXMXXASXMXSASAMAMAAAXAMMMSMAMAAXSAAMXMS
SXMMSMMXMAMSSMSMSXXMASMSXMAMMAXMAMAMMMMMXAXAXXMASASXMAMMAMSSMMSMMAASXXAAMMMSXMMMMXXASXSMSXAMXMXSSSMMMXSMXMMMMMXSASAXXXXSSSSXSAAMASXMMMMSMAMM
MASXAXMAMAMXMAAMXMMSAMAMASXMAXMMSXMMSAMASMSMMMMXMXMAMXMSMMMAAAAMMMMMMSMSMAAXASMAXAMXMXAAXMXSXSMAAXAXAMASXXMAAMMMMMMSSSXAMAXAMSXSASAMXXXAXXMM
SAMXSMSAXASAMSMSASMMASXSXMAXSXSAMASMSAMMAAAXAAMASAXMMAXXXSMSMMXSAMASMXAAMMSSMMMSMXSAAMMMMMXMAXXMMSMMMSAMXMXSXSAXAXXAAMMSMMMSMXXMASXMASXMSSSS
MSMAMMSMSMMAMMASASASASAMXMMMMXMASMMASXMMMMMXXMSASXSMSSSMASAXXMAXXSASAMSMMSAMXAXAAMMMMSMSXSAMMMXAMXMAAMAMMAMAAMMSMSMMSMAXAAAASAMXXXXMSMSAAAAA
SAMASAXMAMASXSAMASAMXSASXMSAMAMMMAMMMASAMXSSMXMMSMAXAMAAASAMMMMSMMASMMMXMMSSXXXSSSMSXAMAASXSXAXAXAMMSSMXSSSMXMMAMAAMXMSSSMSSSSXMSMXMAAMMMMMM
AMMAMAMXMASMMMXMXMXMXXMXMASASXSSSMSXSMMAXAAAMXAAXAMMXMXXXMAMXAXAAMAMAAXSXAMMXSAAAXAMSSMMAMASASMMMMAAMAMMXAAXMAMXSSSMXAXMAMMAMXSAAAAXMMMAMAXM
SXMASAMXXMASAXAMXMASXXMAMASAMAAAMXMAXASMMMSMMMMMSSXMSMAMSMSMSAMMSMAMMMSAMMSAAMMMMMAMMMAXMMAMMMMXAAMXSAMAMXMMMSAMXXXAMXMSMMMAMAMSXMSSSSSXSMSS
XMAXAXSAAMAXSSSSXXMAMSMMMAMXMMMMMAMXMASAXXMASXXMXAAAAMAMAAXXXASAMMXASXSMXXMMMXSASXMMMSMMSMAMXAXXSSMMSMSSMMMAXAAXSSSSMSMXAAXAMXMMSAMAAASAMMAA
MSMMMXMASMXSAMXMXSXSASAASMSSSXSSSMSAMAXMMXMAXMSMMSMSXSAMXMMSXXAAAXXMXAXXMMASAASASXMSAAASAMMSSMSAAAAAMXAAASASMMSMAXAAAASMSMSAMXAAMXXAMXMXMMMS
AMASAAAAMXXMASXMAMAMASMMMAAAAAMAAAAAMAXSMSMSMMAAAXAXASASMSSXMMSMMSSMMMMMSAAMMXMXMAAMMSXSASAAMAMMSMMSSMSSMSAXMAMMMMSMMMAXXMAAMSMXSASXXMASXSXX
MAAMSAMXSXMSAMXMASAMAMAAMMMMMAMMSMSXMASXAAAAXSSMMMXMASAAAXMASAMAAAMXASAASMXMXASXSMMXMMMSAMMSMAMMMMXMAXMAAMAMMASAAAAAAXMXMASAMXAXMASXAXAASMAX
AMSXXXMXAMAMXMSAMXMSMSSSSMSAXSMMXXMASXAMMMMMMMASAMXXXMMMAMSAMMSMMSSSMSMXSSXMSXSMXSAXSXMMSMAAMXSAMXXSXMSMMMAMMMSXMSSSMSXSAMXAXXSXMSMMXMASAMXM
)";
}
