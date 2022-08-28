#include <cstdio>
#include <string>
#include <tokenizer.hpp>
#include <vector>

#include "test.hpp"

using namespace Tokenizer;

static std::string token_to_string(const Token &a) {
  const char *token_types[] = {
      "SYM_TILDE",
      "SYM_BANG",
      "SYM_AT",
      "SYM_SHARP",
      "SYM_DOLLAR",
      "SYM_PERCENT",
      "SYM_POWER",
      "SYM_AMPERSAND",
      "SYM_STAR",
      "SYM_OPEN_PARAN",
      "SYM_CLOSE_PARAN",
      "SYM_MINUS",
      "SYM_EQUAL",
      "SYM_PLUS",
      "SYM_OPEN_SQAURE",
      "SYM_CLOSE_SQUARE",
      "SYM_OPEN_CURLY",
      "SYM_CLOSE_CURLY",
      "SYM_FORWARD_SLASH",
      "SYM_BAR",
      "SYM_SEMICOLON",
      "SYM_COLON",
      "SYM_COMMA",
      "SYM_GT",
      "SYM_PERIOD",
      "SYM_LT",
      "SYM_SLASH",
      "SYM_QUESTION",
      "LTR_STRING",
      "LTR_INTERGER",
      "LTR_DOUBLE",
      "KWD_VAR",
      "KWD_CONST",
      "KWD_IF",
      "KWD_ELSE",
      "KWD_FOR",
      "KWD_WHILE",
      "KWD_STRUCT",
      "KWD_YES",
      "KWD_NO",
      "IDENTIFIER",
  };
  return fmt::format("Token(type={}, length={}, col={}, row={})",
                     token_types[a.type], a.length, a.col, a.row);
}

static bool is_equal(const Token &a, const Token &b) {
  return (a.type == b.type && a.begin == b.begin && a.length == b.length &&
          a.col == b.col && a.row == b.row);
}

static bool is_tokens_equal(const std::vector<Token> &a,
                            const std::vector<Token> &b) {
  size_t size;
  if ((size = a.size()) != b.size()) {
    fmt::print("DEBUG: Size is not the same.\n");
    return false;
  }
  for (size_t i = 0; i < size; i++)
    if (!is_equal(a[i], b[i])) {
      fmt::print("DEBUG: Token is not the same at {}.\n", i);
      fmt::print("DEBUG: Generated Token: {}\n", token_to_string(a[i]));
      return false;
    }
  return true;
}

int main() {
  {
    Test t("Test tokenizer.");

    const char *a_raw = "var hello='hello world';";
    const std::vector<Token> a = get_tokens(a_raw);
    const std::vector<Token> expected_a = {
        Token(KWD_VAR, a_raw, 3, 1, 1), Token(IDENTIFIER, a_raw + 4, 5, 5, 1),
        Token(SYM_EQUAL, a_raw + 9, 1, 10, 1),
        Token(LTR_STRING, a_raw + 10, 13, 11, 1),
        Token(SYM_SEMICOLON, a_raw + 23, 1, 24, 1)};
    t("situation a", is_tokens_equal(a, expected_a));

    const char *b_raw = "for (var i : dead) print(i);\n"
                        "b = yes;";
    const std::vector<Token> b = get_tokens(b_raw);
    const std::vector<Token> expected_b = {
        Token(KWD_FOR, b_raw, 3, 1, 1),
        Token(SYM_OPEN_PARAN, b_raw + 4, 1, 5, 1),
        Token(KWD_VAR, b_raw + 5, 3, 6, 1),
        Token(IDENTIFIER, b_raw + 9, 1, 10, 1),
        Token(SYM_COLON, b_raw + 11, 1, 12, 1),
        Token(IDENTIFIER, b_raw + 13, 4, 14, 1),
        Token(SYM_CLOSE_PARAN, b_raw + 17, 1, 18, 1),
        Token(IDENTIFIER, b_raw + 19, 5, 20, 1),
        Token(SYM_OPEN_PARAN, b_raw + 24, 1, 25, 1),
        Token(IDENTIFIER, b_raw + 25, 1, 26, 1),
        Token(SYM_CLOSE_PARAN, b_raw + 26, 1, 27, 1),
        Token(SYM_SEMICOLON, b_raw + 27, 1, 28, 1),
        Token(IDENTIFIER, b_raw + 29, 1, 1, 2),
        Token(SYM_EQUAL, b_raw + 31, 1, 3, 2),
        Token(KWD_YES, b_raw + 33, 3, 5, 2),
        Token(SYM_SEMICOLON, b_raw + 36, 1, 8, 2)};
    t("situation b", is_tokens_equal(b, expected_b));
  }
}
