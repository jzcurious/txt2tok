#include "line.hpp"

using namespace t2t;

MaybeLine::operator bool() {
  return content.size();
}

Line::operator MaybeLine() {
  return MaybeLine{num, content};
}
