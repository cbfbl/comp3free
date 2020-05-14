#ifndef HANDLER_H
#define HANDLER_H

#include <iostream>
#include <string>
#include <vector>

#include "hw3_output.hpp"
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

  void insertScope();
  void removeScope();

  void handleStatmentTypeId(Basictype* type, Basictype* id);
  void handleStatmentTypeIdAssignExp(Basictype* type, Basictype* id,
                                     Basictype* exp);
  void handleFunctionDeclartion(Basictype* ret_type, Basictype* id,
                                Basictype* args);
  void handleFormalDeclTypeId(Basictype* type, Basictype* id);

 public:
  void handleRule(int rule_number, vector<Basictype*> params);
  void initialize();
};

#endif