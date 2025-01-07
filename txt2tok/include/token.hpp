#ifndef _T2T_TOKEN_HPP_
#define _T2T_TOKEN_HPP_

#include <string>

namespace t2t {

struct Token final {
  std::size_t tid;
  std::string val;  // TODO: replace to StrSpan
  std::size_t nrow;
  std::size_t ncol;
};

}  // namespace t2t

#endif  // _T2T_TOKEN_HPP_
