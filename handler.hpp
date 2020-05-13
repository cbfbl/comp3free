#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <string>
#include <vector>

#include "offsetstack.hpp"
#include "symboltable.hpp"
#include "types.hpp"

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Handler {
  SymbolTable symbol_table;
  OffsetStack offset_stack;

  void handleStatmentTypeId(Basictype* type, Basictype* id);

 public:
  void handleRule(int rule_number, vector<Basictype*> params);
};

#endif