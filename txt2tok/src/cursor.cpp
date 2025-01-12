#include "cursor.hpp"

using namespace t2t;

std::string Cursor::link() const {
  return std::format("{}:{}:{}", fname, nrow, ncol);
}
