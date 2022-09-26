#include "src/token_id.h"
#include "src/rule_id.h"
#include "src/stack.h"
#include <assert.h>
#include "lex.yy.c"


enum TOKEN_ID tok;
void advance() {tok=yylex();}
void error(){
  1/0;
  exit(0);
}
void eat(enum TOKEN_ID t) {if (tok==t) advance(); else error();}

SymbolStack * s;

void PROGRAMA() {
  printf("%d\n", tok);
  switch (tok) {
  case CONST:
  case DECLRS:
  case BLOCO: {
    pop(s);
    push_non_terminal(s, E_NOVO_BLOCO);
    push_non_terminal(s, E_DECLARACOES);
    push_non_terminal(s, E_DEFINICOES);
    break;
  }
  default:
    error();
  }
}

void DEFINICOES() {
  switch (tok) {
  case CONST: {
    pop(s);
    push_terminal(s, CHA_DIR);
    push_non_terminal(s, E_LISTA_DEFINICOES_OU_VAZIO);
    push_non_terminal(s, E_DEFINICAO);
    push_terminal(s, CHA_ESQ);
    push_terminal(s, CONST);
    break;
  }
  case DECLRS:
  case BLOCO: {
    pop(s);
    break;
  }
  default:
    error();
  }
}

void LISTA_DEFINICOES_OU_VAZIO() {
  switch (tok) {
  case CHA_DIR: {
    pop(s);
    break;
  }
  case PONTO_VIRG: {
    pop(s);
    push_non_terminal(s, E_LISTA_DEFINICOES_OU_VAZIO);
    push_non_terminal(s, E_DEFINICAO);
    push_terminal(s, PONTO_VIRG);
    break;
  }
  default:
    error();
  }
}

void DEFINICAO() {
  switch (tok) {
  case ID: {
    pop(s);
    push_non_terminal(s, E_LITERAL);
    push_terminal(s, IGUAL);
    push_terminal(s, ID);
    break;
  }
  default:
    error();
  }
}

void DECLARACOES() {
  switch (tok) {
  case DECLRS: {
    pop(s);
    push_terminal(s, CHA_DIR);
    push_non_terminal(s, E_LISTA_DECLARACOES_OU_VAZIO);
    push_non_terminal(s, E_DECLARACAO);
    push_terminal(s, CHA_ESQ);
    push_terminal(s, DECLRS);
    break;
  }
  case ID:
  case BLOCO:
  case CONTINUE:
  case PARE:
  case SE:
  case ESCOLHA:
  case ENQUANTO:
  case FACA:
  case PARA:
  case RETORNE: {
    pop(s);
    break;
  }
  default:
    error();
  }
}

void LISTA_DECLARACOES_OU_VAZIO() {
  switch (tok) {
  case CHA_DIR: {
    pop(s);
    break;
  }
  case PONTO_VIRG: {
    pop(s);
    push_non_terminal(s, E_LISTA_DECLARACOES_OU_VAZIO);
    push_non_terminal(s, E_DECLARACAO);
    push_terminal(s, PONTO_VIRG);
    break;
  }
  default:
    error();
  }
}

void DECLARACAO() {
  switch (tok) {
  case VAR: {
    pop(s);
    push_non_terminal(s, E_DEC_VAR);
    break;
  }
  case PROC: {
    pop(s);
    push_non_terminal(s, E_DEC_PROC);
    break;
  }
  case FUNC: {
    pop(s);
    push_non_terminal(s, E_DEC_FUNC);
    break;
  }
  case TIPO: {
    pop(s);
    push_non_terminal(s, E_DEC_TIPO);
    break;
  }
  default:
    error();
  }
}

void DEC_VAR() {
  switch (tok) {
  case VAR: {
    pop(s);
    push_non_terminal(s, E_TIPO_);
    push_terminal(s, DOIS_PONTOS);
    push_non_terminal(s, E_IDS_OU_VAZIO);
    push_terminal(s, ID);
    push_terminal(s, VAR);
    break;
  }
  default:
    error();
  }
}

void IDS_OU_VAZIO() {
  switch (tok) {
  case DOIS_PONTOS: {
    pop(s);
    break;
  }
  case VIRGULA: {
    pop(s);
    push_non_terminal(s, E_IDS_OU_VAZIO);
    push_terminal(s, ID);
    push_terminal(s, VIRGULA);
  }
  default:
    error();
  }
}

void LISTA_PARAMETROS_OU_VAZIO() {
  switch (tok) {
  case VIRGULA: {
    pop(s);
    push_non_terminal(s, E_LISTA_PARAMETROS_OU_VAZIO);
    push_non_terminal(s, E_PARAMETRO);
    push_terminal(s, VIRGULA);
  }
  case PAR_DIR: {
    pop(s);
    break;
  }
  default:
    error();
  }
}

void TALVEZ_REF() {
  switch (tok) {
  case ID: {
    pop(s);
    break;
  }
  case REF: {
    pop(s);
    push_terminal(s, REF);
    break;
  }
  default:
    error();
  }
}

void PARAMETRO() {
  switch (tok) {
  case ID:
  case REF: {
    pop(s);
    push_non_terminal(s, E_TIPO_);
    push_terminal(s, DOIS_PONTOS);
    push_terminal(s, ID);
    push_non_terminal(s, E_TALVEZ_REF);
    break;
  }
  default:
    error();
  }
}

void PARAMETROS_OU_VAZIO() {
  switch (tok) {
  case ID:
  case REF: {
    pop(s);
    push_non_terminal(s, E_LISTA_PARAMETROS_OU_VAZIO);
    push_non_terminal(s, E_PARAMETRO);
    break;
  }
  case PAR_DIR: {
    pop(s);
    break;
  }
  default:
    error();
  }
}

void DEC_PROC() {
  switch (tok) {
  case PROC: {
    pop(s);
    push_non_terminal(s, E_BLOCO_);
    push_terminal(s, DOIS_PONTOS);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_PARAMETROS_OU_VAZIO);
    push_terminal(s, PAR_ESQ);
    push_terminal(s, ID);
    push_terminal(s, PROC);
    break;
  }
  default:
    error();
  }
}

void DEC_FUNC() {
  switch (tok) {
  case FUNC: {
    pop(s);
    push_non_terminal(s, E_BLOCO_);
    push_non_terminal(s, E_TIPO_);
    push_terminal(s, DOIS_PONTOS);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_PARAMETROS_OU_VAZIO);
    push_terminal(s, PAR_ESQ);
    push_terminal(s, ID);
    push_terminal(s, FUNC);
    break;
  }
  default:
    error();
  }
}

void DEC_TIPO() {
  switch (tok) {
  case TIPO: {
    pop(s);
    push_non_terminal(s, E_TIPO_);
    push_terminal(s, IGUAL);
    push_terminal(s, ID);
    push_terminal(s, TIPO);
    break;
  }
  default:
    error();
  }
}

void TIPO_() {
  switch (tok) {
  case ID:
  case INT:
  case LOGICO:
  case FLUT:
  case CARAC:
  case ESTRUTURA: {
    pop(s);
    push_non_terminal(s, E_COLCHETES_OU_VAZIO);
    push_non_terminal(s, E_TIPO_PREF);
    break;
  }
  default:
    error();
  }
}

void COLCHETES_OU_VAZIO() {
  switch (tok) {
  case CHA_ESQ:
  case CHA_DIR:
  case PONTO_VIRG:
  case VIRGULA:
  case PAR_DIR:
  case CAST: {
    pop(s);
    break;
  }
  case COL_ESQ: {
    pop(s);
    push_non_terminal(s, E_COLCHETES_OU_VAZIO);
    push_terminal(s, COL_DIR);
    push_non_terminal(s, E_C_EXPR);
    push_terminal(s, COL_ESQ);
  }
  default:
    error();
  }
}

void TIPO_PREF() {
  switch (tok) {
  case ID: {
    pop(s);
    push_terminal(s, ID);
    break;
  }
  case INT:
  case LOGICO:
  case FLUT:
  case CARAC: {
    pop(s);
    push_non_terminal(s, E_TIPO_SIMPLES);
    break;
  }
  case ESTRUTURA: {
    pop(s);
    push_non_terminal(s, E_REGISTRO);
    break;
  }
  default:
    error();
  }
}

void TIPO_SIMPLES() {
  switch (tok) {
  case INT: {
    pop(s);
    push_terminal(s, INT);
    break;
  }
  case LOGICO: {
    pop(s);
    push_terminal(s, LOGICO);
    break;
  }
  case FLUT: {
    pop(s);
    push_terminal(s, FLUT);
    break;
  }
  case CARAC: {
    pop(s);
    push_terminal(s, CARAC);
    break;
  }
  default:
    error();
  }
}

void REGISTRO() {
  switch (tok) {
  case ESTRUTURA: {
    pop(s);
    push_terminal(s, CHA_DIR);
    push_non_terminal(s, E_LISTA_DEC_VAR);
    push_non_terminal(s, E_DEC_VAR);
    push_terminal(s, CHA_ESQ);
    push_terminal(s, ESTRUTURA);
    break;
  }
  default:
    error();
  }
}

void LISTA_DEC_VAR() {
  switch (tok) {
  case CHA_DIR: {
    pop(s);
    break;
  }
  case PONTO_VIRG: {
    pop(s);
    push_non_terminal(s, E_LISTA_DEC_VAR);
    push_terminal(s, PONTO_VIRG);
    break;
  }
  default:
    error();
  }
}

void NOVO_BLOCO() {
  switch (tok) {
  case BLOCO: {
    pop(s);
    push_non_terminal(s, E_BLOCO_);
    push_terminal(s, BLOCO);
    break;
  }
  default:
    error();
  }
}

void BLOCO_() {
  switch (tok) {
  case CHA_ESQ: {
    pop(s);
    push_terminal(s, CHA_DIR);
    push_non_terminal(s, E_LISTA_COMANDOS_OU_VAZIO);
    push_non_terminal(s, E_COMANDO);
    push_non_terminal(s, E_DECLARACOES);
    push_terminal(s, CHA_ESQ);
    break;
  }
  default:
    error();
  }
}

void LISTA_COMANDOS_OU_VAZIO() {
  switch (tok) {
  case CHA_DIR: {
    pop(s);
    break;
  }
  case PONTO_VIRG: {
    pop(s);
    push_non_terminal(s, E_LISTA_COMANDOS_OU_VAZIO);
    push_non_terminal(s, E_COMANDO);
    push_terminal(s, PONTO_VIRG);
    break;
  }
  default:
    error();
  }
}

void COMANDO() {
  switch (tok) {
  case ID: {
    pop(s);
    push_non_terminal(s, E_ATRIBUICAO);
    break;
  }
  case BLOCO: {
    pop(s);
    push_non_terminal(s, E_NOVO_BLOCO);
    break;
  }
  case CONTINUE: {
    pop(s);
    push_terminal(s, CONTINUE);
    break;
  }
  case PARE: {
    pop(s);
    push_terminal(s, PARE);
    break;
  }
  case SE:
  case ESCOLHA: {
    pop(s);
    push_non_terminal(s, E_CONTROLE);
    break;
  }
  case ENQUANTO:
  case FACA:
  case PARA: {
    pop(s);
    push_non_terminal(s, E_REPETICAO);
    break;
  }
  case RETORNE: {
    pop(s);
    push_non_terminal(s, E_RETORNO);
    break;
  }
  default:
    error();
  }
}

void CONTROLE() {
  switch (tok) {
  case SE: {
    pop(s);
    push_non_terminal(s, E_SE_);
    break;
  }
  case ESCOLHA: {
    pop(s);
    push_non_terminal(s, E_ESCOLHA_);
    break;
  }
  default:
    error();
  }
}

void SE_() {
  switch (tok) {
  case SE: {
    pop(s);
    push_non_terminal(s, E_SENAO_OU_VAZIO);
    push_non_terminal(s, E_BLOCO_);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_EXPR);
    push_terminal(s, PAR_ESQ);
    push_terminal(s, SE);
    break;
  }
  default:
    error();
  }
}

void SENAO_OU_VAZIO() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG: {
    pop(s);
    break;
  }
  case SENAO: {
    pop(s);
    push_non_terminal(s, E_BLOCO_OU_SE);
    push_terminal(s, SENAO);
    break;;
  }
  default:
    error();
  }
}

void BLOCO_OU_SE() {
  switch (tok) {
  case CHA_ESQ: {
    pop(s);
    push_non_terminal(s, E_BLOCO_);
    break;
  }
  case SE: {
    pop(s);
    push_non_terminal(s, E_SE_);
    break;
  }
  default:
    error();
  }
}

void ESCOLHA_() {
  switch (tok) {
  case ESCOLHA: {
    pop(s);
    push_terminal(s, CHA_DIR);
    push_non_terminal(s, E_CASOS_ESCOLHA);
    push_terminal(s, CHA_ESQ);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_EXPR);
    push_terminal(s, PAR_ESQ);
    push_terminal(s, ESCOLHA);
    break;
  }
  default:
    error();
  }
}

void CASOS_ESCOLHA() {
  switch (tok) {
  case CASO: {
    pop(s);
    push_non_terminal(s, E_CASO_ESCOLHA_P);
    push_non_terminal(s, E_CASO_ESCOLHA);
    break;
  }
  case PADRAO: {
    pop(s);
    push_non_terminal(s, E_ESCOLHA_PADRAO);
    break;
  }
  default:
    error();
  }
}

void CASO_ESCOLHA_P() {
  switch (tok) {
  case CHA_DIR: {
    pop(s);
    break;
  }
  case CASO:
  case PADRAO: {
    pop(s);
    push_non_terminal(s, E_CASOS_ESCOLHA);
    break;
  }
  default:
    error();
  }
}

void CASO_ESCOLHA() {
  switch (tok) {
  case CASO: {
    pop(s);
    push_terminal(s, PONTO_VIRG);
    push_non_terminal(s, E_COMANDO);
    push_terminal(s, DOIS_PONTOS);
    push_non_terminal(s, E_C_EXPR);
    push_terminal(s, CASO);
    break;
  }
  default:
    error();
  }
}

void ESCOLHA_PADRAO() {
  switch (tok) {
  case PADRAO: {
    pop(s);
    push_terminal(s, PONTO_VIRG);
    push_non_terminal(s, E_COMANDO);
    push_terminal(s, DOIS_PONTOS);
    push_terminal(s, PADRAO);
    break;
  }
  default:
    error();
  }
}

void REPETICAO() {
  switch (tok) {
  case ENQUANTO: {
    pop(s);
    push_non_terminal(s, E_ENQUANTO_);
    break;
  }
  case FACA: {
    pop(s);
    push_non_terminal(s, E_FACA_ENQUANTO);
    break;
  }
  case PARA: {
    pop(s);
    push_non_terminal(s, E_PARA_);
    break;
  }
  default:
    error();
  }
}

void ENQUANTO_() {
  switch (tok) {
  case ENQUANTO: {
    pop(s);
    push_non_terminal(s, E_BLOCO_);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_EXPR);
    push_terminal(s, PAR_ESQ);
    push_terminal(s, ENQUANTO);
    break;
  }
  default:
    error();
  }
}

void FACA_ENQUANTO() {
  switch (tok) {
  case FACA: {
    pop(s);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_EXPR);
    push_terminal(s, PAR_ESQ);
    push_terminal(s, ENQUANTO);
    push_non_terminal(s, E_COMANDO);
    push_non_terminal(s, E_BLOCO_);
    push_terminal(s, FACA);
    break;
  }
  default:
    error();
  }
}

void PARA_() {
  switch (tok) {
  case PARA: {
    pop(s);
    push_non_terminal(s, E_BLOCO_);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_ATRIBUICAO);
    push_terminal(s, PONTO_VIRG);
    push_non_terminal(s, E_EXPR);
    push_terminal(s, PONTO_VIRG);
    push_non_terminal(s, E_ATRIBUICAO);
    push_terminal(s, PAR_ESQ);
    push_terminal(s, PARA);
    break;
  }
  default:
    error();
  }
}

void ATRIBUICAO() {
  switch (tok) {
  case ID: {
    pop(s);
    push_non_terminal(s, E_EXPR);
    push_terminal(s, IGUAL);
    push_non_terminal(s, E_MODIFICADORES_OU_VAZIO);
    push_terminal(s, ID);
    break;
  }
  default:
    error();
  }
}

void RETORNO() {
  switch (tok) {
  case RETORNE: {
    pop(s);
    push_non_terminal(s, E_EXPR_OU_VAZIO);
    push_terminal(s, RETORNE);
    break;
  }
  default:
    error();
  }
}

void EXPR_OU_VAZIO() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG: {
    pop(s);
    break;
  }
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_EXPR);
    break;
  }
  default:
    error();
  }
}

void EXPR() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_EXPR_P);
    push_non_terminal(s, E_T_OR);
    break;
  }
  default:
    error();
  }
}

void EXPR_P() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG:
  case VIRGULA:
  case PAR_DIR:
  case COL_DIR: {
    pop(s);
    break;
  }
  case OU: {
    pop(s);
    push_terminal(s, OU);
    push_non_terminal(s, E_EXPR_P);
    push_non_terminal(s, E_T_OR);
    break;
  }
  default:
    error();
  }
}

void T_OR() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_T_OR_P);
    push_non_terminal(s, E_T_AND);
    break;
  }
  default:
    error();
  }
}

void T_OR_P() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG:
  case VIRGULA:
  case PAR_DIR:
  case COL_DIR:
  case OU: {
    pop(s);
    break;
  }
  case E: {
    pop(s);
    push_terminal(s, E);
    push_non_terminal(s, E_T_OR_P);
    push_non_terminal(s, E_T_AND);
    break;
  }
  default:
    error();
  }
}

void T_AND() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_T_AND_P);
    push_non_terminal(s, E_T_REL);
    break;
  }
  default:
    error();
  }
}

void T_AND_P() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG:
  case VIRGULA:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E: {
    pop(s);
    break;
  }
  case IGUAL_IGUAL: {
    pop(s);
    push_non_terminal(s, E_T_AND_P);
    push_non_terminal(s, E_T_REL);
    push_terminal(s, IGUAL_IGUAL);
    break;
  }
  case DIFERENTE: {
    pop(s);
    push_non_terminal(s, E_T_AND_P);
    push_non_terminal(s, E_T_REL);
    push_terminal(s, DIFERENTE);
    break;
  }
  case MENOR_IGUAL: {
    pop(s);
    push_non_terminal(s, E_T_AND_P);
    push_non_terminal(s, E_T_REL);
    push_terminal(s, MENOR_IGUAL);
    break;
  }
  case MAIOR_IGUAL: {
    pop(s);
    push_non_terminal(s, E_T_AND_P);
    push_non_terminal(s, E_T_REL);
    push_terminal(s, MAIOR_IGUAL);
    break;
  }
  case MENOR: {
    pop(s);
    push_non_terminal(s, E_T_AND_P);
    push_non_terminal(s, E_T_REL);
    push_terminal(s, MENOR);
    break;
  }
  case MAIOR: {
    pop(s);
    push_non_terminal(s, E_T_AND_P);
    push_non_terminal(s, E_T_REL);
    push_terminal(s, MAIOR);
    break;
  }
  default:
    error();
  }
}

void T_REL() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_T_REL_P);
    push_non_terminal(s, E_T_ARIT);
    break;
  }
  default:
    error();
  }
}

void T_REL_P() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG:
  case VIRGULA:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E:
  case IGUAL_IGUAL:
  case DIFERENTE:
  case MENOR_IGUAL:
  case MAIOR_IGUAL:
  case MENOR:
  case MAIOR: {
    pop(s);
    break;
  }
  case MAIS: {
    pop(s);
    push_non_terminal(s, E_T_REL_P);
    push_non_terminal(s, E_T_ARIT);
    push_terminal(s, MAIS);
    break;
  }
  case MENOS: {
    pop(s);
    push_non_terminal(s, E_T_REL_P);
    push_non_terminal(s, E_T_ARIT);
    push_terminal(s, MENOS);
    break;
  }
  default:
    error();
  }
}

void T_ARIT() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_T_ARIT_P);
    push_non_terminal(s, E_T_FATOR);
    break;
  }
  default:
    error();
  }
}

void T_ARIT_P() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG:
  case VIRGULA:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E:
  case IGUAL_IGUAL:
  case DIFERENTE:
  case MENOR_IGUAL:
  case MAIOR_IGUAL:
  case MENOR:
  case MAIOR:
  case MAIS:
  case MENOS: {
    pop(s);
    break;
  }
  case MULT: {
    pop(s);
    push_terminal(s, MULT);
    push_non_terminal(s, E_T_ARIT_P);
    push_non_terminal(s, E_T_FATOR);
    break;
  }
  case DIV: {
    pop(s);
    push_terminal(s, DIV);
    push_non_terminal(s, E_T_ARIT_P);
    push_non_terminal(s, E_T_FATOR);
    break;
  }
  case MOD: {
    pop(s);
    push_terminal(s, MOD);
    push_non_terminal(s, E_T_ARIT_P);
    push_non_terminal(s, E_T_FATOR);
    break;
  }
  default:
    error();
  }
}

void T_FATOR() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_T_FATOR_P);
    push_non_terminal(s, E_T_EXPO);
    break;
  }
  default:
    error();
  }
}

void T_FATOR_P() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG:
  case VIRGULA:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E:
  case IGUAL_IGUAL:
  case DIFERENTE:
  case MENOR_IGUAL:
  case MAIOR_IGUAL:
  case MENOR:
  case MAIOR:
  case MAIS:
  case MENOS:
  case MULT:
  case DIV:
  case MOD: {
    pop(s);
    break;
  }
  case EXP: {
    pop(s);
    push_non_terminal(s, E_T_FATOR);
    push_terminal(s, EXP);
    break;
  }
  default:
    error();
  }
}

void T_EXPO() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_T_UN);
    break;
  }
  default:
    error();
  }
}

void T_UN() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_T_PAR_ID);
    break;
  }
  case MAIS: {
    pop(s);
    push_non_terminal(s, E_T_UN);
    push_terminal(s, MAIS);
    break;
  }
  case MENOS: {
    pop(s);
    push_non_terminal(s, E_T_UN);
    push_terminal(s, MENOS);
    break;
  }
  case NAO: {
    pop(s);
    push_non_terminal(s, E_T_UN);
    push_terminal(s, NAO);
    break;
  }
  case CAST: {
    pop(s);
    push_non_terminal(s, E_T_UN);
    push_non_terminal(s, E_CAST_);
    break;
  }
  default:
    error();
  }
}

void T_PAR_ID() {
  switch (tok) {
  case ID:
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_EXPR_FOLHA);
    break;
  }
  case PAR_ESQ: {
    pop(s);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_EXPR);
    push_terminal(s, PAR_ESQ);
    break;
  }
  default:
    error();
  }
}

void CAST_() {
  switch (tok) {
  case CAST: {
    pop(s);
    push_terminal(s, CAST);
    push_non_terminal(s, E_TIPO_);
    push_terminal(s, CAST);
    break;
  }
  default:
    error();
  }
}

void EXPR_FOLHA() {
  switch (tok) {
  case ID: {
    pop(s);
    push_non_terminal(s, E_MODIFICADORES_OU_VAZIO);
    push_non_terminal(s, E_CHAMADA_FUNC_OU_VAZIO);
    push_terminal(s, ID);
    break;
  }
  case VERDADEIRO:
  case FALSO:
  case ALPHA:
  case NUM_INT:
  case NUM_FLUT: {
    pop(s);
    push_non_terminal(s, E_LITERAL);
    break;
  }
  default:
    error();
  }
}

void MOD_TYPE() {
  switch (tok) {
  case CHA_ESQ: {
    pop(s);
    push_terminal(s, CHA_DIR);
    push_non_terminal(s, E_EXPR);
    push_terminal(s, CHA_ESQ);
    break;
  }
  case PONTO: {
    pop(s);
    push_terminal(s, ID);
    push_terminal(s, PONTO);
    break;
  }
  default:
    error();
  }
}

void MODIFICADORES_OU_VAZIO() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG:
  case DOIS_PONTOS:
  case IGUAL:
  case VIRGULA:
  case PAR_DIR:
  case COL_ESQ:
  case COL_DIR:
  case OU:
  case E:
  case IGUAL_IGUAL:
  case DIFERENTE:
  case MENOR_IGUAL:
  case MAIOR_IGUAL:
  case MENOR:
  case MAIOR:
  case MAIS:
  case MENOS:
  case MULT:
  case DIV:
  case MOD:
  case EXP:
  case PONTO: {
    pop(s);
    break;
  }
  case PAR_ESQ: {
    pop(s);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_ARGS_FUNC_OU_VAZIO);
    push_terminal(s, PAR_ESQ);
    break;
  }
  default:
    error();
  }
}

void CHAMADA_FUNC_OU_VAZIO() {
  switch (tok) {
  case CHA_DIR:
  case PONTO_VIRG:
  case IGUAL:
  case DOIS_PONTOS:
  case VIRGULA:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E:
  case IGUAL_IGUAL:
  case DIFERENTE:
  case MENOR_IGUAL:
  case MAIOR_IGUAL:
  case MENOR:
  case MAIOR:
  case MAIS:
  case MENOS:
  case MULT:
  case DIV:
  case MOD:
  case EXP: {
    pop(s);
    break;
  }
  case COL_ESQ:
  case PONTO: {
    pop(s);
    push_non_terminal(s, E_MODIFICADORES_OU_VAZIO);
    push_non_terminal(s, E_MOD_TYPE);
    break;
  }
  default:
    error();
  }
}

void ARGS_FUNC_OU_VAZIO() {
  switch (tok) {
  case PAR_DIR:
    pop(s);
    break;
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_INT:
  case NUM_FLUT:
    pop(s);
    push_non_terminal(s, E_ARGS_FUNC);
    push_non_terminal(s, E_EXPR);
    break;
  default:
    error();
  }
}

void ARGS_FUNC() {
  switch (tok) {
  case VIRGULA:
    pop(s);
    push_non_terminal(s, E_ARGS_FUNC);
    push_non_terminal(s, E_EXPR);
    push_terminal(s, VIRGULA);
  case PAR_DIR:
    pop(s);
    break;
  default:
    error();
  }
}

void LITERAL() {
  switch (tok) {
  case VERDADEIRO:
  case FALSO:
    pop(s);
    push_non_terminal(s, E_LITERAL_LOGICO);
    break;
  case CARAC:
    pop(s);
    push_non_terminal(s, E_LITERAL_CARAC);
    break;
  case NUM_FLUT:
    pop(s);
    push_non_terminal(s, E_LITERAL_FLUT);
    break;
  case NUM_INT:
    pop(s);
    push_non_terminal(s, E_LITERAL_INT);
    break;
  default:
    error();
  }
}

void LITERAL_LOGICO() {
  switch (tok) {
  case VERDADEIRO:
    pop(s);
    push_terminal(s, VERDADEIRO);
    break;
  case FALSO:
    pop(s);
    push_terminal(s, FALSO);
    break;
  default:
    error();
  }
}

void LITERAL_CARAC() {
  switch (tok) {
  case CARAC:
    pop(s);
    push_terminal(s, CARAC);
    break;
  default:
    error();
  }
}

void LITERAL_FLUT() {
  switch (tok) {
  case NUM_FLUT:
    pop(s);
    push_terminal(s, NUM_FLUT);
    break;
  default:
    error();
  }
}

void LITERAL_INT() {
  switch (tok) {
  case NUM_INT:
    pop(s);
    push_terminal(s, NUM_INT);
    break;
  default:
    error();
  }
}

void C_EXPR() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_INT:
  case NUM_FLUT:
    pop(s);
    push_non_terminal(s, E_C_EXPR_P);
    push_non_terminal(s, E_C_T_OR);
  default:
    error();
  }
}

void C_EXPR_P() {
  switch (tok) {
  case DOIS_PONTOS:
  case PAR_DIR:
  case COL_DIR:
    pop(s);
    break;
  case OU:
    pop(s);
    push_non_terminal(s, E_C_EXPR_P);
    push_non_terminal(s, E_C_T_OR);
    push_terminal(s, OU);
    break;
  default:
    error();
  }
}

void C_T_OR() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_INT:
  case NUM_FLUT:
    pop(s);
    push_non_terminal(s, E_C_T_OR_P);
    push_non_terminal(s, E_C_T_AND);
    break;
  default:
    error();
  }
}

void C_T_OR_P() {
  switch (tok) {
  case DOIS_PONTOS:
  case PAR_DIR:
  case COL_DIR:
  case OU:
    pop(s);
    break;
  case E:
    pop(s);
    push_non_terminal(s, E_C_T_OR_P);
    push_non_terminal(s, E_C_T_AND);
    push_terminal(s, E);
    break;
  default:
    error();
  }
}

void C_T_AND() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_INT:
  case NUM_FLUT:
    pop(s);
    push_non_terminal(s, E_C_T_AND_P);
    push_non_terminal(s, E_C_T_REL);
    break;
  default:
    error();
  }
}

void C_T_AND_P() {
  switch (tok) {
  case DOIS_PONTOS:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E:
    pop(s);
    break;
  case IGUAL:
    pop(s);
    push_non_terminal(s, E_C_T_AND_P);
    push_non_terminal(s, E_C_T_REL);
    push_terminal(s, IGUAL);
    break;
  case DIFERENTE:
    pop(s);
    push_non_terminal(s, E_C_T_AND_P);
    push_non_terminal(s, E_C_T_REL);
    push_terminal(s, DIFERENTE);
    break;
  case MENOR:
    pop(s);
    push_non_terminal(s, E_C_T_AND_P);
    push_non_terminal(s, E_C_T_REL);
    push_terminal(s, MENOR);
    break;
  case MAIOR:
    pop(s);
    push_non_terminal(s, E_C_T_AND_P);
    push_non_terminal(s, E_C_T_REL);
    push_terminal(s, MAIOR);
    break;
  case MENOR_IGUAL:
    pop(s);
    push_non_terminal(s, E_C_T_AND_P);
    push_non_terminal(s, E_C_T_REL);
    push_terminal(s, MENOR_IGUAL);
    break;
  case MAIOR_IGUAL:
    pop(s);
    push_non_terminal(s, E_C_T_AND_P);
    push_non_terminal(s, E_C_T_REL);
    push_terminal(s, MAIOR_IGUAL);
    break;
  default:
    error();
  }
}

void C_T_REL() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_INT:
  case NUM_FLUT:
    pop(s);
    push_non_terminal(s, E_C_T_REL_P);
    push_non_terminal(s, E_C_T_ARIT);
    break;
  default:
    error();
  }
}

void C_T_REL_P() {
  switch (tok) {
  case DOIS_PONTOS:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E:
  case IGUAL:
  case DIFERENTE:
  case MENOR:
  case MAIOR:
  case MENOR_IGUAL:
  case MAIOR_IGUAL:
    pop(s);
    break;
  case MAIS:
    pop(s);
    push_non_terminal(s, E_C_T_REL_P);
    push_non_terminal(s, E_C_T_ARIT);
    push_terminal(s, MAIS);
    break;
  case MENOS:
    pop(s);
    push_non_terminal(s, E_C_T_REL_P);
    push_non_terminal(s, E_C_T_ARIT);
    push_terminal(s, MENOS);
    break;
  default:
    error();
  }
}

void C_T_ARIT_T_P() {
  switch (tok) {
  case DOIS_PONTOS:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E:
  case IGUAL:
  case DIFERENTE:
  case MENOR:
  case MAIOR:
  case MENOR_IGUAL:
  case MAIOR_IGUAL:
  case MAIS:
  case MENOS:
    pop(s);
    break;
  case MULT:
    pop(s);
    push_non_terminal(s, E_C_T_ARIT_T_P);
    push_non_terminal(s, E_C_T_FATOR);
    push_terminal(s, MULT);
    break;
  case DIV:
    pop(s);
    push_non_terminal(s, E_C_T_ARIT_T_P);
    push_non_terminal(s, E_C_T_FATOR);
    push_terminal(s, DIV);
    break;
  case MOD:
    pop(s);
    push_non_terminal(s, E_C_T_ARIT_T_P);
    push_non_terminal(s, E_C_T_FATOR);
    push_terminal(s, MOD);
    break;
  default:
    error();
  }
}

void C_T_FATOR() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_INT:
  case NUM_FLUT:
    pop(s);
    push_non_terminal(s, E_C_T_FATOR_P);
    push_non_terminal(s, E_C_T_EXPO);
    break;
  default:
    error();
  }
}

void C_T_FAOTR_P() {
  switch (tok) {
  case DOIS_PONTOS:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E:
  case IGUAL:
  case DIFERENTE:
  case MENOR:
  case MAIOR:
  case MENOR_IGUAL:
  case MAIOR_IGUAL:
  case MAIS:
  case MENOS:
  case MULT:
  case DIV:
  case MOD:
    pop(s);
    break;
  case EXP:
    pop(s);
    push_non_terminal(s, E_C_T_FATOR);
    push_terminal(s, EXP);
    break;
  default:
    error();
  }
}

void C_T_EXPO() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_INT:
  case NUM_FLUT:
    pop(s);
    push_non_terminal(s, E_C_T_UN);
    break;
  default:
    error();
  }
}

void C_T_UN() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_FLUT:
  case NUM_INT:
    pop(s);
    push_non_terminal(s, E_C_T_PAR_ID);
    break;
  case MAIS:
    pop(s);
    push_non_terminal(s, E_C_T_UN);
    push_terminal(s, MAIS);
    break;
  case MENOS:
    pop(s);
    push_non_terminal(s, E_C_T_UN);
    push_terminal(s, MENOS);
    break;
  case NAO:
    pop(s);
    push_non_terminal(s, E_C_T_UN);
    push_terminal(s, NAO);
    break;
  case CAST:
    pop(s);
    push_non_terminal(s, E_C_T_UN);
    push_non_terminal(s, E_CAST_);
    break;
  default:
    error();
  }
}

void C_T_PAR_ID() {
  switch (tok) {
  case ID:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_FLUT:
  case NUM_INT:
    pop(s);
    push_non_terminal(s, E_EXPR_FOLHA);
    break;
  case PAR_ESQ:
    pop(s);
    push_terminal(s, PAR_DIR);
    push_non_terminal(s, E_C_EXPR);
    push_terminal(s, PAR_ESQ);
    break;
  default:
    error();
  }
}

void C_T_ARIT() {
  switch (tok) {
  case ID:
  case PAR_ESQ:
  case MAIS:
  case MENOS:
  case NAO:
  case CAST:
  case VERDADEIRO:
  case FALSO:
  case CARAC:
  case NUM_INT:
  case NUM_FLUT:
    pop(s);
    push_non_terminal(s, E_C_T_ARIT_T_P);
    push_non_terminal(s, E_C_T_FATOR);
    break;
  default:
    error();
  }
}

void C_T_FATOR_P() {
  switch (tok) {
  case DOIS_PONTOS:
  case PAR_DIR:
  case COL_DIR:
  case OU:
  case E:
  case IGUAL:
  case DIFERENTE:
  case MENOR:
  case MAIOR:
  case MENOR_IGUAL:
  case MAIOR_IGUAL:
  case MAIS:
  case MENOS:
  case MULT:
  case DIV:
  case MOD:
    pop(s);
    break;
  case EXP:
    pop(s);
    push_non_terminal(s, E_C_T_FATOR);
    push_terminal(s, EXP);
    break;
  default:
    error();
  }
}



int main(){
  s = create_stack();

  push_non_terminal(s, E_PROGRAMA);
  advance();


  while(s->size > 0){
    Symbol* s_top = top(s);
    // printf("SIZE: %d\n", s->size);
    // printf("O PROXIMO TOKEN EH...... %d !!!!\n", tok);
    if(s_top->is_tok == 1){
      // printf("EU SOU TOKEN: %d\n", s_top->type.tok);
      eat(s_top->type.tok);
      pop(s);
    }else{ // eh nao terminal
      // printf("EU SOU RECURSIVO: %d\n", s_top->type.rule);
      assert(s_top->is_tok == 0);
      switch (s_top->type.rule) {
        case E_PROGRAMA: PROGRAMA(); break; 
        case E_DEFINICOES: DEFINICOES(); break; 
        case E_DECLARACOES: DECLARACOES(); break; 
        case E_DEFINICAO: DEFINICAO(); break; 
        case E_DECLARACAO: DECLARACAO(); break; 
        case E_LISTA_DEFINICOES_OU_VAZIO: LISTA_DEFINICOES_OU_VAZIO(); break; 
        case E_LISTA_DECLARACOES_OU_VAZIO: LISTA_DECLARACOES_OU_VAZIO(); break; 
        case E_IDS_OU_VAZIO: IDS_OU_VAZIO(); break; 
        case E_DEC_VAR: DEC_VAR(); break; 
        case E_DEC_PROC: DEC_PROC(); break; 
        case E_DEC_FUNC: DEC_FUNC(); break; 
        case E_DEC_TIPO: DEC_TIPO(); break; 
        case E_TIPO_PREF: TIPO_PREF(); break; 
        case E_COLCHETES_OU_VAZIO: COLCHETES_OU_VAZIO(); break; 
        case E_PARAMETRO: PARAMETRO(); break; 
        case E_TIPO_SIMPLES: TIPO_SIMPLES(); break; 
        case E_NOVO_BLOCO: NOVO_BLOCO(); break; 
        case E_LISTA_DEC_VAR: LISTA_DEC_VAR(); break; 
        case E_LISTA_PARAMETROS_OU_VAZIO: LISTA_PARAMETROS_OU_VAZIO(); break; 
        case E_TALVEZ_REF: TALVEZ_REF(); break; 
        case E_PARAMETROS_OU_VAZIO: PARAMETROS_OU_VAZIO(); break; 
        case E_BLOCO_: BLOCO_(); break; 
        case E_ATRIBUICAO: ATRIBUICAO(); break; 
        case E_LISTA_COMANDOS_OU_VAZIO: LISTA_COMANDOS_OU_VAZIO(); break; 
        case E_REGISTRO: REGISTRO(); break; 
        case E_COMANDO: COMANDO(); break; 
        case E_CONTROLE: CONTROLE(); break; 
        case E_RETORNO: RETORNO(); break; 
        case E_SENAO_OU_VAZIO: SENAO_OU_VAZIO(); break; 
        case E_BLOCO_OU_SE: BLOCO_OU_SE(); break; 
        case E_CASOS_ESCOLHA: CASOS_ESCOLHA(); break; 
        case E_CASO_ESCOLHA: CASO_ESCOLHA(); break; 
        case E_CASO_ESCOLHA_P: CASO_ESCOLHA_P(); break; 
        case E_ESCOLHA_PADRAO: ESCOLHA_PADRAO(); break; 
        case E_REPETICAO: REPETICAO(); break; 
        case E_ESCOLHA_: ESCOLHA_(); break; 
        case E_ENQUANTO_: ENQUANTO_(); break; 
        case E_FACA_ENQUANTO: FACA_ENQUANTO(); break; 
        case E_PARA_: PARA_(); break; 
        case E_EXPR_OU_VAZIO: EXPR_OU_VAZIO(); break; 
        case E_EXPR: EXPR(); break; 
        case E_T_OR: T_OR(); break; 
        case E_EXPR_P: EXPR_P(); break; 
        case E_T_AND: T_AND(); break; 
        case E_T_OR_P: T_OR_P(); break; 
        case E_T_REL: T_REL(); break; 
        case E_T_AND_P: T_AND_P(); break; 
        case E_T_ARIT: T_ARIT(); break; 
        case E_T_REL_P: T_REL_P(); break; 
        case E_T_FATOR: T_FATOR(); break; 
        case E_T_ARIT_P: T_ARIT_P(); break; 
        case E_T_EXPO: T_EXPO(); break; 
        case E_T_FATOR_P: T_FATOR_P(); break; 
        case E_T_UN: T_UN(); break; 
        case E_T_PAR_ID: T_PAR_ID(); break; 
        case E_CAST_: CAST_(); break; 
        case E_EXPR_FOLHA: EXPR_FOLHA(); break; 
        case E_TIPO_: TIPO_(); break; 
        case E_CHAMADA_FUNC_OU_VAZIO: CHAMADA_FUNC_OU_VAZIO(); break; 
        case E_MODIFICADORES_OU_VAZIO: MODIFICADORES_OU_VAZIO(); break; 
        case E_MOD_TYPE: MOD_TYPE(); break; 
        case E_ARGS_FUNC_OU_VAZIO: ARGS_FUNC_OU_VAZIO(); break; 
        case E_ARGS_FUNC: ARGS_FUNC(); break; 
        case E_LITERAL: LITERAL(); break; 
        case E_LITERAL_LOGICO: LITERAL_LOGICO(); break; 
        case E_LITERAL_CARAC: LITERAL_CARAC(); break; 
        case E_LITERAL_INT: LITERAL_INT(); break; 
        case E_LITERAL_FLUT: LITERAL_FLUT(); break; 
        case E_C_EXPR: C_EXPR(); break; 
        case E_C_EXPR_P: C_EXPR_P(); break; 
        case E_C_T_OR: C_T_OR(); break; 
        case E_C_T_OR_P: C_T_OR_P(); break; 
        case E_C_T_AND: C_T_AND(); break; 
        case E_C_T_AND_P: C_T_AND_P(); break; 
        case E_C_T_REL: C_T_REL(); break; 
        case E_C_T_REL_P: C_T_REL_P(); break; 
        case E_C_T_ARIT: C_T_ARIT(); break; 
        case E_C_T_ARIT_T_P: C_T_ARIT_T_P(); break; 
        case E_C_T_FATOR: C_T_FATOR(); break; 
        case E_C_T_FATOR_P: C_T_FATOR_P(); break; 
        case E_C_T_EXPO: C_T_EXPO(); break; 
        case E_C_T_UN: C_T_UN(); break; 
        case E_C_T_PAR_ID: C_T_PAR_ID(); break;
        case E_SE_ : SE_(); break;
        default: error();
      }
    }
  } 
}