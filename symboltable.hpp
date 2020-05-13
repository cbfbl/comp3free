#ifndef SYMBOLETABLE_H
#define SYMBOLETABLE_H

#include <vector>

#include "types.hpp"

using std::vector;

class SymbolTable {
  vector<vector<Basictype*>> scopes;

 public:
  void insertScope();
  void insertItem(Basictype* item);
};

#endif