#include "tree_nodes.hpp"
#include "code_gen.hpp"

#include <iostream>

using namespace node;

SymbleTable symble_table;

Programa::Programa(Definicoes* definicoes, Declaracoes* decs, NovoBloco* novo_bloco)
:Node({definicoes, decs, novo_bloco}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = code_gen::concat_code({
      "#include<stdio.h>\n\n",
      "enum{false, true} bool;\n",
      children[0]->code,
      children[1]->code,
      "\n",
      code_gen::print_vars(),
      "\n",
      "int main()",
      children[2]->code,
      "\n\n",
    });
  });
  exec();
  cout << code;
}

Definicoes::Definicoes(ListaDefinicoes* lista):Node({lista}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    if(children[0]) code = children[0]->code + "\n";
  });
}

ListaDefinicoes::ListaDefinicoes(Definicao* definicao, ListaDefinicoes* lista)
:Node({definicao, lista}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
    if(children[1]) 
      code = code_gen::concat_code({code, children[1]->code});
  }); 
}

Definicao::Definicao(VariavelConstante *var_const, Literal* literal)
:Node({var_const, literal}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    Entry* entry = new Constant(
      ((Literal*) children[1])->type,
      ((Literal*) children[1])->value
    );

    symble_table.add_entry(
      ((VariavelConstante*) children[0])->id,
      entry
    );

    code = code_gen::concat_code({
      "#define ", children[0]->code, " ", children[1]->code, "\n"
    });
  });
}

VariavelConstante::VariavelConstante(string* _id):id(_id){
  code = *id;
}

Declaracoes::Declaracoes(ListaDeclaracoes* lista):Node({lista}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    if(children[0]) code = children[0]->code;
  }); 
}

ListaDeclaracoes::ListaDeclaracoes(Declaracao* declaracao, ListaDeclaracoes* lista)
:Node({declaracao, lista}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
    if(children[1]) 
      code = code_gen::concat_code({code, children[1]->code});
  }); 
}

Declaracao::Declaracao(DecVar* dec_var)
:Node({dec_var}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
  }); 
}

Declaracao::Declaracao(DecProc* dec_proc)
:Node({dec_proc}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
  }); 
}

Declaracao::Declaracao(DecFunc* dec_func)
:Node({dec_func}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
  }); 
}

Declaracao::Declaracao(DecTipo* dec_tipo)
:Node({dec_tipo}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
  }); 
}

NovoBloco::NovoBloco(Bloco* bloco):Node({bloco}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
  });
}

Bloco::Bloco(Declaracoes* declaracoes, ListaComandos* lista_comandos)
:Node({declaracoes, lista_comandos}){
  exec = function<void()> ([&]() -> void
  {
    symble_table.add_scope();
    exec_children();
    symble_table.pop_scope();

    code = code_gen::concat_code({
      "{\n",
      children[0]->code,
      children[1]->code,
      "}\n"
    });
  });
}

ListaComandos::ListaComandos(Comando* comando, ListaComandos* lista_comandos)
:Node({comando, lista_comandos}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = code_gen::get_next_label();
    exec_children();
    
    code = code_gen::concat_code({
      children[0]->code,
      code_gen::gen_label(children[0]->next), ":;\n",
    });

    if(children[1]){
      code = code_gen::concat_code({code, children[1]->code});
    }
  });
}

DecVar::DecVar(ListaIdVars* lista_id_vars, Tipo* tipo)
:Node({lista_id_vars, tipo}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();


    for(auto id : ((ListaIdVars *) children[0])->id_list){      
      Variable* entry = new Variable(((Tipo *) children[1])->type);
      symble_table.add_entry(id, entry);
    }

    code = ((Tipo *) children[1])->type->name.first + " ";
    for(auto id : ((ListaIdVars *) children[0])->id_list){
      code += *id + ((Tipo *) children[1])->type->name.second + ", ";
    }
    code.pop_back(); code.pop_back();
    code += ";\n";
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

    if(children[0]){
      code = code_gen::concat_code({
        *id,
        ", ",
        children[0]->code
      });
    }else{
      code = *id;
    }
  });
}

DecProc::DecProc(string* _id, Bloco* bloco, ListaParametros* lista_parametros)
:Node({bloco, lista_parametros}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    children[1]->exec();

    Entry *entry = new Procedure(((ListaParametros*) children[1])->parameters);
    symble_table.add_entry(id, entry);

    symble_table.add_scope();
    for(auto [type, name, is_ref] : ((ListaParametros*) children[1])->parameters){
      Entry *entry = new Variable(type);
      symble_table.add_entry(name, entry);
    }
    children[0]->exec_children();
    symble_table.pop_scope();
  });
}

DecFunc::DecFunc(string* _id, Tipo* tipo, Bloco* bloco, ListaParametros* lista_parametros)
:Node({tipo, bloco, lista_parametros}), id(_id){
  exec = function<void()> ([&]() -> void
  {
    children[0]->exec();
    children[2]->exec();

    Entry *entry = new Function(
      ((Tipo*) children[0])->type,
      ((ListaParametros*) children[2])->parameters
    );
    symble_table.add_entry(id, entry);

    symble_table.add_scope();
    for(auto [type, name, is_ref] : ((ListaParametros*) children[2])->parameters){
      Entry *entry = new Variable(type);
      symble_table.add_entry(name, entry);
    }
    children[1]->exec_children();
    symble_table.pop_scope();
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
    Entry *entry = new AliasType(((Tipo*) children[0])->type, *id);
    symble_table.add_entry(id, entry);

    // typedef unsigned char BYTE;
    code = code_gen::concat_code({
      "typedef ", children[0]->code, " _", *id, ";\n"
    });
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


    code = code_gen::concat_code({
      *id,
      children[0]->code
    });
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


    code = code_gen::concat_code({
      children[0]->code,
      children[1]->code
    });
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

    code = code_gen::concat_code({
      children[0]->code,
      children[1]->code
    });
  });
}

TipoSimples::TipoSimples(PRIMITIVE_TYPE t){
  switch(t) {
    case PINT:
      type = INT_TYPE;
      code = "int";
      break;
    case PLOGICO:
      type = BOOL_TYPE;
      code = "bool";
      break;
    case PFLUT:
      type = FLUT_TYPE;
      code = "float";
      break;
    case PCARAC:
      type = CHAR_TYPE;
      code = "char";
      break;
  }
}

ColchetesOuVazio::ColchetesOuVazio(){
  exec = function<void()> ([&]() -> void
  {
    sizes = {};
    code = "";
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

    code = code_gen::concat_code({
      "[",
      children[0]->code,
      "]",
      children[1]->code
    });
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

    code = code_gen::concat_code({
      "struct{\n",
      children[0]->code,
      "}"
    });
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

    if(children[1]){
      code = code_gen::concat_code({
        children[0]->code,
        ",\n",
        children[1]->code
      });
    }else{
      code = children[0]->code;
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

    code = ((Tipo *) children[1])->type->name.first + " ";
    for(auto id : ((ListaIdVars *) children[0])->id_list){
      code += *id + ((Tipo *) children[1])->type->name.second + ", ";
    }
    code.pop_back(); code.pop_back();
    code += ";\n";
  });
}

Comando::Comando(COMMAND c):command(c){
  exec = function<void()> ([&]() -> void
  {
    if(command == EPARE){
      if(code_gen::loop_goto.empty()){
        yyerror("Cannot have break here");
        exit(1);
      }
      int nxt_loop = code_gen::loop_goto.top().second;
      code = "goto " + code_gen::gen_label(nxt_loop) + ";\n";
    }else{
      if(code_gen::loop_goto.empty() || code_gen::loop_goto.top().first == -1){
        yyerror("Cannot have continue outside a loop");
        exit(1);
      }
      int start_loop = code_gen::loop_goto.top().first;
      code = "goto " + code_gen::gen_label(start_loop) + ";\n";
    }
  });
}

Comando::Comando(Retorno* retorno):Node({retorno}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
  });
}

Comando::Comando(NovoBloco* novo_bloco):Node({novo_bloco}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
  });
}

Comando::Comando(Controle* controle):Node({controle}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = next;
    exec_children();
    code = children[0]->code;
  });
}

Comando::Comando(Repeticao* repeticao):Node({repeticao}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = next;
    exec_children();
    code = children[0]->code;
  });
}

// IMPRIMA
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

    code = children[0]->code;
    code += "printf(\"";
    for(int i = 0; i < ((ListaExpr*) children[0])->type_list.size(); ++i){
      auto type = ((ListaExpr*) children[0])->type_list[i];
      if(type == INT_TYPE) code += "%d";
      else if(type == FLUT_TYPE) code += "%f";
      else if(type == CHAR_TYPE) code += "%c";

      // if(i + 1 < ((ListaExpr*) children[0])->type_list.size()){
      //   code += " ";
      // }
    }
    code += "\", ";

    for(int i = 0; i < ((ListaExpr*) children[0])->var_list.size(); ++i){
      code += ((ListaExpr*) children[0])->var_list[i];
      if(i + 1 < ((ListaExpr*) children[0])->var_list.size())
        code += ", ";
    }
    code += ");\n";
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

    code = children[0]->code;
    code += "scanf(\"";

    if(((Variavel*) children[0])->type == INT_TYPE){
      code += "%d";
    }else if(((Variavel*) children[0])->type == FLUT_TYPE){
      code += "%f";
    }else if(((Variavel*) children[0])->type == CHAR_TYPE){
      code += "%c";
    }else{

    }
    
    code = code_gen::concat_code({
      code,
      "\", &",
      ((Variavel*)children[0])->var,
      ");\n"
    });
  });
}

Comando::Comando(Atribuicao* atribuicao):Node({atribuicao}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
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

    vector<Parameter> parameters;
    if(entry->entry_type == FUNCTION){
      parameters = ((Function*) entry)->parameters;
    }else{
      parameters = ((Procedure*) entry)->parameters;
    }

    if((children[0] == nullptr && parameters.size() > 0) ||
      (children[0] != nullptr && !are_compatible_types(((ListaExpr*) children[0])->type_list, parameters))){
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

    code = code_gen::concat_code({
      children[1]->code, 
      children[0]->code,
      ((Variavel*) children[0])->var,
      " = ",
      ((Expr*) children[1])->var,
      ";\n"
    });
  });
}

ListaExpr::ListaExpr(Expr* expr, ListaExpr* lista_expr)
:Node({expr, lista_expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type_list = {((Expr *)children[0])->type};
    var_list = {((Expr *)children[0])->var};
    code = children[0]->code;

    if(children[1]){
      for(auto expr_type : ((ListaExpr *)children[1])->type_list)
        type_list.push_back(expr_type);
      for(auto expr_var : ((ListaExpr *)children[1])->var_list)
        var_list.push_back(expr_var);

      code = code_gen::concat_code({code, children[1]->code});
    }
  });
}

Controle::Controle(Se* se):Node({se}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = next;
    exec_children();
    code = children[0]->code;
  }); 
}

Controle::Controle(Escolha* escolha):Node({escolha}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = next;
    exec_children();
    code = children[0]->code;
  }); 
}

Se::Se(Expr* expr, Bloco* bloco, Senao* senao):Node({expr, bloco, senao}){
  exec = function<void()> ([&]() -> void
  {

    ((Expr*) children[0])->l_true = code_gen::get_next_label();
    children[1]->next = next;
    if(children[2]){ // se tem senao
      children[2]->next = next;
      ((Expr*) children[0])->l_false = code_gen::get_next_label();
    }else{
      ((Expr*) children[0])->l_false = next;
    }
    
    exec_children();

    if(((Expr*) children[0])->type != BOOL_TYPE){
      yyerror("Expression type in conditional is not boolean");
      exit(1);
    }

    code = code_gen::concat_code({
      children[0]->code,
      code_gen::gen_label(((Expr*) children[0])->l_true), ":;\n",
      children[1]->code
    });

    if(children[2]){ // se tem senao
      code = code_gen::concat_code({
        code,
        "goto ", code_gen::gen_label(next), ";\n",
        code_gen::gen_label(((Expr*) children[0])->l_false), ":;\n",
        children[2]->code
      }); 
    }
  });
}

Senao::Senao(Bloco *bloco):Node({bloco}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = next;
    exec_children();
    code = children[0]->code;
  }); 
}

Senao::Senao(Se* se):Node({se}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = next;
    exec_children();
    code = children[0]->code;
  }); 
}

Escolha::Escolha(Expr* expr, ListaCasos* lista_casos):Node({expr, lista_casos}){
  exec = function<void()> ([&]() -> void
  {
    int before_guard = -1;
    if(!code_gen::loop_goto.empty())
      before_guard = code_gen::loop_goto.top().first;
    
    code_gen::loop_goto.push({before_guard, next});
    children[0]->exec();
    ((ListaCasos*) children[1])->switch_nxt = next;
    ((ListaCasos*) children[1])->guard_var = ((Expr*) children[0])->var;
    children[1]->exec();

    code_gen::loop_goto.pop();

    code = code_gen::concat_code({
      children[0]->code,
      children[1]->code      
    });
  });
}

ListaCasos::ListaCasos(EscolhaPadrao* escolha_padrao):Node({escolha_padrao}){
  exec = function<void()> ([&]() -> void
  {
    ((EscolhaPadrao*) children[0])->switch_nxt = switch_nxt;
    exec_children();
    code = children[0]->code;
  });
}

ListaCasos::ListaCasos(CasoEscolha* caso_escolha, ListaCasos* lista_casos)
:Node({caso_escolha, lista_casos}){
  exec = function<void()> ([&]() -> void
  {
    int case_nxt = code_gen::get_next_label();

    if(children[1]){
      ((ListaCasos*) children[1])->switch_nxt = switch_nxt;
      ((ListaCasos*) children[1])->guard_var = guard_var;
    }

    ((CasoEscolha*) children[0])->switch_nxt = switch_nxt;
    ((CasoEscolha*) children[0])->guard_var = guard_var;
    ((CasoEscolha*) children[0])->case_nxt = case_nxt;

    exec_children();

    code = code_gen::concat_code({
      children[0]->code,
      code_gen::gen_label(case_nxt), ":;\n"
    });

    if(children[1]){
      code = code_gen::concat_code({code, children[1]->code});
    }
  });
}

EscolhaPadrao::EscolhaPadrao(Comando* comando):Node({comando}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    code = children[0]->code;
  });
}

CasoEscolha::CasoEscolha(Expr* expr_const, Comando* comando)
:Node({expr_const, comando}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    // checar se tipo ta safe
   
    code = code_gen::concat_code({
      children[0]->code,
      "if(!(", ((Expr*) children[0])->var, " == ", guard_var, ")) goto ", code_gen::gen_label(case_nxt), ";\n",
      children[1]->code
    });
  });
}

Repeticao::Repeticao(Enquanto *enquanto):Node({enquanto}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = next;
    exec_children();
    code = children[0]->code;
  });
}

Repeticao::Repeticao(FacaEnquanto *faca_enquanto):Node({faca_enquanto}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = next;
    exec_children();
    code = children[0]->code;
  });
}

Repeticao::Repeticao(Para *para):Node({para}){
  exec = function<void()> ([&]() -> void
  {
    children[0]->next = next;
    exec_children();
    code = children[0]->code;
  });
}

Enquanto::Enquanto(Expr* expr, Bloco* bloco):Node({expr, bloco}){
  exec = function<void()> ([&]() -> void
  {
    int before_guard = code_gen::get_next_label();
    int inside_loop = code_gen::get_next_label();

    ((Expr*) children[0])->l_false = next;
    ((Expr*) children[0])->l_true = inside_loop;

    code_gen::loop_goto.push({before_guard, next});
    exec_children();
    code_gen::loop_goto.pop();

    if(((Expr*) children[0])->type != BOOL_TYPE){
      yyerror("Expression type in loop guard is not boolean");
      exit(1);
    }

    code = code_gen::concat_code({
      code_gen::gen_label(before_guard), ":;\n",
      children[0]->code,
      code_gen::gen_label(inside_loop), ":;\n",
      // "if(!(", ((Expr*) children[0])->var, ")) goto ", code_gen::gen_label(next), ";\n",
      children[1]->code,
      "goto ", code_gen::gen_label(before_guard), ";\n",
    });
  });
}

// do while
FacaEnquanto::FacaEnquanto(Bloco* bloco, Expr* expr):Node({bloco, expr}){
  exec = function<void()> ([&]() -> void
  {
    int inside_loop = code_gen::get_next_label();

    ((Expr*) children[1])->l_false = next;
    ((Expr*) children[1])->l_true = inside_loop;

    code_gen::loop_goto.push({inside_loop, next});
    exec_children();
    code_gen::loop_goto.pop();

    if(((Expr*) children[1])->type != BOOL_TYPE){
      yyerror("Expression type in loop guard is not boolean");
      exit(1);
    }

    code = code_gen::concat_code({
      code_gen::gen_label(inside_loop), ":;\n",
      children[0]->code,
      children[1]->code
    });
  });
}

Para::Para(Atribuicao* atribuicao1, Expr* expr, Atribuicao* atribuicao2, Bloco* bloco)
:Node({atribuicao1, expr, atribuicao2, bloco}){
  exec = function<void()> ([&]() -> void
  {
    int before_guard = code_gen::get_next_label();
    int inside_loop = code_gen::get_next_label();

    ((Expr*) children[1])->l_false = next;
    ((Expr*) children[1])->l_true = inside_loop;

    code_gen::loop_goto.push({before_guard, next});
    exec_children();
    code_gen::loop_goto.pop();

    if(((Expr*) children[1])->type != BOOL_TYPE){
      yyerror("Expression type in loop guard is not boolean");
      exit(1);
    }

    code = code_gen::concat_code({
      children[0]->code, // TEM ;?
      code_gen::gen_label(before_guard), ":;\n",
      children[1]->code,
      code_gen::gen_label(inside_loop), ":;\n",
      children[3]->code,
      children[2]->code,
      "goto ", code_gen::gen_label(before_guard), ";\n",
    });
  });
}

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

    var = *id;

    if(children[0]){
      code = children[0]->code;

      type = modify_type(type, ((ListaModificadores*) children[0])->modifiers);
      if(type == nullptr){
        yyerror("Failed to modify variable type");
        exit(1);
      }

      for(auto modifier : ((ListaModificadores*) children[0])->modifiers){
        if(modifier.is_idx){
          var += "[" + *modifier.name + "]";
        }else{
          var += "." + *modifier.name;
        }
      }
    }
  });
}

ListaModificadores::ListaModificadores(ModificadorVariavel* modificador, ListaModificadores* lista_modf):
Node({modificador, lista_modf}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();

    code = children[0]->code;
    modifiers = {((ModificadorVariavel*) children[0])->modifier};
    if(children[1]){
      code = code_gen::concat_code({code, children[1]->code});

      for(auto modifier : ((ListaModificadores*) children[1])->modifiers)
        modifiers.push_back(modifier);
    }
  });
}

ModificadorVariavel::ModificadorVariavel(string *id){
  modifier = Modifier(id, false);
}

ModificadorVariavel::ModificadorVariavel(Expr* expr):Node({expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    if(((Expr*) children[0])->type == INT_TYPE){
      modifier = Modifier(&((Expr*) children[0])->var, true);
      code = children[0]->code;
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
  code = to_string(int_val);
}

Literal::Literal(char carac_val){
  type = CHAR_TYPE;
  value.carac = carac_val;
  if(carac_val == '\n'){
    code = "\'  \'";
    code[1] = '\\';    
    code[2] = 'n';    
  }else{
    code = "\' \'";
    code[1] = carac_val;
  }
}

Literal::Literal(float flut_val){
  type = FLUT_TYPE;
  value.flut = flut_val;
  code = to_string(flut_val);
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
    int true_case = l_true, false_case = l_false;
    int nxt_op = -1;
   
    if(operand == OR || operand == AND){
      nxt_op = code_gen::get_next_label();
      if(true_case == -1 && false_case == -1){
        true_case = code_gen::get_next_label();
        false_case = code_gen::get_next_label();
      }

      if(operand == OR){
        ((Expr*) children[0])->l_true = true_case;
        ((Expr*) children[0])->l_false = nxt_op;
        ((Expr*) children[1])->l_true = true_case;
        ((Expr*) children[1])->l_false = false_case;
      }else{ // AND
        ((Expr*) children[0])->l_true = nxt_op;
        ((Expr*) children[0])->l_false = false_case;   
        ((Expr*) children[1])->l_true = true_case;
        ((Expr*) children[1])->l_false = false_case;
      }
    }else{
      ((Expr*) children[0])->l_true = ((Expr*) children[0])->l_false = -1; 
      ((Expr*) children[1])->l_true = ((Expr*) children[1])->l_false = -1; 
    }

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

    if(nxt_op == -1){
      code = code_gen::concat_code({
        children[0]->code,
        children[1]->code
      });
    }else{
      code = code_gen::concat_code({
        children[0]->code,
        code_gen::gen_label(nxt_op), ":", "\n",
        children[1]->code
      });
    }

    if(operand == OR || operand == AND){
      if(l_true == -1 && l_false == -1){
        var = code_gen::gen_var(type->name);

        int next_attr = code_gen::get_next_label();
        code = code_gen::concat_code({
          code,
          code_gen::gen_label(true_case), ":", "\n",
          var, " = true;\n",
          "goto ", code_gen::gen_label(next_attr), ";\n", 
          code_gen::gen_label(false_case), ":", "\n",
          var, " = false;\n",
          code_gen::gen_label(next_attr), ":", "\n",
        });
      }else{
        // vou ter gotozado pra algum gancho
      }
    }else if(code_gen::is_op_rel(operand)){
      if(l_true == -1 && l_false == -1){
        var = code_gen::gen_var(type->name);

        code = code_gen::concat_code({
          code,
          var, " = ",
          ((Expr*) children[0])->var, " ", code_gen::get_op_name(operand), " ", ((Expr*) children[1])->var,
          ";\n"
        });
      }else{
        code = code_gen::concat_code({
          code,
          "if(", 
          ((Expr*) children[0])->var, " ", code_gen::get_op_name(operand), " ", ((Expr*) children[1])->var
          ,") goto ", code_gen::gen_label(l_true), ";\n",
          "goto ", code_gen::gen_label(l_false), ";\n"
        });
      }
    }else{
      var = code_gen::gen_var(type->name);
      code = code_gen::concat_code({
        code,
        var,
        " = ",
        ((Expr*) children[0])->var,
        " ",
        code_gen::get_op_name(operand),
        " ",
        ((Expr*) children[1])->var,
        ";\n"
      });
    }

  });
}

Expr::Expr(OP _operand, Expr* expr):Node({expr}), operand(_operand){
  exec = function<void()> ([&]() -> void
  {
    int true_case = l_true, false_case = l_false;
    int nxt_op = -1;
   
    if(operand == NOT){
      if(true_case == -1 && false_case == -1){
        true_case = code_gen::get_next_label();
        false_case = code_gen::get_next_label();
      }
      ((Expr*) children[0])->l_true = false_case;
      ((Expr*) children[0])->l_false = true_case;
    }else{
      ((Expr*) children[0])->l_true = ((Expr*) children[0])->l_false = -1;
    }

    exec_children();
    type = unary_operand(operand, ((Expr*) children[0])->type);
    if(type == nullptr){
      yyerror("Uncompatible operand");
      exit(1);
    }

    if(operand == NOT){
      if(l_true == -1 && l_false == -1){
        var = code_gen::gen_var(type->name);

        code = code_gen::concat_code({
          code,
          var, " = ", code_gen::get_op_name(operand), " ", ((Expr*) children[0])->var,
          ";\n"
        });
      }else{
        // ja vai ter gotozado
      }
    }else{
      var = code_gen::gen_var(type->name);
      code = code_gen::concat_code({
        children[0]->code,
        var,
        " = ",
        code_gen::get_op_name(operand),
        ((Expr*) children[0])->var,
        ";\n"
      });
    }

  });
}

// ? cast de q?
Expr::Expr(Tipo *tipo, Expr* expr):Node({tipo, expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = casting_result(((Tipo*) children[0])->type, ((Expr*) children[1])->type);
    if(type == nullptr){
      yyerror("Uncompatible casting");
      exit(1);
    }
    // TODO
  });
}

// PARENTESES
Expr::Expr(Expr* expr):Node({expr}){
  exec = function<void()> ([&]() -> void
  {
    ((Expr*) children[0])->l_true = l_true;
    ((Expr*) children[0])->l_false = l_false;

    exec_children();
    type = ((Expr*) children[0])->type;

    code = children[0]->code;
    if((l_true == -1 && l_false == -1) || type != BOOL_TYPE){
      var = code_gen::gen_var(type->name);
      code = code_gen::concat_code({
        code,
        var,
        " = ",
        ((Expr*) children[0])->var,
        ";\n"
      });
    }

  });
}

Expr::Expr(FolhaExpr* folha_expr):Node({folha_expr}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((FolhaExpr*) children[0])->type;
    var = code_gen::gen_var(type->name);

    code = code_gen::concat_code({
      children[0]->code,
      var, " = ", ((FolhaExpr*) children[0])->var, ";\n"
    });

    if(type == BOOL_TYPE && (l_true != -1 && l_false != -1)){
      code = code_gen::concat_code({
        code,
        "if(", var ,") goto ", code_gen::gen_label(l_true), ";\n",
        "goto ", code_gen::gen_label(l_false), ";\n"
      });
    }

  });
}

FolhaExpr::FolhaExpr(Literal* literal):Node({literal}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Literal*) children[0])->type;
    var = code_gen::gen_var(type->name);
    code = code_gen::concat_code({
      var,
      " = ",
      children[0]->code,
      ";\n"
    });
  });
}

FolhaExpr::FolhaExpr(Variavel* variavel):Node({variavel}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Variavel*) children[0])->type;
    var = ((Variavel*) children[0])->var;
    code = children[0]->code;
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
      (children[0] != nullptr && !are_compatible_types(((ListaExpr*) children[0])->type_list, parameters))){
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

    if(type == INT_TYPE){
      if(operand == PLUS)
        value.int_ = ((ExprConst*) children[0])->value.int_ + ((ExprConst*) children[1])->value.int_;
      else if(operand == MINUS)
        value.int_ = ((ExprConst*) children[0])->value.int_ - ((ExprConst*) children[1])->value.int_;
      else exit(1);
    }
  });
}

ExprConst::ExprConst(Literal* literal):Node({literal}){
  exec = function<void()> ([&]() -> void
  {
    exec_children();
    type = ((Literal*) children[0])->type;
    value = ((Literal*) children[0])->value;
  });
}