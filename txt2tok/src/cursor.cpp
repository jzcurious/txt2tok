#include "cursor.hpp"

using namespace t2t;

std::string Cursor::link() const {
  return std::format("{}:{}:{}", path.generic_string(), nrow, ncol);
}
