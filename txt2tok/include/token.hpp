#ifndef _T2T_TOKEN_HPP_
#define _T2T_TOKEN_HPP_

#include <string>

namespace t2t {

struct MaybeToken;

struct Token {
  std::size_t tid;
  std::string val;  // TODO: replace to StrSpan
  operator MaybeToken();
};

struct MaybeToken final : Token {
  operator bool();  // return true if Token::val is not empty
};

}  // namespace t2t

#endif  // _T2T_TOKEN_HPP_
