#include "source.hpp"
#include <regex>

using namespace t2t;

Source::Source(const std::string& fname, const char* skip_regex)
    : _ifstream(fname)
    , _skip_regex(std::regex(skip_regex))
    , fname(fname) {}

Source::Source(const std::string& fname, const std::regex& skip_regex)
    : _ifstream(fname)
    , _skip_regex(skip_regex)
    , fname(fname) {}

MaybeLine Source::read_line() {
  if (eof()) return Line{};

  std::string content;

  for (; not eof(); ++_line_counter) {
    std::getline(_ifstream, content);
    if (not std::regex_match(content, _skip_regex)) break;
  }

  return Line{_line_counter, content};
}

Source::operator bool() {
  return not _ifstream.eof();
}

bool Source::eof() {
  return _ifstream.eof();
}
