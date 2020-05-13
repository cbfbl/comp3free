#ifndef SYMBOLETABLE_H
#define SYMBOLETABLE_H

#include <unordered_map>
#include <vector>

#include "types.hpp"

using std::unordered_map;
using std::vector;

class SymbolTable {
  vector<vector<Basictype*>> scopes;
  unordered_map<string, vector<int>> id_map;

 public:
  void insertScope();
  void insertItem(Basictype* item);
  bool exists(string id);
};

#endif