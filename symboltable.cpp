
#include "symboltable.hpp"

void SymbolTable::insertScope() { scopes.push_back(vector<Basictype*>()); }

void SymbolTable::removeScope() {
  vector<Basictype*> items = scopes.back();
  for (Basictype* item : items) {
    id_map.erase(item->getLexeme());
  }
  scopes.pop_back();
}

void SymbolTable::insertItem(Basictype* item) {
  vector<unsigned long> location_vec{scopes.size(), scopes.back().size()};
  id_map.insert({item->getLexeme(), location_vec});
  scopes.back().push_back(item);
}
bool SymbolTable::exists(string id) {
  if (id_map.end() != id_map.find(id)) {
    return true;
  }
  return false;
}

int SymbolTable::getTopScopeSize() { return scopes.back().size(); }