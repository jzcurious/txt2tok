#ifndef _T2T_LINE_
#define _T2T_LINE_

#include <string>

namespace t2t {

struct MaybeLine;

struct Line {
  const std::size_t num;
  const std::string content;
  operator MaybeLine();
};

struct MaybeLine final : Line {
  operator bool();  // return true if line is not empty
};

}  // namespace t2t

#endif  // _T2T_LINE_
