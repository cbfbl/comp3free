#ifndef TYPES_H
#define TYPES_H

#include <string>
using std::string;

class Basictype {
  string lexeme;
  int global_offset;
  int local_offset;

 public:
  Basictype(char* yytext);
  string getLexeme();
  int getGlobalOffset();
  int getLocalOffset();
  void setGlobalOffset(int global_set);
  void setLocalOffset(int local_set);
};

class Int : public Basictype {
  int lexeme_value;
};

#define YYSTYPE Basictype*

#endif