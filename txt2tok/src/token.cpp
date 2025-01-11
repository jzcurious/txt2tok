#include "token.hpp"

using namespace t2t;

Token::operator bool() {
  return val.size();
}
