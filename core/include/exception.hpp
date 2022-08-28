#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <fmt/core.h>
#include <string>

class Exception {
protected:
  std::string title;
  std::string msg;

  Exception(const std::string &p_msg, const std::string &p_title = "Exception")
      : title(p_title), msg(p_msg) {}

public:
  Exception(const std::string &p_msg) : title("Exception"), msg(p_msg) {}
  std::string to_string() { return fmt::format("{}: {}", title, msg); }
};

#endif //_EXCEPTION_HPP_
