#ifndef _T2T_STBUILDER_HPP_
#define _T2T_STBUILDER_HPP_

#include "scantable.hpp"

namespace t2t {

template <TidKind TidT>
struct ScanTableBuilder final {
 private:
  ScanTable<TidT> _table;

 public:
  ScanTableBuilder& bind_token(TidT tid, std::regex re, const char* repr = "") {
    _table.bind_token(tid, re, repr);
    return *this;
  }

  ScanTableBuilder& bind_token(TidT tid, const char* re, const char* repr = "") {
    return bind_token(tid, std::regex(re), repr);
  }

  const ScanTable<TidT> build() {
    return _table;
  }
};

}  // namespace t2t

#endif  // _T2T_STBUILDER_HPP_
