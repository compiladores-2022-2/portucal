#ifndef TREE_NODES_H
#define TREE_NODES_H

#include<string>
#include <functional>
#include "symble_table.hpp"
#include "internal_enums.hpp"
using namespace std;

namespace node{

class Programa;
class Definicoes;
class ListaDefinicoes;
class Definicao;
class VariavelConstante;
class Declaracoes;
class ListaDeclaracoes;
class Declaracao;
class NovoBloco;
class Bloco;
class ListaComandos;
class DecVar;
class ListaIdVars;
class DecProc;
class DecFunc;
class ListaParametros;
class Parametro;
class DecTipo;
class Tipo;
class TipoSimples;
class ColchetesOuVazio;
class Registro;
class ListaDecAtr;
class DecAtr;
class Comando;
class Atribuicao;
class ListaExpr;
class Controle;
class Se;
class Senao;
class Escolha;
class ListaCasos;
class EscolhaPadrao;
class CasoEscolha;
class Repeticao;
class Enquanto;
class FacaEnquanto;
class Para;
class Retorno;
class Variavel;
class ListaModificadores;
class ModificadorVariavel;
class Literal;
class LiteralLogico;
class LiteralArray;
class ListaLiterais;
class Expr;
class FolhaExpr;
class ExprConst;
class FolhaExprConst;

class Node{
public:
  vector<Node*> children;
  function<void(void)> exec;

  Node(vector<Node*> _children = {})
  :children(_children), exec([&](){
    exec_children();
  }){}

  void exec_children(){
    for(auto node : children){
      if(node) node->exec();
    }
  }
};

class Programa : public Node{
public:
  Programa(Definicoes* definicoes, Declaracoes* decs, NovoBloco* novo_bloco);
};

class Definicoes : public Node{
public:
  Definicoes(ListaDefinicoes* lista = nullptr);
};

class ListaDefinicoes : public Node{
public:
  ListaDefinicoes(Definicao* definicao);
  ListaDefinicoes(Definicao* definicao, ListaDefinicoes* lista);
};

class Definicao : public Node{
public:
  Definicao(VariavelConstante *var_const, Literal* literal);
};

class VariavelConstante : public Node{
public:
  VariavelConstante(string* id);
};

class Declaracoes : public Node{
public:
  Declaracoes(ListaDeclaracoes* lista = nullptr);
};

class ListaDeclaracoes : public Node{
public:
  bool ok;
  ListaDeclaracoes(Declaracao* declaracao, ListaDeclaracoes* lista = nullptr);
};

class Declaracao : public Node{
public:
  bool ok;
  Declaracao(DecVar* dec_var);
  Declaracao(DecProc* dec_proc);
  Declaracao(DecFunc* dec_func);
  Declaracao(DecTipo* dec_tipo);
};

class NovoBloco : public Node{
public:
  NovoBloco(Bloco* bloco);
};

class Bloco : public Node{
public:
  Bloco(Declaracoes* declaracoes, ListaComandos* lista_comandos);
};


class ListaComandos : public Node{
public:
  ListaComandos(Comando* comando, ListaComandos* lista_comandos = nullptr);
};

class DecVar : public Node{
public:
  vector<string*> id_list;
  Type* type;

  DecVar(ListaIdVars* lista_id_vars, Tipo* tipo);
};

class ListaIdVars : public Node{
public:
  string *id;
  vector<string*> id_list;

  ListaIdVars(string* _id, ListaIdVars *lista_id_vars = nullptr);
};

class DecProc : public Node{
public:
  DecProc(Bloco* bloco);
  DecProc(ListaParametros* lista_parametros, Bloco* bloco);
};

class DecFunc : public Node{
public:
  DecFunc(Bloco* bloco);
  DecFunc(ListaParametros* lista_parametros, Bloco* bloco);
};

class ListaParametros : public Node{
public:
  ListaParametros(Parametro* parametro, ListaParametros* lista_parametros);
};

class Parametro : public Node{
public:
  Parametro(string* id, Tipo* tipo);
};

class DecTipo : public Node{
  string* id;
public:
  DecTipo(string* _id, Tipo* tipo);
};

class Tipo : public Node{
  string *id;
public:
  Type* type;

  Tipo(string *id, ColchetesOuVazio* colchetes_ou_vazio);
  Tipo(TipoSimples* tipo_simples, ColchetesOuVazio* colchetes_ou_vazio);
  Tipo(Registro* registro, ColchetesOuVazio* colchetes_ou_vazio);
};

class TipoSimples : public Node{
public:
  Type* type;

  TipoSimples(PRIMITIVE_TYPE );
};


class ColchetesOuVazio : public Node{
public:
  vector<int> sizes;

  ColchetesOuVazio(void);
  ColchetesOuVazio(ExprConst* expr_const, ColchetesOuVazio* colchetes_ou_vazio);
};

class Registro : public Node{
public:
  Type* type;
  Registro(ListaDecAtr* lista_dec_attr);
};

class ListaDecAtr : public Node{
public:
  vector<pair<Type*, string*>> attr_list;
  ListaDecAtr(DecAtr* dec_atr, ListaDecAtr* lista_dec_atr = nullptr);
};

class DecAtr : public Node{
public:
  vector<string*> id_list;
  Type* type;
  DecAtr(ListaIdVars* lista_id_vars, Tipo* tipo);
};

class Comando : public Node{
public:
  COMMAND command;
  string* id;

  Comando(COMMAND c);
  Comando(Retorno* retorno);
  Comando(NovoBloco* novo_bloco);
  Comando(Controle* controle);
  Comando(Repeticao* repeticao);
  Comando(ListaExpr* lista_expr); // escreva
  Comando(Variavel* variavel);
  Comando(Atribuicao* atribuicao);
  Comando(string* _id, ListaExpr* lista_expr = nullptr);
};


class Atribuicao : public Node{
public:
  Atribuicao(Variavel* variavel, Expr* expr);
};

class ListaExpr : public Node{
public:
  vector<Type*> type_list;

  ListaExpr(Expr* expr, ListaExpr* lista_expr = nullptr);
};

class Controle : public Node{
public:

};

class Se : public Node{
public:

};

class Senao : public Node{
public:

};

class Escolha : public Node{
public:

};


class ListaCasos : public Node{
public:

};

class EscolhaPadrao : public Node{
public:

};

class CasoEscolha : public Node{
public:

};

class Repeticao : public Node{
public:

};

class Enquanto : public Node{
public:

};


class FacaEnquanto : public Node{
public:

};

class Para : public Node{
public:

};

class Retorno : public Node{
public:

};

class Variavel : public Node{
public:
  Type *type;
  string* id;

  Variavel(string* _id, ListaModificadores* lista_modificadores = nullptr);
};

class ListaModificadores : public Node{
public:
  vector<Modifier> modifiers;

  ListaModificadores(ModificadorVariavel* modificador, ListaModificadores* lista_mod = nullptr);
};


class ModificadorVariavel : public Node{
public:
  Modifier modifier;

  ModificadorVariavel(string *id);
  ModificadorVariavel(Expr* expr);
};

class Literal : public Node{
public:
  Type *type;

  Literal(Type *_type);
  Literal(LiteralArray *literal_array);

};

class LiteralLogico : public Node{
public:

};

class LiteralArray : public Node{
public:
  Type *type;
  LiteralArray();
  LiteralArray(ListaLiterais* lista_literais);
};

class ListaLiterais : public Node{
public:
  Type* type;
  int size;

  ListaLiterais(Literal* literal, ListaLiterais* lista_literais = nullptr);

};


class Expr : public Node{
public:
  Type *type;
  OP operand;

  Expr(Expr* expr1, OP operand, Expr* expr2);
  Expr(OP operand, Expr* expr);
  Expr(Tipo *_t, Expr* expr);
  Expr(Expr* expr);
  Expr(FolhaExpr* folha_expr);
};

class FolhaExpr : public Node{
public:
  Type* type;
  string *id;

  FolhaExpr(Literal* literal);
  FolhaExpr(Variavel* variavel);
  FolhaExpr(
    string* _id, 
    ListaExpr* lista_expr = nullptr, 
    ListaModificadores* lista_modificadores = nullptr
  );
};

class ExprConst : public Node{
public:
  Type* type;

};

class FolhaExprConst : public Node{
public:

};


}

#endif