#ifndef _T2T_SOURCE_HPP_
#define _T2T_SOURCE_HPP_

#include <fstream>
#include <string_view>

namespace t2t {

class Source {
 private:
  std::size_t _line_counter = 0;
  std::fstream _ifstream;

 public:
  struct Line {
    const std::string_view fname;
    const std::size_t num;
    const std::string content;
    operator bool();
  };

  const std::string fname;

  Source(const std::string& fname);
  Line read_line();
  operator bool();
  bool eof();
};

}  // namespace t2t

#endif  // _T2T_SOURCE_HPP_
