#include "source.hpp"
#include <fstream>
#include <gtest/gtest.h>

TEST(Source, reading) {
  auto src = t2t::Source("../../assets/tests.udl");
  auto istream = std::ifstream("../../assets/tests.udl");

  std::vector<std::string> lines1;
  std::vector<std::string> lines2;

  while (not src.eof()) {
    lines1.push_back(src.read_line().content);
  }

  std::string line;
  while (not istream.eof()) {
    std::getline(istream, line);
    if (line != "\n") lines2.push_back(line);
  }

  EXPECT_EQ(lines1, lines2);
}
