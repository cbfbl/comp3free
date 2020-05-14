#include "handler.hpp"

void Handler::handleRule(int rule_number, vector<Basictype*> params) {
  int x = 0;
  cout << "Rule number " << rule_number << " was called" << endl;
  for (Basictype* param : params) {
    cout << param->getLexeme() + " ";
  }
  cout << endl;
  return;
}

void Handler::handleStatmentTypeId(Basictype* type, Basictype* id) {
  if (symbol_table.exists(id->getLexeme())) {
    return;
  }
  id->setGlobalOffset(offset_stack.getTopOffset());
  id->setLocalOffset(symbol_table.getTopScopeSize());
  id->setType(type->getLexeme());
  symbol_table.insertItem(id);
  offset_stack.increaseOffset();
}

void Handler::removeScope() {
  symbol_table.removeScope();
  offset_stack.removeLastItem();
}