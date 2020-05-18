#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Basictype {
    string lexeme;
    int global_offset;
    int local_offset;
    string type;

public:
    Basictype();

    Basictype(const char *yytext);

    string &getLexeme();

    int getGlobalOffset();

    int getLocalOffset();

    void setGlobalOffset(int global_set);

    void setLocalOffset(int local_set);

    string &getType();

    void setType(string type_set);
};

class Num : public Basictype {
    int lexeme_value;

public:
    Num(const char *yytext);
};

class Id : public Basictype {
    string name;

public:
    Id(const char *yytext);

    string getName();
};

class Bool : public Basictype {
    bool bool_val;

public:
    Bool(const char *yytext);
};

class Container : public Basictype {
    vector<Basictype *> variables_list;
    vector <string> variables_types;

public:
    Container(const char *yytext);

    vector<Basictype *> getVariables();

    void addVariable(Basictype *var);
};

class Function : public Container {
    string ret_type;
    string function_type;

public:
    Function(const char *yytext);

    Function(string yytext);

    void setRetType(string set_ret_type);

    string getFunctionType();

    void setFunctionType(string set_func_type);
};

class String : public Basictype {
public:
    String(const char *yytext);
};

#define YYSTYPE Basictype*

#endif