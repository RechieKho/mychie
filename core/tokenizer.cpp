#include <cstdlib>
#include <ctype.h>
#include <tokenizer.hpp>
#include <vector>

static const char end_word_chars[] = {' ', '\n', '\t', (char)-1};
static const char *symbol_chars =
    "~!@#$%^&*()-=+[]{}\\|;:,<.>/?"; // The sequence must be in sync with
                                     // TokenType!!
static const char *init_str_chars = "`\"'";

static inline short is_number(const char *p_str, size_t p_length) {
  /* 0: It is not a number.
   * 1: It is an integer.
   * 2: It is a float.*/
  short is_num = 1;
  for (size_t i = 0; i < p_length; i++)
    if (p_str[i] == '.') {
      is_num = 2;
    } else if (!isdigit(p_str[i]))
      return 0;
  return is_num;
}

static inline bool is_valid_identifier(const char *p_str, size_t p_length) {
  if (!isalpha(*p_str))
    return false; // First letter must be an alphabet
  for (size_t i = 0; i < p_length; i++)
    if (!(isalnum(p_str[i]) || p_str[i] == '_')) {
      return false;
    }
  return true;
}

namespace Tokenizer {
std::vector<Token> get_tokens(const char *p_str) {
  // Buffer
  const char *begin = p_str; // buffer string begin
  size_t length = 0;         // buffer string length
  std::vector<Token> tokens;
  size_t b_col = 1;
  size_t b_row = 1;

  // States
  size_t col = 1; // col in raw text
  size_t row = 1; // row in raw text
  char init_str_char = 0;

  for (int i = 0; i < strlen(p_str); i++) {
    const char *c_ptr = p_str + i;
    const char c = *c_ptr;
    if (!init_str_char) {
      const char *symbol_char = NULL;

#define PUSH_BACK_WORD()                                                       \
  {                                                                            \
    short is_num = is_number(begin, length);                                   \
    if (is_num == 1)                                                           \
      tokens.push_back(                                                        \
          Token(TokenType::LTR_INTERGER, begin, length, b_col, b_row));        \
    else if (is_num == 2)                                                      \
      tokens.push_back(                                                        \
          Token(TokenType::LTR_DOUBLE, begin, length, b_col, b_row));          \
    else if (!strncmp(begin, "var", 3) && length == 3)                         \
      tokens.push_back(                                                        \
          Token(TokenType::KWD_VAR, begin, length, b_col, b_row));             \
    else if (!strncmp(begin, "const", 5) && length == 5)                       \
      tokens.push_back(                                                        \
          Token(TokenType::KWD_CONST, begin, length, b_col, b_row));           \
    else if (!strncmp(begin, "if", 2) && length == 2)                          \
      tokens.push_back(Token(TokenType::KWD_IF, begin, length, b_col, b_row)); \
    else if (!strncmp(begin, "else", 4) && length == 4)                        \
      tokens.push_back(                                                        \
          Token(TokenType::KWD_ELSE, begin, length, b_col, b_row));            \
    else if (!strncmp(begin, "for", 3) && length == 3)                         \
      tokens.push_back(                                                        \
          Token(TokenType::KWD_FOR, begin, length, b_col, b_row));             \
    else if (!strncmp(begin, "while", 5) && length == 5)                       \
      tokens.push_back(                                                        \
          Token(TokenType::KWD_WHILE, begin, length, b_col, b_row));           \
    else if (!strncmp(begin, "struct", 6) && length == 6)                      \
      tokens.push_back(                                                        \
          Token(TokenType::KWD_STRUCT, begin, length, b_col, b_row));          \
    else if (!strncmp(begin, "yes", 3) && length == 3)                         \
      tokens.push_back(                                                        \
          Token(TokenType::KWD_YES, begin, length, b_col, b_row));             \
    else if (!strncmp(begin, "no", 2) && length == 2)                          \
      tokens.push_back(Token(TokenType::KWD_NO, begin, length, b_col, b_row)); \
    else if (is_valid_identifier(begin, length))                               \
      tokens.push_back(                                                        \
          Token(TokenType::IDENTIFIER, begin, length, b_col, b_row));          \
    else                                                                       \
      throw TokenizerException(                                                \
          fmt::format("Invalid word at row {}, column {}.", b_row, b_col));    \
  }

      if ((symbol_char = strchr(symbol_chars, c)) != NULL) {
        if (length)
          PUSH_BACK_WORD();
        tokens.push_back(
            Token((TokenType)(symbol_char - symbol_chars), c_ptr, 1, col, row));
        // update states
        col++;
        // update buffer
        length = 0;
        begin = c_ptr + 1;
        b_col = col;
        b_row = row;
        continue;
      } else if (strchr(end_word_chars, c) != NULL) {
        if (length)
          PUSH_BACK_WORD();
        // update states
        if (c == '\n') {
          row++;
          col = 1;
        } else
          col++;
        // update buffer
        length = 0;
        begin = c_ptr + 1;
        b_col = col;
        b_row = row;
        continue;
      } else if (strchr(init_str_chars, c) != NULL) {
        if (length)
          PUSH_BACK_WORD();
        // update buffer
        length = 1;
        begin = c_ptr; // include init_str char
        b_col = col;
        b_row = row;
        // update states
        col++;
        init_str_char = c;
        continue;
      }
    } else if (c == init_str_char) {
      tokens.push_back(
          Token(TokenType::LTR_STRING, begin, length + 1, b_col, b_row));
      // update buffer
      length = 0;
      begin = c_ptr + 1;
      b_col = col;
      b_row = row;
      // update states
      col++;
      init_str_char = 0;
      continue;
    }
    col++;
    length++;
#undef PUSH_BACK_WORD
  }

  // Errors
  if (init_str_char)
    throw TokenizerException(
        fmt::format("Unterminated string at row {}, col {}.", b_row, b_col));
  return tokens;
}
} // namespace Tokenizer
