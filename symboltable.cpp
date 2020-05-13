
#include "symboltable.hpp"

void SymbolTable::insertScope() { scopes.push_back(vector<Basictype*>()); }
void SymbolTable::insertItem(Basictype* item) { scopes.back().push_back(item); }