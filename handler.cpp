#include "handler.hpp"

Basictype* Handler::handleRule(int rule_number, vector<Basictype*> params) {
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
    case 17:
      return handleIdAssignExp(params[0], params[1]);
      break;
    case 19:
      handleReturnVoid();
      break;
    case 20:
      handleReturnWithType(params[0]);
      break;
    case 39:
      return handleNum(params[0]);
      break;
    case 40:
      return handleNumB(params[0]);
      break;
    case 44:
      return handleNotExp(params[0]);
      break;
    case 45:
      return handleExpAndExp(params[0], params[1]);
      break;
    case 46:
      return handleExpOrExp(params[0], params[1]);
      break;
    case 47:
      return handleExpRelopExp(params[0], params[1]);
      break;
    case 48:
      return handleExpReleqExp(params[0], params[1]);
      break;

    default:
      break;
  }
  return NULL;
}

Handler::Handler() : expected_ret_type("VOID") {}

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

void Handler::setExpectedRetType(string ret_type) {
  expected_ret_type = ret_type;
}

// rule 1
void Handler::finalize() { removeScope(); }

// rule 4
void Handler::handleFunctionDeclartion(Basictype* ret_type, Basictype* id,
                                       Basictype* args) {
  if (symbol_table.exists(((Id*)id)->getName())) {
    return;
  }
  if (expected_ret_type != "VOID") {
    return;
  }
  vector<string> params_types;
  Function* func = new Function(((Id*)id)->getName());
  func->setType("FUNC");
  func->setRetType(ret_type->getType());
  func->setGlobalOffset(0);
  int i = -1;
  for (Basictype* basic_type : ((Container*)args)->getVariables()) {
    basic_type->setGlobalOffset(i);
    func->addVariable(basic_type);
    i--;
    params_types.push_back(basic_type->getType());
  }
  string func_type =
      output::makeFunctionType(ret_type->getType(), params_types);
  func->setFunctionType(func_type);
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

// rule 17

Basictype* Handler::handleIdAssignExp(Basictype* id, Basictype* exp) {
  if (id->getType() != exp->getType()) {
    return new Basictype("ERROR");
  }
  return id;
}

// rule 19
void Handler::handleReturnVoid() {
  if (expected_ret_type != "VOID") {
    return;
  }
}

// rule 20
void Handler::handleReturnWithType(Basictype* ret_type) {
  if (expected_ret_type != ret_type->getType()) {
    return;
  }
  setExpectedRetType("VOID");
}

// rule 39
Basictype* Handler::handleNum(Basictype* num) {
  num->setType("INT");
  return num;
}

// rule 40
Basictype* Handler::handleNumB(Basictype* num) {
  num->setType("BYTE");
  return num;
}

// rule 44
Basictype* Handler::handleNotExp(Basictype* exp) {
  if (exp->getType() != "BOOL") {
    return new Basictype("ERROR");
  }
  return new Bool("true");
}

// rule 45
Basictype* Handler::handleExpAndExp(Basictype* exp_left, Basictype* exp_right) {
  if (exp_left->getType() != "BOOL" || exp_right->getType() != "BOOL") {
    return new Basictype("ERROR");
  }
  return new Bool("true");
}

// rule 46
Basictype* Handler::handleExpOrExp(Basictype* exp_left, Basictype* exp_right) {
  if (exp_left->getType() != "BOOL" || exp_right->getType() != "BOOL") {
    return new Basictype("ERROR");
  }
  return new Bool("true");
}

// rule 47
Basictype* Handler::handleExpRelopExp(Basictype* exp_left,
                                      Basictype* exp_right) {
  if (exp_left->getType() != exp_right->getType()) {
    return new Basictype("ERROR");
  }
  return new Bool("true");
}

// rule 48
Basictype* Handler::handleExpReleqExp(Basictype* exp_left,
                                      Basictype* exp_right) {
  if (exp_left->getType() != exp_right->getType()) {
    return new Basictype("ERROR");
  }
  return new Bool("true");
}