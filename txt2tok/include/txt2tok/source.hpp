#ifndef _T2T_SOURCE_HPP_
#define _T2T_SOURCE_HPP_

#include "line.hpp"

#include <filesystem>
#include <fstream>
#include <regex>  // IWYU pragma: export

namespace t2t {

namespace fs = std::filesystem;

class Source {  // TODO: move the class to a side project
 public:
  const fs::path path;

 private:
  std::size_t _line_counter = 0;
  std::fstream _ifstream;
  const std::regex _skip_regex;

 public:
  Source(const std::string& fname, const char* skip_regex = R"(^\s*$)");
  Source(const std::string& fname, const std::regex& skip_regex);
  MaybeLine read_line();
  operator bool();
  bool eof();
};

}  // namespace t2t

#endif  // _T2T_SOURCE_HPP_
