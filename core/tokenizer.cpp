#include <ctype.h>
#include <cstdlib>
#include <tokenizer.hpp>
#include <vector>

#define EXCEPTION_STR(s) "Tokenizer: " s

static const char end_word_chars[] = { ' ', '\n', '\t', (char)-1 };
static const char *symbol_chars = "~!@#$%^&*()-=+[]{}\\|;:,<.>/?"; // The sequence must be in sync with TokenType!!
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
    if (!(isalnum(p_str[i]) || p_str[i] == '_')){
      return false;
    }
  return true;
}


namespace Tokenizer {
std::vector<Token> get_tokens(const char *p_str) {
  const char *begin = p_str; // buffer string begin
  size_t length = 0; // buffer string length
  std::vector<Token> tokens;
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
      tokens.push_back(Token(TokenType::LTR_INTERGER, begin, length));                         \
    else if (is_num == 2)                                                      \
      tokens.push_back(Token(TokenType::LTR_DOUBLE, begin, length));                           \
    else if (!strncmp(begin, "var", length))                                   \
      tokens.push_back(Token(TokenType::KWD_VAR, begin, length));                              \
    else if (!strncmp(begin, "const", length))                                 \
      tokens.push_back(Token(TokenType::KWD_CONST, begin, length));                            \
    else if (!strncmp(begin, "if", length))                                    \
      tokens.push_back(Token(TokenType::KWD_IF, begin, length));                               \
    else if (!strncmp(begin, "else", length))                                  \
      tokens.push_back(Token(TokenType::KWD_ELSE, begin, length));                             \
    else if (!strncmp(begin, "for", length))                                   \
      tokens.push_back(Token(TokenType::KWD_FOR, begin, length));                              \
    else if (!strncmp(begin, "while", length))                                 \
      tokens.push_back(Token(TokenType::KWD_WHILE, begin, length));                            \
    else if (!strncmp(begin, "struct", length))                                \
      tokens.push_back(Token(TokenType::KWD_STRUCT, begin, length));                           \
    else if (is_valid_identifier(begin, length))                               \
      tokens.push_back(Token(TokenType::IDENTIFIER, begin, length));                           \
    else                                                                       \
      throw EXCEPTION_STR("Unexpected word.");                                 \
  }

      if ((symbol_char = strchr(symbol_chars, c)) != NULL) {
        if (length)
            PUSH_BACK_WORD();
        tokens.push_back(Token((TokenType)(symbol_char - symbol_chars), c_ptr, 1));
        length = 0;
        begin = c_ptr + 1;
        continue;
      } else if (strchr(end_word_chars, c) != NULL) {
        if (length)
            PUSH_BACK_WORD();
        length = 0;
        begin = c_ptr + 1;
        continue;
      } else if (strchr(init_str_chars, c) != NULL) {
        if (length)
            PUSH_BACK_WORD();
        length = 1;
        begin = c_ptr; // include init_str char
        init_str_char = c;
        continue;
      }
    } else if (c == init_str_char) {
      tokens.push_back(Token(TokenType::LTR_STRING, begin, length));
      length = 0;
      begin = c_ptr + 1;
      init_str_char = 0;
      continue;
    }
    length++;
#undef PUSH_BACK_WORD
  }

  // Errors
  if (init_str_char)
    throw EXCEPTION_STR("Unterminated string.");
  return tokens;
}
} // namespace Tokenizer
