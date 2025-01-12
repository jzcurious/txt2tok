#ifndef _T2T_SCANNER_HPP_
#define _T2T_SCANNER_HPP_

#include "scantable.hpp"
#include "source.hpp"
#include "token.hpp"

#include <iostream>
#include <queue>
#include <type_traits>

namespace t2t {

template <class T>
concept UnknownSymbolHandlerKind = std::is_invocable_v<T, AnchoredToken>;

inline auto default_unknown_symbol_handler = [](const t2t::AnchoredToken& token) {
  std::cout << std::format(
      "Unknown symbol at {}: \"{}\".\n", token.pos.link(), token.val);
};

template <TidKind TidT, UnknownSymbolHandlerKind UnknownSymbolHandlerT>
class Scanner final {
 private:
  const ScanTable<TidT>& _table;
  UnknownSymbolHandlerT _unknown_symbol_handler;
  std::queue<AnchoredToken> _tokens;

  AnchoredToken _pop_token() {
    auto t = _tokens.front();
    _tokens.pop();
    return t;
  }

 public:
  Scanner(const ScanTable<TidT>& table, UnknownSymbolHandlerT unknown_symbol_handler)
      : _table(table)
      , _unknown_symbol_handler(unknown_symbol_handler) {}

  MaybeAnchoredToken scan(Source& src) {
    if (not _tokens.empty()) return _pop_token();

    auto line = src.read_line();
    if (not line) return MaybeAnchoredToken{};

    auto span = Span(line.content);
    for (std::size_t ncol = 0; not span.empty(); ncol = span.begin_idx()) {
      AnchoredToken token = {
          _table.match(span), {src.path, line.num, ncol}
      };
      span.begin_idx(ncol + token.val.size());

      if (token.tid == TidT::unknown) _unknown_symbol_handler(token);
      _tokens.push(token);
    }

    return _pop_token();
  }
};

}  // namespace t2t

#endif  // _T2T_SCANNER_HPP_
