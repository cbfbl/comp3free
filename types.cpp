#include "types.hpp"

Basictype::Basictype(char* yytext) : lexeme(yytext) {
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

Id::Id(char* yytext) : Basictype(yytext), name(yytext) {}

Bool::Bool(char* yytext) : Basictype(yytext) {
  if (this->getLexeme() == "true") {
    bool_val = true;
  } else if (this->getLexeme() == "false") {
    bool_val = false;
  }
}

Container::Container(char* yytext) : Basictype(yytext) {
  for (Basictype*& basic_type : variables_list) {
    variables_types.push_back(basic_type->getType());
  }
}

vector<Basictype*> Container::getVariables() { return variables_list; }
vector<string>& Container::getTypes() { return variables_types; }