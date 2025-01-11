#include "token.hpp"

using namespace t2t;

MaybeToken::operator bool() {
  return val.size();
}

Token::operator MaybeToken() {
  return MaybeToken{tid, val};
}

MaybeAnchoredToken::operator bool() {
  return val.size();
}

AnchoredToken::operator MaybeAnchoredToken() {
  return MaybeAnchoredToken{
      Token{tid, val},
      pos,
  };
}
