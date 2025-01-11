#ifndef _T2T_SCANNER_HPP_
#define _T2T_SCANNER_HPP_

#include "scantable.hpp"
#include "source.hpp"
#include "token.hpp"
#include <queue>

#include <iostream>

namespace t2t {

template <TidKind TidT>
class Scanner final {
 private:
  const ScanTable<TidT>& _table;
  std::queue<Token> _tokens;

  Token _pop_token() {
    auto t = _tokens.front();
    _tokens.pop();
    return t;
  }

 public:
  Scanner(const ScanTable<TidT>& table)
      : _table(table) {}

  MaybeToken scan(Source& src) {
    if (not _tokens.empty()) return _pop_token();

    auto line = src.read_line();
    if (not line) return Token{};

    auto span = Span(line.content);
    for (std::size_t ncol = 0; not span.empty(); ncol = span.begin_idx()) {
      auto token = _table.match(span);
      span.begin_idx(ncol + token.val.size());

      // if (ScanTable::skip.contains(token.tid)) continue;
      // token.cursor = {src.fname, line.num, ncol + 1};

      if (token.tid == TidT::unknown) {
        // TODO: wall
        // Messenger::unknown_symbol(token);
        std::cout << token.val << std::endl;
        exit(1);
      }

      _tokens.push(token);
    }

    return _pop_token();
  }
};

}  // namespace t2t

#endif  // _T2T_SCANNER_HPP_
