#ifndef _T2T_SCANNTABLE_HPP_
#define _T2T_SCANNTABLE_HPP_

#include <regex>

namespace t2t {

template <class T>
concept TidKind = std::is_enum_v<T> and requires { T::unknown; };

template <TidKind TidT>
struct ScannTable final {
 private:
  std::regex _patterns[TidT::unknown];
  std::string _repr[TidT::unknown];

 public:
  void register_token(TidT tid, std::regex re, const char* repr = "");
  // Token operator[](const Span& span);
  // const char* operator[](const Token& token);
};

}  // namespace t2t

#endif  // _T2T_SCANNTABLE_HPP_
