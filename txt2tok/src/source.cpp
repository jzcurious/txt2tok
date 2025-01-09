#include "source.hpp"

using namespace t2t;

Source::Source(const std::string& fname)
    : _ifstream(fname)
    , fname(fname) {}

Source::Line Source::read_line() {
  if (eof())
    return Line{
        {fname, 0, 0},
        ""
    };

  std::string content;

  for (content = '\n'; content == "\n" and not _ifstream.eof();) {
    std::getline(_ifstream, content);
    ++_line_counter;
  }

  return Line{
      {fname, _line_counter, 1},
      content
  };
}

Source::Line::operator bool() {
  return cursor.nrow;
}

Source::operator bool() {
  return not _ifstream.eof();
}

bool Source::eof() {
  return _ifstream.eof();
}
