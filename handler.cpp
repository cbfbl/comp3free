#include "handler.hpp"

Basictype* Handler::handleRule(int rule_number, vector<Basictype*> params) {
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
    case 1:
      finalize();
      break;
    case 4:
      handleFunctionDeclartion(params[0], params[1], params[2]);
      break;
    case 5:
      return handleRettypeType(params[0]);
      break;
    case 6:
      return handleRettypeVoid(params[0]);
      break;
    case 7:
      return handleFormalsEpsilon();
      break;
    case 9:
      return handleFormalDecl(params[0]);
      break;
    case 10:
      return handleFormalDeclFormalList(params[0], params[1]);
      break;
    case 11:
      return handleFormalDeclTypeId(params[0], params[1]);
      break;
    case 15:
      handleStatmentTypeId(params[0], params[1]);
      break;
    case 16:
      handleStatmentTypeIdAssignExp(params[0], params[1], params[2]);
      break;

    default:
      break;
  }
  return NULL;
}

void Handler::initialize() {
  offset_stack.initialize();
  symbol_table.insertScope();
}

void Handler::removeScope() {
  output::endScope();
  vector<Basictype*> last_scope = symbol_table.getLastScopeData();
  for (Basictype* basic_p : last_scope) {
    if (basic_p->getType() == "FUNC") {
      output::printID(basic_p->getLexeme(), basic_p->getGlobalOffset(),
                      ((Function*)basic_p)->getFunctionType());
    } else {
      output::printID(basic_p->getLexeme(), basic_p->getGlobalOffset(),
                      basic_p->getType());
    }
  }
  symbol_table.removeScope();
  offset_stack.removeLastItem();
}

void Handler::insertScope() {
  symbol_table.insertScope();
  offset_stack.duplicateLastItem();
}

void Handler::finalize() { removeScope(); }

Basictype* Handler::handleRettypeType(Basictype* type) { return type; }
Basictype* Handler::handleRettypeVoid(Basictype* void_type) {
  return void_type;
}

void Handler::handleStatmentTypeId(Basictype* type, Basictype* id) {
  if (symbol_table.exists(id->getLexeme())) {
    return;
  }
  id->setGlobalOffset(offset_stack.getTopOffset());
  id->setLocalOffset(symbol_table.getLastScopeSize());
  id->setType(type->getType());
  symbol_table.insertItem(id);
  offset_stack.increaseOffset();
}

void Handler::handleStatmentTypeIdAssignExp(Basictype* type, Basictype* id,
                                            Basictype* exp) {
  if (type->getType() != exp->getType()) {
    return;
  }
  handleStatmentTypeId(type, id);
}

void Handler::handleFunctionDeclartion(Basictype* ret_type, Basictype* id,
                                       Basictype* args) {
  if (symbol_table.exists(((Id*)id)->getName())) {
    return;
  }
  string func_type = output::makeFunctionType(ret_type->getType(),
                                              ((Container*)args)->getTypes());
  Function* func = new Function(((Id*)id)->getName());
  func->setType("FUNC");
  func->setFunctionType(func_type);
  func->setRetType(ret_type->getType());
  func->setGlobalOffset(0);
  int i = -1;
  for (Basictype* basic_type : ((Container*)args)->getVariables()) {
    basic_type->setGlobalOffset(i);
    func->addVariable(basic_type);
    i--;
  }
  symbol_table.insertItem(func);
}

Basictype* Handler::handleFormalDeclTypeId(Basictype* type, Basictype* id) {
  if (symbol_table.exists(((Id*)id)->getName())) {
    cout << "error" << endl;
    exit(0);
  }
  id->setType(type->getType());
  symbol_table.insertItem(id);
  return id;
}

Basictype* Handler::handleFormalDecl(Basictype* formal_decl) {
  Container* con = new Container(formal_decl->getLexeme().c_str());
  return con;
}

Basictype* Handler::handleFormalDeclFormalList(Basictype* formal_decl,
                                               Basictype* formal_list) {
  ((Container*)formal_list)->addVariable(formal_decl);
  return formal_list;
}

Basictype* Handler::handleFormalsEpsilon() { return new Container("epsilon"); }