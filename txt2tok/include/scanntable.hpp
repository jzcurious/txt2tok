#ifndef _T2T_SCANNTABLE_HPP_
#define _T2T_SCANNTABLE_HPP_

#include <regex>
#include <vector>

namespace t2t {

struct ScannTable final {
  std::vector<std::regex> _patterns;
  std::vector<std::regex> _repr;

  void register_token(std::regex);
};

}  // namespace t2t

#endif  // _T2T_SCANNTABLE_HPP_
