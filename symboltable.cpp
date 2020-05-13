
#include "symboltable.hpp"

void SymbolTable::insertScope() { scopes.push_back(vector<Basictype*>()); }
void SymbolTable::insertItem(Basictype* item) {
  vector<int> location_vec{item->getGlobalOffset(), item->getLocalOffset()};
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