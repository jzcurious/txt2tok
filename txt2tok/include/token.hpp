#ifndef _T2T_TOKEN_HPP_
#define _T2T_TOKEN_HPP_

#include "cursor.hpp"

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

struct MaybeAnchoredToken;

struct AnchoredToken : Token {
  Cursor pos;
  operator MaybeAnchoredToken();
};

struct MaybeAnchoredToken final : AnchoredToken {
  operator bool();
};

}  // namespace t2t

#endif  // _T2T_TOKEN_HPP_
