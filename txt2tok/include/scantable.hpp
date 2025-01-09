#ifndef _T2T_SCANTABLE_HPP_
#define _T2T_SCANTABLE_HPP_

#include "strspan.hpp"
#include "token.hpp"

#include <regex>

namespace t2t {

template <class T>
concept TidKind = std::is_enum_v<T> and requires { T::unknown; };

using Span = strspan::StrSpan<const std::string>;

template <TidKind TidT>
struct ScanTable final {
 private:
  std::regex _patterns[TidT::unknown];
  std::string_view _repr[TidT::unknown];

 public:
  void register_token(TidT tid, std::regex re, const char* repr = "") {
    _patterns[tid] = re;
    _repr[tid] = repr;
  }

  Token operator[](const Span& span) const {
    std::smatch sm;
    std::size_t i = 0;

    for (auto p : _patterns) {
      std::regex_search(span.begin(), span.end(), sm, _patterns[i]);
      if (sm.size()) return Token{i, sm[0]};
      ++i;
    }

    return Token{};
  }

  const char* operator[](const Token& token) const {
    return _repr[token.tid];
  }

  const char* operator[](TidT tid) const {
    return _repr[tid];
  }
};

}  // namespace t2t

#endif  // _T2T_SCANTABLE_HPP_
