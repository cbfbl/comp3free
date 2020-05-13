#ifndef HANDLER_H
#define HANDLER_H

#include <string>
#include <vector>

#include "offsetstack.hpp"
#include "symboltable.hpp"
#include "types.h"

using std::string;
using std::vector;

class Handler {
  SymbolTable symbol_table;
  OffsetStack offset_stack;

 public:
  void handleRule(int rule_number, vector<Basictype*> params);
};

#endif