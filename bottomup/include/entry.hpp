#ifndef ENTRY_H
#define ENTRY_H

#include "internal_enums.hpp"

void yyerror(const char *msg);

#include <vector>
#include <utility>
#include <string>
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

class Type : public Entry{
  bool supports_io = false;

public: 

  vector<int> array_sizes;
  Type* parent;



  vector<pair<Type*, string*>> attrs;

  bool is_io(){ return supports_io; }

  Type(vector<int> sizes, Type* par, bool _supports_io = false)
  :Entry(TYPE), supports_io(_supports_io), array_sizes(sizes), parent(par), attrs({}){}

  Type(vector<pair<Type*, string*>> _attrs, vector<int> sizes)
  :Entry(TYPE), array_sizes(sizes), parent(nullptr), attrs(_attrs){}
};

class Constant : public Entry{
public:
  Type* type;
  // value

  Constant(Type *t): Entry(CONSTANT), type(t){}
};

class Variable : public Entry{
public:
  Type* type;
  Variable(Type* _type): Entry(VARIABLE), type(_type){}
};

class Function : public Entry{
public:
  Type* type;
  vector<pair<Type*, string*>> args;

  Function(Type* t, vector<pair<Type*, string*>> _args):
  Entry(FUNCTION), type(t), args(_args){}
};

class Procedure : public Entry{
public:
  vector<pair<Type*, string*>> args;

  Procedure(vector<pair<Type*, string*>> _args):
  Entry(PROCEDURE), args(_args){}
};

struct Modifier{
  bool is_idx;
  string* name;

  Modifier(string* id): is_idx(false), name(id){}

  // se nao tem nada, assumo que eh indice numerico
  Modifier(): is_idx(true), name(nullptr){}
};

extern Type* INT_TYPE;
extern Type* BOOL_TYPE;
extern Type* CHAR_TYPE;
extern Type* FLUT_TYPE;

Type* casting_result(Type* a, Type *b);
bool are_compatible_types(vector<Type*> a, vector<pair<Type*, string*>> b);

Type* modify_type(Type* type, vector<Modifier> modifiers);

Type* unary_operand(OP operand, Type *t);
Type* binary_operand(OP operand, Type *t1, Type *t2);


#endif