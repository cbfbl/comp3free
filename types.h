#ifndef TYPES_H
#define TYPES_H

#include <string>
using std::string;

class Basictype {
  string lexeme;
};

class Int : public Basictype {
  int lexeme_value;
};

#endif