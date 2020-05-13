#ifndef TYPES_H
#define TYPES_H

#include <string>
using std::string;

class Basictype {
  string lexeme;

 public:
  Basictype(char* yytext);
};

class Int : public Basictype {
  int lexeme_value;
};

#endif