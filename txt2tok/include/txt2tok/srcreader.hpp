#ifndef _T2T_SOURCE_HPP_
#define _T2T_SOURCE_HPP_

#include <txt2lines/reader.hpp>

namespace t2t {

namespace fs = std::filesystem;

class SourceReader : public t2l::Reader {
 public:
  SourceReader(const fs::path& path_to_file);
};

}  // namespace t2t

#endif  // _T2T_SOURCE_HPP_
