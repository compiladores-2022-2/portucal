#ifndef ENTRY_H
#define ENTRY_H

#include <vector>
#include <utility>
#include <string>
#include "internal_enums.hpp"

void yyerror(const char *msg);

using namespace std;

enum Entry_t{
  CONSTANT,
  VARIABLE,
  FUNCTION,
  PROCEDURE,
  TYPE,
};

class Entry{
public:
  Entry_t entry_type;
  Entry(Entry_t _entry_type):entry_type(_entry_type){}
};

union Value{
  int int_;
  float flut;
  bool logico;
  char carac;
};

class Type;
class Modifier;

class Constant : public Entry{
public:
  Type* type;
  Value value;
  Constant(Type *t, Value _value): Entry(CONSTANT), type(t), value(_value){}
};

class Variable : public Entry{
public:
  Type* type;
  Variable(Type* _type): Entry(VARIABLE), type(_type){}
};

struct Parameter{
  Type* type;
  string* name;
  bool is_ref;
};

class Function : public Entry{
public:
  Type* type;
  vector<Parameter> parameters;

  Function(Type* t, vector<Parameter> _parameters):
  Entry(FUNCTION), type(t), parameters(_parameters){}
};

class Procedure : public Entry{
public:
  vector<Parameter> parameters;

  Procedure(vector<Parameter> _parameters):
  Entry(PROCEDURE), parameters(_parameters){}
};



#endif