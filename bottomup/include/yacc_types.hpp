#ifndef TYPES_H
#define TYPES_H

#include "tree_nodes.hpp"

typedef union{
  node::Programa* _programa;
  node::Definicoes* _definicoes;
  node::ListaDefinicoes* _listadefinicoes;
  node::Definicao* _definicao;
  node::VariavelConstante* _variavelconstante;
  node::Declaracoes* _declaracoes;
  node::ListaDeclaracoes* _listadeclaracoes;
  node::Declaracao* _declaracao;
  node::NovoBloco* _novobloco;
  node::Bloco* _bloco;
  node::ListaComandos* _listacomandos;
  node::DecVar* _decvar;
  node::ListaIdVars* _listaidvars;
  node::DecProc* _decproc;
  node::DecFunc* _decfunc;
  node::ListaParametros* _listaparametros;
  node::Parametro* _parametro;
  node::DecTipo* _dectipo;
  node::Tipo* _tipo;
  node::TipoSimples* _tiposimples;
  node::ColchetesOuVazio* _colchetesouvazio;
  node::Registro* _registro;
  node::ListaDecAtr* _listadecatr;
  node::DecAtr* _decatr;
  node::Comando* _comando;
  node::Atribuicao* _atribuicao;
  node::ListaExpr* _listaexpr;
  node::Controle* _controle;
  node::Se* _se;
  node::Senao* _senao;
  node::Escolha* _escolha;
  node::ListaCasos* _listacasos;
  node::EscolhaPadrao* _escolhapadrao;
  node::CasoEscolha* _casoescolha;
  node::Repeticao* _repeticao;
  node::Enquanto* _enquanto;
  node::FacaEnquanto* _facaenquanto;
  node::Para* _para;
  node::Retorno* _retorno;
  node::Variavel* _variavel;
  node::ListaModificadores* _listamodificadores;
  node::ModificadorVariavel* _modificadorvariavel;
  node::Literal* _literal;
  node::LiteralLogico* _literallogico;
  node::LiteralArray* _literalarray;
  node::ListaLiterais* _listaliterais;
  node::Expr* _expr;
  node::FolhaExpr* _folhaexpr;
  node::ExprConst* _exprconst;
  node::FolhaExprConst* _folhaexprconst;
	string* name;
} YYSTYPE;

extern YYSTYPE yylval;


#endif