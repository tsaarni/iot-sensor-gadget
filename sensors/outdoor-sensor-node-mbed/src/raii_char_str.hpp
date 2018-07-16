
#pragma once

#include <string>
#include <vector>

struct raii_char_str
{
   raii_char_str(std::string s) : buf(s.c_str(), s.c_str() + s.size() + 1) { };
   operator char*() const { return &buf[0]; };
   size_t size() const { return buf.size(); };
   mutable std::vector<char> buf;
};
