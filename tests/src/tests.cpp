#include "txt2tok/scanner.hpp"
#include "txt2tok/scantable.hpp"
#include "txt2tok/source.hpp"
#include "txt2tok/stbuilder.hpp"
#include "txt2tok/token.hpp"

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
  .bind_token(Tid::indent,        R"(^    |\t)",            R"(indent)"             )
  .bind_token(Tid::space,         R"(^ )",                  R"(space)"              )
  .bind_token(Tid::type_kw,       R"(^type)",               R"("type")"             )
  .bind_token(Tid::var_kw,        R"(^var)",                R"("var")"              )
  .bind_token(Tid::const_kw,      R"(^const)",              R"("const")"            )
  .bind_token(Tid::struct_kw,     R"(^struct)",             R"("struct")"           )
  .bind_token(Tid::func_kw,       R"(^func)",               R"("func")"             )
  .bind_token(Tid::ret_kw,        R"(^ret)",                R"("ret")"              )
  .bind_token(Tid::type_id,       R"(^[A-Z][A-Za-z0-9_]*)", R"(type identifier)"    )
  .bind_token(Tid::join,          R"(^\|)",                 R"("|")"                )
  .bind_token(Tid::inst_id,       R"(^[a-z][a-z0-9_]*)",    R"(instance identifier)")
  .bind_token(Tid::assign,        R"(^=)",                  R"("=")"                )
  .bind_token(Tid::str_lit,       R"(^\"([^\"\n]|\.)*\")",  R"(string literal)"     )
  .bind_token(Tid::num_lit,       R"(^[0-9]+(\.[0-9]+)?)",  R"(number literal)"     )
  .bind_token(Tid::semicolon,     R"(^;)",                  R"(";")"                )
  .bind_token(Tid::plus,          R"(^\+)",                 R"("+")"                )
  .bind_token(Tid::minus,         R"(^\-)",                 R"("-")"                )
  .bind_token(Tid::mul,           R"(^\*)",                 R"("*")"                )
  .bind_token(Tid::divide,        R"(^/)",                  R"("/")"                )
  .bind_token(Tid::lpar,          R"(^\()",                 R"("(")"                )
  .bind_token(Tid::rpar,          R"(^\))",                 R".()")."               )
  .bind_token(Tid::lbracket,      R"(^\[)",                 R"("[")"                )
  .bind_token(Tid::rbracket,      R"(^\])",                 R"("]")"                )
  .bind_token(Tid::lbrace,        R"(^\{)",                 R"("{")"                )
  .bind_token(Tid::rbrace,        R"(^\})",                 R"("}")"                )
  .bind_token(Tid::langle,        R"(^<)",                  R"("<")"                )
  .bind_token(Tid::rangle,        R"(^>)",                  R"(">")"                )
  .bind_token(Tid::colon,         R"(^:)",                  R"(":")"                )
  .bind_token(Tid::comma,         R"(^,)",                  R"(",")"                )
  .bind_token(Tid::line_comment,  R"(^//.*$)",              R"(line comment)"       )
  .bind_token(Tid::block_comment, R"(^/\*(.|\s)*\*/)",      R"(block comment)"      )
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

  t2t::MaybeAnchoredToken t;

  while ((t = scanner.scan(src))) {
    std::cout << table.repr(t) << " " << t.val << std::endl;
  }

  EXPECT_EQ(1, 1);
}
