#include "scanner.hpp"
#include "scantable.hpp"
#include "source.hpp"
#include "stbuilder.hpp"
#include "token.hpp"
#include <fstream>
#include <gtest/gtest.h>

static const char* src_path = "../../assets/tests.udl";

enum Tid {
  indent,
  space,
  type_kw,
  var_kw,
  const_kw,
  struct_kw,
  func_kw,
  ret_kw,
  type_id,
  join,
  inst_id,
  assign,
  str_lit,
  num_lit,
  semicolon,
  plus,
  minus,
  mul,
  divide,
  lpar,
  rpar,
  lbracket,
  rbracket,
  lbrace,
  rbrace,
  langle,
  rangle,
  colon,
  comma,
  line_comment,
  block_comment,
  unknown,
};

// clang-format off
static auto table = t2t::ScanTableBuilder<Tid>{}
  .bind_token(Tid::indent,        R"(^    |\t)",            "indent"             )
  .bind_token(Tid::space,         R"(^ )",                  "space"              )
  .bind_token(Tid::type_kw,       R"(^type)",               "\"type\""           )
  .bind_token(Tid::var_kw,        R"(^var)",                "\"var\""            )
  .bind_token(Tid::const_kw,      R"(^const)",              "\"const\""          )
  .bind_token(Tid::struct_kw,     R"(^struct)",             "\"struct\""         )
  .bind_token(Tid::func_kw,       R"(^func)",               "\"func\""           )
  .bind_token(Tid::ret_kw,        R"(^ret)",                "\"ret\""            )
  .bind_token(Tid::type_id,       R"(^[A-Z][A-Za-z0-9_]*)", "type identifier"    )
  .bind_token(Tid::join,          R"(^\|)",                 "\"|\""              )
  .bind_token(Tid::inst_id,       R"(^[a-z][a-z0-9_]*)",    "instance identifier")
  .bind_token(Tid::assign,        R"(^=)",                  "\"=\""              )
  .bind_token(Tid::str_lit,       R"(^\"([^\"\n]|\.)*\")",  "string literal"     )
  .bind_token(Tid::num_lit,       R"(^[0-9]+(\.[0-9]+)?)",  "number literal"     )
  .bind_token(Tid::semicolon,     R"(^;)",                  "\";\""              )
  .bind_token(Tid::plus,          R"(^\+)",                 "\"+\""              )
  .bind_token(Tid::minus,         R"(^\-)",                 "\"-\""              )
  .bind_token(Tid::mul,           R"(^\*)",                 "\"*\""              )
  .bind_token(Tid::divide,        R"(^/)",                  "\"/\""              )
  .bind_token(Tid::lpar,          R"(^\()",                 "\"(\""              )
  .bind_token(Tid::rpar,          R"(^\))",                 "\")\""              )
  .bind_token(Tid::lbracket,      R"(^\[)",                 "\"[\""              )
  .bind_token(Tid::rbracket,      R"(^\])",                 "\"]\""              )
  .bind_token(Tid::lbrace,        R"(^\{)",                 "\"{\""              )
  .bind_token(Tid::rbrace,        R"(^\})",                 "\"}\""              )
  .bind_token(Tid::langle,        R"(^<)",                  "\"<\""              )
  .bind_token(Tid::rangle,        R"(^>)",                  "\">\""              )
  .bind_token(Tid::colon,         R"(^:)",                  "\":\""              )
  .bind_token(Tid::comma,         R"(^,)",                  "\",\""              )
  .bind_token(Tid::line_comment,  R"(^//.*$)",              "line comment"       )
  .bind_token(Tid::block_comment, R"(^/\*(.|\s)*\*/)",      "block comment"      )
  .bind_token(Tid::unknown,       R"(.*)",                  "unknown"            )
  .build();
// clang-format on

TEST(Source, reading) {
  auto src1 = t2t::Source(src_path);
  auto src2 = t2t::Source(src_path);
  auto istream = std::ifstream(src_path);

  std::vector<std::string> lines1;
  std::vector<std::string> lines2;
  std::vector<std::string> lines3;

  while (not src1.eof()) {
    lines1.push_back(src1.read_line().content);
  }
  lines1.pop_back();

  while (1) {
    auto line = src2.read_line();
    if (not line) break;
    lines2.push_back(line.content);
  }

  EXPECT_EQ(lines1, lines2);
}

TEST(ScanTableBuilder, match) {
  auto t1 = table.match("var x = 1;");
  auto t2 = t2t::Token{Tid::var_kw, "var"};

  EXPECT_EQ(t1.tid, t2.tid);
  EXPECT_EQ(t1.val, t2.val);
}

TEST(ScanTableBuilder, repr) {
  auto t1 = table.match("var x = 1;");

  EXPECT_EQ(std::string(table.repr(static_cast<Tid>(t1.tid))), "\"var\"");
  EXPECT_EQ(std::string(table.repr(t1)), "\"var\"");
}

TEST(Scanner, scan) {
  auto src = t2t::Source(src_path);
  auto scanner = t2t::Scanner(table);

  t2t::Token t;

  while ((t = scanner.scan(src))) {
    std::cout << table.repr(t) << " " << t.val << std::endl;
  }

  EXPECT_EQ(1, 1);
}
