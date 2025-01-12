#ifndef _T2T_STBUILDER_HPP_
#define _T2T_STBUILDER_HPP_

#include "scantable.hpp"

namespace t2t {

template <TidKind TidT>
struct ScanTableBuilder final {
 private:
  ScanTable<TidT> _table;
  bool _unknown_symbol_is_redefined;

 public:
  ScanTableBuilder& bind_token(TidT tid, std::regex re, const char* repr = "") {
    _table.bind_token(tid, re, repr);
    if (tid == TidT::unknown) _unknown_symbol_is_redefined = true;
    return *this;
  }

  ScanTableBuilder& bind_token(TidT tid, const char* re, const char* repr = "") {
    return bind_token(tid, std::regex(re), repr);
  }

  const ScanTable<TidT> build() {
    if (not _unknown_symbol_is_redefined)
      _table.bind_token(TidT::unknown, std::regex(R"(^.*)"), "unknown symbol");
    return _table;
  }
};

}  // namespace t2t

#endif  // _T2T_STBUILDER_HPP_
