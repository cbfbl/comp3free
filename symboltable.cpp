
#include "symboltable.hpp"

void SymbolTable::insertScope() { scopes.push_back(vector<Basictype*>()); }

void SymbolTable::removeScope() {
  vector<Basictype*> items = scopes.back();
  for (Basictype* item : items) {
    id_map.erase(item->getLexeme());
  }
  scopes.pop_back();
}

void SymbolTable::insertItem(Basictype* item, bool insert_to_scope) {
  vector<unsigned long> location_vec{scopes.size(), scopes.back().size()};
  id_map.insert({item->getLexeme(), location_vec});
  if (insert_to_scope) {
    scopes.back().push_back(item);
  }
}
bool SymbolTable::exists(string id) {
  if (id_map.end() != id_map.find(id)) {
    return true;
  }
  return false;
}

int SymbolTable::getLastScopeSize() { return scopes.back().size(); }

vector<Basictype*> SymbolTable::getLastScopeData() { return scopes.back(); }