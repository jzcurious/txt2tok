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
 public:
  static constexpr const std::size_t nrows = TidT::unknown + 1;

 private:
  std::regex _patterns[nrows];
  const char* _repr[nrows];

 public:
  void bind_token(TidT tid, std::regex re, const char* repr = "") {
    _patterns[tid] = re;
    _repr[tid] = repr;
  }

  Token match(const Span& span) const {
    std::smatch sm;

    for (std::size_t i = 0; i < nrows; ++i) {
      if (std::regex_search(span.begin(), span.end(), sm, _patterns[i]))
        return Token{i, sm[0]};
    }

    return Token{TidT::unknown};
  }

  Token match(const std::string& str) const {
    return match(Span(str));
  }

  const char* repr(const Token& token) const {
    return _repr[token.tid];
  }

  const char* repr(TidT tid) const {
    return _repr[tid];
  }
};

}  // namespace t2t

#endif  // _T2T_SCANTABLE_HPP_
