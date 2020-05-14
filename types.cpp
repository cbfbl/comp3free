#include "types.hpp"

Basictype::Basictype(const char* yytext) : lexeme(yytext) {
  if (lexeme == "int") {
    setType("INT");
  } else if (lexeme == "bool") {
    setType("BOOL");
  } else if (lexeme == "b" || lexeme == "byte") {
    setType("BYTE");
  } else {
    setType("UNKNOWN");
  }
}

Basictype::Basictype(){};
string& Basictype::getLexeme() { return lexeme; }
int Basictype::getGlobalOffset() { return global_offset; }
int Basictype::getLocalOffset() { return local_offset; }
void Basictype::setGlobalOffset(int global_set) { global_offset = global_set; }
void Basictype::setLocalOffset(int local_set) { local_offset = local_set; }
string& Basictype::getType() { return type; }
void Basictype::setType(string type_set) { type = type_set; }

Num::Num(char* yytext)
    : Basictype(yytext), lexeme_value(std::stoi(string(yytext))) {
  this->setType("INT OR BYTE");
}

Id::Id(const char* yytext) : Basictype(yytext), name(yytext) {}
string Id::getName() { return name; }

Bool::Bool(const char* yytext) : Basictype(yytext) {
  if (this->getLexeme() == "true") {
    bool_val = true;
  } else if (this->getLexeme() == "false") {
    bool_val = false;
  }
}

Container::Container(const char* yytext) : Basictype(yytext) {}
vector<Basictype*> Container::getVariables() { return variables_list; }
vector<string>& Container::getTypes() { return variables_types; }
void Container::addVariable(Basictype* var) {
  variables_list.push_back(var);
  variables_types.push_back(var->getType());
}

Function::Function(const char* yytext) : Container(yytext) {}
Function::Function(string yytext) : Container(yytext.c_str()) {}
void Function::setRetType(string set_ret_type) { ret_type = set_ret_type; }