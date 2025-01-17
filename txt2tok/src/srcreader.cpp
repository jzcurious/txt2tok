#include "txt2tok/srcreader.hpp"

using namespace t2t;

SourceReader::SourceReader(const fs::path& path_to_file)
    : t2l::Reader::Reader(path_to_file, R"(^\s*$)") {}
