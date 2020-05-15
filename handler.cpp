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
    case 8:
      return handleFormalsFormalList(params[0]);
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

// rule 1
void Handler::finalize() { removeScope(); }

// rule 4
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
    cout << i << endl;
    basic_type->setGlobalOffset(i);
    func->addVariable(basic_type);
    i--;
  }
  symbol_table.insertItem(func);
}

// rule 5
Basictype* Handler::handleRettypeType(Basictype* type) { return type; }

// rule 6
Basictype* Handler::handleRettypeVoid(Basictype* void_type) {
  return void_type;
}

// rule 7
Basictype* Handler::handleFormalsEpsilon() { return new Container("epsilon"); }

// rule 8
Basictype* Handler::handleFormalsFormalList(Basictype* formals) {
  return formals;
}

// rule 9
Basictype* Handler::handleFormalDecl(Basictype* formal_decl) {
  return formal_decl;
}

// rule 10
Basictype* Handler::handleFormalDeclFormalList(Basictype* formal_decl,
                                               Basictype* formal_list) {
  ((Container*)formal_list)->addVariable(formal_decl);
  return formal_list;
}

// rule 11
Basictype* Handler::handleFormalDeclTypeId(Basictype* type, Basictype* id) {
  if (symbol_table.exists(((Id*)id)->getName())) {
    cout << "error" << endl;
    exit(0);
  }
  Container* con = new Container(id->getLexeme().c_str());
  con->addVariable(con);
  con->setType(type->getType());
  symbol_table.insertItem(con);
  return con;
}

// rule 15
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

// rule 16
void Handler::handleStatmentTypeIdAssignExp(Basictype* type, Basictype* id,
                                            Basictype* exp) {
  if (type->getType() != exp->getType()) {
    return;
  }
  handleStatmentTypeId(type, id);
}