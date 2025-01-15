#include "txt2tok/token.hpp"

using namespace t2t;

bool Token::operator==(std::size_t rhs) const {
  return tid == rhs;
}

Token::operator MaybeToken() {
  return MaybeToken{tid, val};
}

MaybeToken::operator bool() {
  return val.size();
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
