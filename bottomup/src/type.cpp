#include "type.hpp"
#include <iostream>

Type::Type(Type_t _type_t, Type* _parent, bool _io, pair<string,string> _name)
:Entry(TYPE), supports_io(_io), type_t(_type_t), parent(_parent), name(_name){}

bool Type::is_io(){ return supports_io; }

Type* casting_result(Type* a, Type *b){
  
}

bool are_compatible_types(vector<Type*> args, vector<Parameter> parameters){
  if(args.size() != parameters.size()) return false;

  for(int i = 0; i < args.size(); ++i){
    auto type_a = args[i];
    auto [type_b, name, is_ref] = parameters[i];
    if(!type_a->are_equiv(type_b)) return false;
  }
  return true;
}


ArrayType::ArrayType(Type* _parent, int size)
:Type(
  ARRAY, 
  _parent, 
  false, 
  {
    _parent->name.first,
    _parent->name.second + "[" + to_string(size) + "]"
  }
), array_size(size){}

Type::~Type() = default;
ArrayType::~ArrayType() = default;
StructType::~StructType() = default;
PrimitiveType::~PrimitiveType() = default;
AliasType::~AliasType() = default;

bool ArrayType::are_equiv(Type* type){
  if(type->type_t == ARRAY){
    if(array_size == ((ArrayType* )type)->array_size){
      switch(parent->type_t){
        case ARRAY:
          return ((ArrayType*) parent)->are_equiv(type->parent);
        case STRUCT:
          return ((StructType*) parent)->are_equiv(type->parent);
        case ALIAS:
          return ((AliasType*) parent)->are_equiv(type->parent);
        case PRIMITIVE:
          return ((PrimitiveType*) parent)->are_equiv(type->parent);
        default:
          return false;
      }
    } else return false;
  }else return false;
}

Type* ArrayType::access_array(){ return parent; }
Type* ArrayType::access_attr(string *attr_name){ return nullptr; }

StructType::StructType(vector<pair<Type*, string*>> _attrs)
:Type(STRUCT, nullptr, false, {"", ""}), attrs(_attrs){
  name.first = "struct{\n";
  for(auto [typ, attr_name] : attrs){
    name.first += typ->name.first + " " + *attr_name + typ->name.second + ";\n";
  }
  name.first += "}";
}

bool StructType::are_equiv(Type* type){
  if(type->type_t == STRUCT){
    StructType* q_type = (StructType*) type;
    if(q_type->attrs.size() != attrs.size()) return false;
    
    bool equiv = true;
    for(int i = 0; i < attrs.size(); ++i){
      Type* t_a = attrs[i].first;
      Type* t_b = q_type->attrs[i].first;

      switch(t_a->type_t){
        case ARRAY:
          equiv &= ((ArrayType*) t_a)->are_equiv(t_b);
          break;
        case STRUCT:
          equiv &= ((StructType*) t_a)->are_equiv(t_b);
          break;
        case ALIAS:
          equiv &= ((AliasType*) t_a)->are_equiv(t_b);
          break;
        case PRIMITIVE:
          equiv &= ((PrimitiveType*) t_a)->are_equiv(t_b);
          break;
      }
    }
    return equiv;
  }else return false;
}

Type* StructType::access_array(){ return nullptr; }
Type* StructType::access_attr(string *attr_name){
  for(auto [type, name] : attrs){
    if(*name == *attr_name) return type;
  }
  return nullptr;
}

AliasType::AliasType(Type* _parent, string _name)
:Type(
  ALIAS, 
  _parent, 
  _parent->is_io(),
  {"_" + _name, ""}  
){}

bool AliasType::are_equiv(Type* type){
  if(type->type_t == ALIAS){
    return (this == ((AliasType*) type));
  }else return false;
}

Type* AliasType::access_array(){ return parent->access_array(); }
Type* AliasType::access_attr(string *attr_name){ 
  return parent->access_attr(attr_name); 
}

PrimitiveType::PrimitiveType(string _name):
Type(PRIMITIVE, nullptr, true, {_name, ""}){}

bool PrimitiveType::are_equiv(Type* type){
  if(type->type_t == PRIMITIVE){
    return (this == ((PrimitiveType*) type));
  }else return false;
}

Type* PrimitiveType::access_array(){ return nullptr; }
Type* PrimitiveType::access_attr(string *attr_name){ return nullptr; }


Type* binary_operand(OP operand, Type *t1, Type *t2){
  if(t1 == INT_TYPE){
    return int_binary_op(operand, t2);
  }else if(t1 == BOOL_TYPE){
    return bool_binary_op(operand, t2);
  }else if(t1 == FLUT_TYPE){
    return flut_binary_op(operand, t2);
  }else if(operand == UNION){
    if(t1->are_equiv(t2)) return t1;
  }

  return nullptr;
}

Type* modify_type(Type* type, vector<Modifier> modifiers){
  for(auto modifier : modifiers){
    if(modifier.is_idx){
      type = type->access_array();
      if(type == nullptr){
        yyerror("Trying to access index on non-array type");
        exit(1);
      }
    }else{
      type = type->access_attr(modifier.name);
      if(type == nullptr){
        yyerror("Cannot find attribute");
        exit(1);
      }
    }
  }
  return type;
}

Type* unary_operand(OP operand, Type *t){
  switch(operand) {
    case UNARY_PLUS:
    case UNARY_MINUS:
      if(t == INT_TYPE || t == FLUT_TYPE) return t;
      break;
    case NOT:
      if(t == BOOL_TYPE) return t;
      break;
    default:
      return nullptr;
  }
  return nullptr;
}

Type* int_binary_op(OP operand, Type* t){
  if(t == INT_TYPE){
    switch(operand){
      case PLUS:
      case MINUS:
      case TIMES:
      case MODOP:
      case DIV:
      case EXP:
      case UNION:
        return INT_TYPE;
      case EQ:
      case DIF:
      case LEQ:
      case GEQ:
      case LESS:
      case GREATER:
        return BOOL_TYPE;
      default:
        return nullptr;
    }
  }else if(t == FLUT_TYPE){
    switch(operand){
      case PLUS:
      case MINUS:
      case TIMES:
      case DIV:
      case UNION:
        return FLUT_TYPE;
      case EQ:
      case DIF:
      case LEQ:
      case GEQ:
      case LESS:
      case GREATER:
        return BOOL_TYPE;
      default:
        return nullptr;
    }
  }

  return nullptr;
}

Type* flut_binary_op(OP operand, Type* t){
  if(t == INT_TYPE){
    switch(operand){
      case PLUS:
      case MINUS:
      case TIMES:
      case DIV:
      case UNION:
        return FLUT_TYPE;
      case EQ:
      case DIF:
      case LEQ:
      case GEQ:
      case LESS:
      case GREATER:
        return BOOL_TYPE;
      default:
        return nullptr;
    }
  }else if(t == FLUT_TYPE){
    switch(operand){
      case PLUS:
      case MINUS:
      case TIMES:
      case DIV:
      case UNION:
        return FLUT_TYPE;
      case EQ:
      case DIF:
      case LEQ:
      case GEQ:
      case LESS:
      case GREATER:
        return BOOL_TYPE;
      default:
        return nullptr;
    }
  }

  return nullptr;
}

Type* bool_binary_op(OP operand, Type* t){
  if(t == BOOL_TYPE){
    switch(operand){
      case AND:
      case OR:
      case UNION:
      case EQ:
      case DIF:
        return BOOL_TYPE;
      default:
        return nullptr;
    }
  }
  return nullptr;
}

Type* FLUT_TYPE;
Type* BOOL_TYPE;
Type* INT_TYPE;
Type* CHAR_TYPE;