#ifndef _T2T_SOURCE_HPP_
#define _T2T_SOURCE_HPP_

#include <fstream>
#include <regex>  // IWYU pragma: export

namespace t2t {

class Source {
 private:
  std::size_t _line_counter = 0;
  std::fstream _ifstream;
  const std::regex _skip_regex;

 public:
  struct Line final {
    const std::size_t num;
    const std::string content;
    operator bool();  // return true if line is not empty
  };

  const std::string fname;

  Source(const std::string& fname, const char* skip_regex = R"(^\s*$)");
  Source(const std::string& fname, const std::regex& skip_regex);
  Line read_line();
  operator bool();
  bool eof();
};

}  // namespace t2t

#endif  // _T2T_SOURCE_HPP_
