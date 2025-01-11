#ifndef _T2T_SCANNER_HPP_
#define _T2T_SCANNER_HPP_

#include "scantable.hpp"
#include "source.hpp"
#include "token.hpp"
#include <queue>

namespace t2t {

template <TidKind TidT>
class Scanner final {
 private:
  const ScanTable<TidT>& _table;
  std::queue<AnchoredToken> _tokens;

  AnchoredToken _pop_token() {
    auto t = _tokens.front();
    _tokens.pop();
    return t;
  }

 public:
  Scanner(const ScanTable<TidT>& table)
      : _table(table) {}

  MaybeAnchoredToken scan(Source& src) {
    if (not _tokens.empty()) return _pop_token();

    auto line = src.read_line();
    if (not line) return MaybeAnchoredToken{};

    auto span = Span(line.content);
    for (std::size_t ncol = 0; not span.empty(); ncol = span.begin_idx()) {
      AnchoredToken token = {
          _table.match(span), {src.fname, line.num, ncol}
      };
      span.begin_idx(ncol + token.val.size());

      if (token.tid == TidT::unknown) {
        // Messenger::unknown_symbol(token);
        // exit(1);
      }

      _tokens.push(token);
    }

    return _pop_token();
  }
};

}  // namespace t2t

#endif  // _T2T_SCANNER_HPP_
