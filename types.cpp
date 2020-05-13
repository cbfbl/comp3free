#include "types.hpp"

Basictype::Basictype(char* yytext) : lexeme(yytext) {}

string Basictype::getLexeme() { return lexeme; }

int Basictype::getGlobalOffset() { return global_offset; }

int Basictype::getLocalOffset() { return local_offset; }

void Basictype::setGlobalOffset(int global_set) { global_offset = global_set; }

void Basictype::setLocalOffset(int local_set) { local_offset = local_set; }

string Basictype::getType() { return type; }

void Basictype::setType(string type_set) { type = type_set; }