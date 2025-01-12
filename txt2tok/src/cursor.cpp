#include "cursor.hpp"

using namespace t2t;

std::string Cursor::link(bool absolute) const {
  auto fname = absolute ? std::filesystem::canonical(path).generic_string()
                        : path.generic_string();
  return std::format("{}:{}:{}", fname, nrow, ncol);
}
