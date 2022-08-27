#ifndef _TOKENIZER_HPP_
#define _TOKENIZER_HPP_

#include <string>
#include <vector>

namespace Tokenizer {

enum TokenType {
  // SYMBOLS
  SYM_TILDE,
  SYM_BANG,
  SYM_AT,
  SYM_SHARP,
  SYM_DOLLAR,
  SYM_PERCENT,
  SYM_POWER,
  SYM_AMPERSAND,
  SYM_STAR,
  SYM_OPEN_PARAN,
  SYM_CLOSE_PARAN,
  SYM_MINUS,
  SYM_EQUAL,
  SYM_PLUS,
  SYM_OPEN_SQAURE,
  SYM_CLOSE_SQUARE,
  SYM_OPEN_CURLY,
  SYM_CLOSE_CURLY,
  SYM_FORWARD_SLASH,
  SYM_BAR,
  SYM_SEMICOLON,
  SYM_COLON,
  SYM_COMMA,
  SYM_GT,
  SYM_PERIOD,
  SYM_LT,
  SYM_SLASH,
  SYM_QUESTION,

  // LITERALS
  LTR_STRING,
  LTR_INTERGER,
  LTR_DOUBLE,

  // KEYWORD
  KWD_VAR,
  KWD_CONST,
  KWD_IF,
  KWD_ELSE,
  KWD_FOR,
  KWD_WHILE,
  KWD_STRUCT,

  IDENTIFIER
};

struct Token {
  TokenType type;
  const char *begin;
  size_t length;
  Token(TokenType p_type, const char *p_begin, size_t p_length) : type(p_type), begin(p_begin), length(p_length){}
};

std::vector<Token> get_tokens(const char *p_str);

} // namespace Tokenizer

#endif //_TOKENIZER_HPP_
