#include "source.hpp"
#include <regex>

using namespace t2t;

Source::Source(const std::string& fname)
    : _ifstream(fname)
    , fname(fname) {}

Source::Line Source::read_line() {
  if (eof()) return Line{0, ""};

  std::string content;
  const auto skip_re = std::regex(R"(^\s*$)");

  for (; not eof(); ++_line_counter) {
    std::getline(_ifstream, content);
    if (not std::regex_match(content, skip_re)) break;
  }

  return Line{_line_counter, content};
}

Source::Line::operator bool() {
  return content.size();
}

Source::operator bool() {
  return not _ifstream.eof();
}

bool Source::eof() {
  return _ifstream.eof();
}
