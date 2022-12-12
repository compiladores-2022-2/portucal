#ifndef TYPE_H
#define TYPE_H

#include "entry.hpp"

enum Type_t{
  PRIMITIVE,
  ARRAY,
  STRUCT,
  ALIAS
};

class Type : public Entry{
public:
  bool supports_io;
  Type_t type_t;
  Type* parent;
  pair<string, string> name;

  Type(Type_t _type_t, Type* _parent, bool _io, pair<string,string> _name);
  virtual ~Type();

  bool is_io();

  virtual bool are_equiv(Type* type) = 0;
  virtual Type* access_array() = 0;
  virtual Type* access_attr(string *attr_name) = 0;
};

class ArrayType;
class StructType;
class AliasType;
class PrimitiveType;

class ArrayType : public Type{
public:
  int array_size;
  ArrayType(Type* _parent, int size);
  ~ArrayType();

  bool are_equiv(Type* type);
  Type* access_array();
  Type* access_attr(string *attr_name);
};

class StructType : public Type{
public:
  vector<pair<Type*, string*>> attrs;

  StructType(vector<pair<Type*, string*>> _attrs);
  ~StructType();

  bool are_equiv(Type* type);
  Type* access_array();
  Type* access_attr(string *attr_name);
};

class AliasType : public Type{
public:
  AliasType(Type* _parent, string _name);
  ~AliasType();

  bool are_equiv(Type* type);
  Type* access_array();
  Type* access_attr(string *attr_name);
};

class PrimitiveType : public Type{
public:
  PrimitiveType(string _name);
  ~PrimitiveType();

  bool are_equiv(Type* type);
  Type* access_array();
  Type* access_attr(string *attr_name);
};

extern Type* INT_TYPE;
extern Type* BOOL_TYPE;
extern Type* CHAR_TYPE;
extern Type* FLUT_TYPE;

Type* casting_result(Type* a, Type *b);

bool are_compatible_types(vector<Type*> args, vector<Parameter> parameters);

Type* unary_operand(OP operand, Type *t);
Type* binary_operand(OP operand, Type *t1, Type *t2);

Type* int_binary_op(OP operand, Type* t2);
Type* bool_binary_op(OP operand, Type* t2);
Type* char_binary_op(OP operand, Type* t2);
Type* flut_binary_op(OP operand, Type* t2);

struct Modifier{
  bool is_idx;
  string* name;
  Modifier(string* id = nullptr, bool _is_idx = false): is_idx(_is_idx), name(id){}
};

Type* modify_type(Type* type, vector<Modifier> modifiers);


#endif