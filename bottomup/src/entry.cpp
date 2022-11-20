#include "entry.hpp"
#include <iostream>

Type* FLUT_TYPE;
Type* BOOL_TYPE;
Type* INT_TYPE;
Type* CHAR_TYPE;

Type* casting_result(Type* a, Type *b){
  
}

bool are_compatible_types(vector<Type*> a, vector<pair<Type*, string*>> b){

}


Type* modify_type(Type* type, vector<Modifier> modifiers){
  int curr_dim = 0;
  for(auto modifier : modifiers){
    if(modifier.is_idx){
      if(curr_dim == type->array_sizes.size()){
        cerr << "Erro ao acessar dimensao\n"; 
        return nullptr;
      }else curr_dim++;
    }else{
      if(curr_dim != type->array_sizes.size()){
        cerr << "Erro ao acessar atributo\n"; 
        return nullptr;
      }else{
        Type* nxt_type = nullptr;
        for(auto [attr_type, attr_name] : type->attrs){
          if(*attr_name == *modifier.name) nxt_type = attr_type;
        }
        if(nxt_type == nullptr){
          cerr << "Nao existe atributo com esse nome\n";
          return nullptr;
        }else{
          type = nxt_type;
        }
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
    }
  }

  return nullptr;
}

Type* bool_binary_op(OP operand, Type* t){
  if(t == BOOL_TYPE){
    switch(operand){
      case AND:
      case OR:
        return BOOL_TYPE;
    }
  }
  return nullptr;
}

Type* binary_operand(OP operand, Type *t1, Type *t2){
  if(t1 == INT_TYPE){
    return int_binary_op(operand, t2);
  }else if(t1 == BOOL_TYPE){
    return bool_binary_op(operand, t2);
  }else if(t1 == FLUT_TYPE){
    return flut_binary_op(operand, t2);
  }else if(t1 == CHAR_TYPE){
    return nullptr;
  }else if(operand == UNION){
    if(t1->array_sizes == t2->array_sizes && t1->parent == t2->parent) return t1;
  }

  return nullptr;
}