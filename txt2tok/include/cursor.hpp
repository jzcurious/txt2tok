#ifndef _T2T_CURSOR_
#define _T2T_CURSOR_

#include <filesystem>
#include <format>  // IWYU pragma: export
#include <string>

namespace t2t {

struct Cursor final {
  std::filesystem::path path;
  std::size_t nrow;
  std::size_t ncol;

  std::string link() const;
};

}  // namespace t2t

#endif  // _T2T_CURSOR_
