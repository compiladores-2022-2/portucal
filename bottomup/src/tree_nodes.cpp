#include "tree_nodes.hpp"

#include <iostream>

using namespace node;

SymbleTable symble_table;

Programa::Programa(Definicoes* definicoes, Declaracoes* decs, NovoBloco* novo_bloco)
:Node({definicoes, decs, novo_bloco}){
  exec();
}

Definicoes::Definicoes(ListaDefinicoes* lista):Node({lista}){}

ListaDefinicoes::ListaDefinicoes(Definicao* definicao, ListaDefinicoes* lista)
:Node({definicao, lista}){}

Definicao::Definicao(VariavelConstante *var_const, Literal* literal)
:Node({var_const, literal}){}

VariavelConstante::VariavelConstante(string* _id):id(_id){}

Declaracoes::Declaracoes(ListaDeclaracoes* lista):Node({lista}){}

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

NovoBloco::NovoBloco(Bloco* bloco):Node({bloco}){}

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

DecProc::DecProc(string* _id, Bloco* bloco, ListaParametros* lista_parametros)
:Node({bloco, lista_parametros}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    Entry *entry = new Procedure(((ListaParametros*) children[1])->parameters);
    symble_table.add_entry(id, entry);
  });
}

DecFunc::DecFunc(string* _id, Tipo* tipo, Bloco* bloco, ListaParametros* lista_parametros)
:Node({tipo, bloco, lista_parametros}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    Entry *entry = new Function(
      ((Tipo*) children[0])->type,
      ((ListaParametros*) children[1])->parameters
    );
    symble_table.add_entry(id, entry);
  });
}

ListaParametros::ListaParametros(Parametro* parametro, ListaParametros* lista_parametros)
:Node({parametro, lista_parametros}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    parameters = {((Parametro*) children[0])->parameter};
    if(children[1]){
      for(auto p : ((ListaParametros*) children[1])->parameters)
        parameters.push_back(p);
    }
  });
}

Parametro::Parametro(string* _id, Tipo* tipo, bool _is_ref)
:Node({tipo}), is_ref(_is_ref), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    parameter = Parameter{
      ((Tipo*) children[0])->type,
      id,
      is_ref
    };
  });
}

DecTipo::DecTipo(string* _id, Tipo* tipo)
:Node({tipo}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    Entry *entry = new AliasType(((Tipo*) children[0])->type);
    symble_table.add_entry(id, entry);
  });
}

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

    type = (Type*) entry;
    for(auto size : ((ColchetesOuVazio *)children[0])->sizes){
      type = new ArrayType(type, size);
    }
  });
}

Tipo::Tipo(TipoSimples* tipo_simples, ColchetesOuVazio* colchetes_ou_vazio)
:Node({tipo_simples, colchetes_ou_vazio}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((TipoSimples*) children[0])->type;
    for(auto size : ((ColchetesOuVazio *)children[1])->sizes){
      type = new ArrayType(type, size);
    }
  });
}

Tipo::Tipo(Registro* registro, ColchetesOuVazio* colchetes_ou_vazio)
:Node({registro, colchetes_ou_vazio}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Registro*) children[0])->type;
    for(auto size : ((ColchetesOuVazio *)children[1])->sizes){
      type = new ArrayType(type, size);
    }
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
:Node({expr_const, colchetes_ou_vazio}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    if(((ExprConst*) children[0])->type != INT_TYPE){
      yyerror("Trying to create a type w/ non-int dimension");
      exit(1);
    }

    sizes = {((ExprConst*) children[0])->value.int_};
    for(auto size : ((ColchetesOuVazio *) children[1])->sizes)
      sizes.push_back(size);
  });
}

Registro::Registro(ListaDecAtr* lista_dec_attr)
:Node({lista_dec_attr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = new StructType(
      ((ListaDecAtr*) children[0])->attr_list
    );
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

    vector<Parameter> parameters;
    if(entry->entry_type == FUNCTION){
      parameters = ((Function*) entry)->parameters;
    }else{
      parameters = ((Procedure*) entry)->parameters;
    }

    if((children[0] == nullptr && parameters.size() > 0) ||
      (children[0] != nullptr && !are_compatible_types(lista_expr->type_list, parameters))){
      yyerror("Argument list does not match declared arguments");
      exit(1);
    }
  });
}

Atribuicao::Atribuicao(Variavel* variavel, Expr* expr)
:Node({variavel, expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    Type* union_type = binary_operand(
        UNION,
      ((Variavel*) children[0])->type,
      ((Expr*) children[1])->type
    );

    if(union_type != ((Variavel*) children[0])->type){
      yyerror("Variable and expression type do not match");
      exit(1);
    }
  });
}

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

Controle::Controle(Se* se):Node({se}){}

Controle::Controle(Escolha* escolha):Node({escolha}){}

Se::Se(Expr* expr, Bloco* bloco, Senao* senao):Node({expr, bloco, senao}){}

Senao::Senao(Bloco *bloco):Node({bloco}){}

Senao::Senao(Se* se):Node({se}){}

Escolha::Escolha(Expr* expr, ListaCasos* lista_casos):Node({expr, lista_casos}){}

ListaCasos::ListaCasos(EscolhaPadrao* escolha_padrao):Node({escolha_padrao}){}

ListaCasos::ListaCasos(CasoEscolha* caso_escolha, ListaCasos* lista_casos)
:Node({caso_escolha, lista_casos}){}

EscolhaPadrao::EscolhaPadrao(Comando* comando):Node({comando}){}

CasoEscolha::CasoEscolha(ExprConst* expr_const, Comando* comando)
:Node({expr_const, comando}){}

Repeticao::Repeticao(Enquanto *enquanto):Node({enquanto}){}

Repeticao::Repeticao(FacaEnquanto *faca_enquanto):Node({faca_enquanto}){}

Repeticao::Repeticao(Para *para):Node({para}){}

Enquanto::Enquanto(Expr* expr, Bloco* bloco):Node({expr, bloco}){}

FacaEnquanto::FacaEnquanto(Bloco* bloco, Expr* expr):Node({bloco, expr}){}

Para::Para(Atribuicao* atribuicao1, Expr* expr, Atribuicao* atribuicao2, Bloco* bloco)
:Node({atribuicao1, expr, atribuicao2, bloco}){}

Retorno::Retorno(Expr* expr):Node({expr}){}

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

ModificadorVariavel::ModificadorVariavel(string *id){
  modifier = Modifier(id);
}

ModificadorVariavel::ModificadorVariavel(Expr* expr):Node({expr}){
  exec = function<void()> ([&]() -> void
  {
    if(((Expr*) children[0])->type != INT_TYPE){
      modifier = Modifier();
    }else{
      yyerror("Trying to index array using non-int value");
      exit(1);
    }
  });
}

Literal::Literal(LiteralLogico* literal_logico){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    value.logico = ((LiteralLogico*) children[0])->value;
    type = BOOL_TYPE;
  });
}

Literal::Literal(int int_val){
  type = INT_TYPE;
  value.int_ = int_val;
}

Literal::Literal(char carac_val){
  type = CHAR_TYPE;
  value.carac = carac_val;
}

Literal::Literal(float flut_val){
  type = FLUT_TYPE;
  value.flut = flut_val;
}

Literal::Literal(LiteralArray *literal_array)
:Node({literal_array}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((LiteralArray*) children[0])->type;
  });
}

LiteralLogico::LiteralLogico(bool _value):value(_value){}

LiteralArray::LiteralArray(){} // string

LiteralArray::LiteralArray(ListaLiterais* lista_literais)
:Node({lista_literais}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = new ArrayType(
      ((ListaLiterais*) children[0])->type, 
      ((ListaLiterais*) children[0])->size
    );
  });
}

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

Expr::Expr(Expr* expr1, OP _operand, Expr* expr2)
:Node({expr1, expr2}), operand(_operand){
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

Expr::Expr(OP _operand, Expr* expr):Node({expr}), operand(_operand){
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

Expr::Expr(Tipo *tipo, Expr* expr):Node({tipo, expr}){
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

Expr::Expr(Expr* expr):Node({expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Expr*) children[0])->type;
  });
}

Expr::Expr(FolhaExpr* folha_expr):Node({folha_expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((FolhaExpr*) children[0])->type;
  });
}

FolhaExpr::FolhaExpr(Literal* literal):Node({literal}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Literal*) children[0])->type;
  });
}

FolhaExpr::FolhaExpr(Variavel* variavel):Node({variavel}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Variable*) children[0])->type;
  });
}

FolhaExpr::FolhaExpr(string* _id, ListaExpr* lista_expr, 
  ListaModificadores* lista_modificadores
):Node({lista_expr, lista_modificadores}), id(_id){
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

    auto parameters = ((Function*) entry)->parameters;

    if((children[0] == nullptr && parameters.size() > 0) ||
      (children[0] != nullptr && !are_compatible_types(lista_expr->type_list, parameters))){
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

ExprConst::ExprConst(ExprConst* expr1, OP _operand, ExprConst* expr2)
:Node({expr1, expr2}), operand(_operand){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = binary_operand(
      operand, 
      ((ExprConst*) children[0])->type, 
      ((ExprConst*) children[1])->type
    );
    if(type == nullptr){
      yyerror("Uncompatible operands");
      exit(1);
    }
  });
}

ExprConst::ExprConst(OP _operand, ExprConst* expr)
:Node({expr}), operand(_operand){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = unary_operand(operand, ((ExprConst*) children[0])->type);
    if(type == nullptr){
      yyerror("Uncompatible operand");
      exit(1);
    }
  });
}

ExprConst::ExprConst(Tipo *tipo, ExprConst* expr)
:Node({tipo, expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = casting_result(((Tipo*) children[0])->type, ((ExprConst*) children[1])->type);
    if(type == nullptr){
      yyerror("Uncompatible casting");
      exit(1);
    }
  });
}

ExprConst::ExprConst(ExprConst* expr):Node({expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((ExprConst*) children[0])->type;
  });
}

ExprConst::ExprConst(FolhaExprConst* folha_expr):Node({folha_expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((FolhaExprConst*) children[0])->type;
    value = ((FolhaExprConst*) children[0])->value;
  });
}

FolhaExprConst::FolhaExprConst(Literal* literal):Node({literal}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Literal*) children[0])->type;
    value = ((Literal*) children[0])->value;
  });
}
