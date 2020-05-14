#include "handler.hpp"

void Handler::handleRule(int rule_number, vector<Basictype*> params) {
  int x = 0;
  cout << "Rule number " << rule_number << " was called" << endl;
  if (params.size() > 0) {
    cout << "Params passed : ";
  }
  for (Basictype* param : params) {
    cout << param->getLexeme() + ", ";
  }
  cout << endl;
  switch (rule_number) {
    case 15:
      handleStatmentTypeId(params[0], params[1]);
      break;
    case 16:
      handleStatmentTypeIdAssignExp(params[0], params[1], params[2]);
      break;

    default:
      break;
  }
  return;
}

void Handler::initialize() {
  offset_stack.initialize();
  symbol_table.insertScope();
}

void Handler::removeScope() {
  symbol_table.removeScope();
  offset_stack.removeLastItem();
}

void Handler::insertScope() {
  symbol_table.insertScope();
  offset_stack.duplicateLastItem();
}

void Handler::handleStatmentTypeId(Basictype* type, Basictype* id) {
  if (symbol_table.exists(id->getLexeme())) {
    return;
  }
  id->setGlobalOffset(offset_stack.getTopOffset());
  id->setLocalOffset(symbol_table.getTopScopeSize());
  id->setType(type->getType());
  symbol_table.insertItem(id);
  offset_stack.increaseOffset();
}

void Handler::handleStatmentTypeIdAssignExp(Basictype* type, Basictype* id,
                                            Basictype* exp) {
  if (type->getType() != exp->getType()) {
    return;
  }
}
