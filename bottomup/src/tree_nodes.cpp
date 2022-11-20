#include "tree_nodes.hpp"

#include <iostream>

using namespace node;

SymbleTable symble_table;

void match_args(){

}

Programa::Programa(Definicoes* definicoes, Declaracoes* decs, NovoBloco* novo_bloco)
:Node({definicoes, decs, novo_bloco}){
  exec();
}

Definicoes::Definicoes(ListaDefinicoes* lista)
:Node({lista}){}

Declaracoes::Declaracoes(ListaDeclaracoes* lista)
:Node({lista}){
}

ListaDeclaracoes::ListaDeclaracoes(Declaracao* declaracao, ListaDeclaracoes* lista)
:Node({declaracao, lista}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    ok = ((Declaracao*) children[0])->ok;
    if(children[1]) ok &= ((ListaDeclaracoes*) children[1])->ok;      
  });
}

Declaracao::Declaracao(DecVar* dec_var)
:Node({dec_var}){}

Declaracao::Declaracao(DecProc* dec_proc)
:Node({dec_proc}){}

Declaracao::Declaracao(DecFunc* dec_func)
:Node({dec_func}){}

Declaracao::Declaracao(DecTipo* dec_tipo)
:Node({dec_tipo}){}

DecTipo::DecTipo(string* _id, Tipo* tipo)
:Node({tipo}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    symble_table.create_type_alias(id, ((Tipo*) children[0])->type);
  });
}

Comando::Comando(COMMAND c):command(c){}

Comando::Comando(Retorno* retorno):Node({retorno}){}

Comando::Comando(NovoBloco* novo_bloco):Node({novo_bloco}){}

Comando::Comando(Controle* controle):Node({controle}){}

Comando::Comando(Repeticao* repeticao):Node({repeticao}){}

Comando::Comando(ListaExpr* lista_expr):Node({lista_expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    for(auto type : ((ListaExpr*) children[0])->type_list){
      if(!type->is_io()){
        yyerror("Expression type does not support printing");
        exit(1);
      }
    }
  });
}

Comando::Comando(Variavel* variavel):Node({variavel}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    if(!((Variavel*) children[0])->type->is_io()){
      yyerror("Variable type does not support reading");
      exit(1);
    }
  });
}

Comando::Comando(Atribuicao* atribuicao):Node({atribuicao}){}

Atribuicao::Atribuicao(Variavel* variavel, Expr* expr)
:Node({variavel, expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    if(binary_operand(
      UNION,
      ((Variavel*) children[0])->type,
      ((Expr*) children[1])->type) != ((Variavel*) children[0])->type){
      yyerror("Variable and expression type do not match");
      exit(1);
    }
  });
}

Variavel::Variavel(string* _id, ListaModificadores* lista_modificadores)
:Node({lista_modificadores}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    Entry* entry = symble_table.get(id);
    if(entry == nullptr){
      yyerror("Undeclared variable");
      exit(1);
    }else if(entry->entry_type != VARIABLE){
      yyerror("Name is not from variable");
      exit(1);
    }

    type = ((Variable*) entry)->type;

    if(children[0]){
      type = modify_type(type, ((ListaModificadores*) children[0])->modifiers);
      if(type == nullptr){
        yyerror("Failed to modify variable type");
        exit(1);
      }
    }
  });
}

Comando::Comando(string* _id, ListaExpr* lista_expr):
Node({lista_expr}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    Entry* entry = symble_table.get(id);
    if(entry == nullptr){
      yyerror("Undeclared function or procedure");
      exit(1);
    }else if(entry->entry_type != FUNCTION && entry->entry_type != PROCEDURE){
      yyerror("Name is not from function nor procedure");
      exit(1);
    }

    vector<std::pair<Type *, std::string *>> arg_list;
    if(entry->entry_type == FUNCTION){
      arg_list = ((Function*) entry)->args;
    }else{
      arg_list = ((Procedure*) entry)->args;
    }

    if((children[0] == nullptr && arg_list.size() > 0) ||
      (children[0] != nullptr && !are_compatible_types(lista_expr->type_list, arg_list))){
      yyerror("Argument list does not match declared arguments");
      exit(1);
    }
  });
}

NovoBloco::NovoBloco(Bloco* bloco)
:Node({bloco}){}

Bloco::Bloco(Declaracoes* declaracoes, ListaComandos* lista_comandos)
:Node({declaracoes, lista_comandos}){
  exec = function<void()> ([&]() -> void
  {
    symble_table.add_scope();
    exec_children();
    symble_table.pop_scope();
  });
}

ListaComandos::ListaComandos(Comando* comando, ListaComandos* lista_comandos)
:Node({comando, lista_comandos}){}

Tipo::Tipo(string *_id, ColchetesOuVazio* colchetes_ou_vazio)
:Node({colchetes_ou_vazio}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    Entry* entry = symble_table.get(id);
    if(entry == nullptr){
      yyerror("Undeclared type");
      exit(1);
    }else if(entry->entry_type != TYPE){
      yyerror("Name is not from type");
      exit(1);
    }

    if(((Type*) entry)->parent == nullptr){
      type = new Type(((ColchetesOuVazio *)children[0])->sizes, ((Type*) entry));
    }else{
      vector<int> new_sizes(((Type*) entry)->array_sizes);
      for(auto size : ((ColchetesOuVazio *)children[0])->sizes){
        new_sizes.push_back(size);
      }

      type = new Type(new_sizes, ((Type*) entry)->parent);
    }
  });
}

Tipo::Tipo(TipoSimples* tipo_simples, ColchetesOuVazio* colchetes_ou_vazio)
:Node({tipo_simples, colchetes_ou_vazio}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    if(((ColchetesOuVazio*) children[1])->sizes.size() == 0){
      type = ((TipoSimples*) children[0])->type;
    }else{
      type = new Type(
        ((ColchetesOuVazio*) children[1])->sizes,
        ((TipoSimples*) children[0])->type
      );
    }
  });
}

Tipo::Tipo(Registro* registro, ColchetesOuVazio* colchetes_ou_vazio)
:Node({registro, colchetes_ou_vazio}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    if(((ColchetesOuVazio*) children[1])->sizes.size()){
      type = new Type(*((Registro*) children[0])->type);
      type->array_sizes = ((ColchetesOuVazio*) children[1])->sizes;
    }else{
      type = ((Registro*) children[0])->type;
    }
  });
}

Registro::Registro(ListaDecAtr* lista_dec_attr)
:Node({lista_dec_attr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = new Type(((ListaDecAtr*) children[0])->attr_list, {});
  });
}

ListaDecAtr::ListaDecAtr(DecAtr* dec_atr, ListaDecAtr* lista_dec_atr)
:Node({dec_atr, lista_dec_atr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    for(auto id : ((DecAtr*) children[0])->id_list){
      attr_list.push_back({((DecAtr*) children[0])->type, id});
    }

    if(children[1]){
      for(auto el : ((ListaDecAtr*) children[1])->attr_list)
        attr_list.push_back(el);
    }
  });
}

DecAtr::DecAtr(ListaIdVars* lista_id_vars, Tipo* tipo)
:Node({lista_id_vars, tipo}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Tipo*) children[1])->type;
    id_list = ((ListaIdVars*) children[0])->id_list;
  });
}

TipoSimples::TipoSimples(PRIMITIVE_TYPE t){
  switch(t) {
    case PINT:
      type = INT_TYPE;
      break;
    case PLOGICO:
      type = BOOL_TYPE;
      break;
    case PFLUT:
      type = FLUT_TYPE;
      break;
    case PCARAC:
      type = CHAR_TYPE;
      break;
  }
}

ColchetesOuVazio::ColchetesOuVazio(){
  exec = function<void()> ([&]() -> void
  {
    sizes = {};
  });
}

ColchetesOuVazio::ColchetesOuVazio(ExprConst* expr_const, ColchetesOuVazio* colchetes_ou_vazio)
:Node({colchetes_ou_vazio}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    if(expr_const->type != INT_TYPE){
      yyerror("Trying to create a type w/ non-int dimension");
      exit(1);
    }

    sizes = {1};
    for(auto size : ((ColchetesOuVazio *) children[0])->sizes)
      sizes.push_back(size);
  });
}

// DEC VAR
DecVar::DecVar(ListaIdVars* lista_id_vars, Tipo* tipo)
:Node({lista_id_vars, tipo}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    for(auto id : ((ListaIdVars *) children[0])->id_list){
      Variable* entry = new Variable(((Tipo *) children[1])->type);
      symble_table.add_entry(id, entry);
    }

  });
}

// LISTA ID VARS

ListaIdVars::ListaIdVars(string* _id, ListaIdVars *lista_id_vars)
:Node({lista_id_vars}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    id_list = {id};
    if(children[0]){
      for(auto id_el : ((ListaIdVars *) children[0])->id_list)
        id_list.push_back(id_el);
    }
  });
}

// LISTA MODIFICADORES
ListaModificadores::ListaModificadores(ModificadorVariavel* modificador, ListaModificadores* lista_modf):
Node({modificador, lista_modf}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    modifiers = {((ModificadorVariavel*) children[0])->modifier};
    if(children[1]){
      for(auto modifier : ((ListaModificadores*) children[1])->modifiers)
        modifiers.push_back(modifier);
    }
  });
}

// MODIFICADOR VARIAVEL
ModificadorVariavel::ModificadorVariavel(string *id){
  modifier = Modifier(id);
}

ModificadorVariavel::ModificadorVariavel(Expr* expr){
  exec = function<void()> ([&]() -> void
  {
    modifier = Modifier();
  });
}

// LISTA EXPR
ListaExpr::ListaExpr(Expr* expr, ListaExpr* lista_expr)
:Node({expr, lista_expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type_list = {((Expr *)children[0])->type};
    if(children[1]){
      for(auto expr_type : ((ListaExpr *)children[1])->type_list)
        type_list.push_back(expr_type);
    }
  });
}

// LITERAL
Literal::Literal(Type *_type){
  type = _type;
}

Literal::Literal(LiteralArray *literal_array)
:Node({literal_array}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((LiteralArray*) children[0])->type;
  });
}

// LITERAL ARRAY
LiteralArray::LiteralArray(){}

LiteralArray::LiteralArray(ListaLiterais* lista_literais)
:Node({lista_literais}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    vector<int> array_sizes = ((ListaLiterais*) children[0])->type->array_sizes;
    array_sizes.push_back(((ListaLiterais*) children[0])->size);

    type = new Type(array_sizes, ((ListaLiterais*) children[0])->type);
  });
}

// LISTA LITERAIS
ListaLiterais::ListaLiterais(Literal* literal, ListaLiterais* lista_literais)
:Node({literal, lista_literais}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    size = 1;
    type = ((Literal*) children[0])->type;

    if(children[1] != nullptr){
      auto union_type = binary_operand(
        UNION, 
        ((Literal*) children[0])->type, 
        ((ListaLiterais*) children[1])->type
      );

      if(union_type != nullptr){
        type = union_type;
        size += ((ListaLiterais*) children[1])->size;
      }else{
        yyerror("Type mismatch for array literal");
        exit(1);
      }
    }
  });
}

// EXPR
Expr::Expr(Expr* expr1, OP operand, Expr* expr2)
:Node({expr1, expr2}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = binary_operand(
      operand, 
      ((Expr*) children[0])->type, 
      ((Expr*) children[1])->type
    );
    if(type == nullptr){
      yyerror("Uncompatible operands");
      exit(1);
    }
  });
}

Expr::Expr(OP _operand, Expr* expr)
:Node({expr}), operand(_operand){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = unary_operand(operand, ((Expr*) children[0])->type);
    if(type == nullptr){
      yyerror("Uncompatible operand");
      exit(1);
    }
  });
}

Expr::Expr(Tipo *tipo, Expr* expr)
:Node({tipo, expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = casting_result(((Tipo*) children[0])->type, ((Expr*) children[1])->type);
    if(type == nullptr){
      yyerror("Uncompatible casting");
      exit(1);
    }
  });
}

Expr::Expr(Expr* expr)
:Node({expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Expr*) children[0])->type;
  });
}

Expr::Expr(FolhaExpr* folha_expr)
:Node({folha_expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((FolhaExpr*) children[0])->type;
  });
}


// FOLHA EXPR
FolhaExpr::FolhaExpr(Literal* literal)
:Node({literal}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Literal*) children[0])->type;
  });
}

FolhaExpr::FolhaExpr(Variavel* variavel)
:Node({variavel}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Variable*) children[0])->type;
  });
}

FolhaExpr::FolhaExpr(string* _id, ListaExpr* lista_expr, 
  ListaModificadores* lista_modificadores
):
Node({lista_expr, lista_modificadores}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    Entry* entry = symble_table.get(id);
    if(entry == nullptr){
      yyerror("Undeclared function");
      exit(1);
    }else if(entry->entry_type != FUNCTION){
      yyerror("Name is not from function");
      exit(1);
    }

    auto arg_list = ((Function*) entry)->args;

    if((children[0] == nullptr && arg_list.size() > 0) ||
      (children[0] != nullptr && !are_compatible_types(lista_expr->type_list, arg_list))){
      yyerror("Argument list does not match declared arguments");
      exit(1);
    }

    type = ((Function*) entry)->type;
    if(children[1]){
      type = modify_type(type, ((ListaModificadores*) children[1])->modifiers);
      if(type == nullptr){
      yyerror("Failed to modify variable type");
      exit(1);
      }
    }
  });  
}