#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Basictype {
  string lexeme;
  int global_offset;
  int local_offset;
  string type;

 public:
  Basictype(char* yytext);
  string& getLexeme();
  int getGlobalOffset();
  int getLocalOffset();
  void setGlobalOffset(int global_set);
  void setLocalOffset(int local_set);
  string& getType();
  void setType(string type_set);
};

class Num : public Basictype {
  int lexeme_value;

 public:
  Num(char* yytext);
};

class Id : public Basictype {
  string name;

 public:
  Id(char* yytext);
};

class Bool : public Basictype {
  bool bool_val;

 public:
  Bool(char* yytext);
};

class Container : public Basictype {
  vector<Basictype*> variables_list;
  vector<string> variables_types;

 public:
  Container(char* yytext);
  vector<Basictype*> getVariables();
  vector<string>& getTypes();
};

#define YYSTYPE Basictype*

#endif