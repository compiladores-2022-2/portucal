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

void _ARGS_FUNC_OU_VAZIO();
void _ATRIBUICAO();
void _BLOCO();
void _BLOCO_OU_SE();
void _CASOS_ESCOLHA();
void _CASO_ESCOLHA();
void _CASO_ESCOLHA_P();
void _CAST();
void _CHAMADA_FUNC_OU_VAZIO();
void _COLCHETES_OU_VAZIO();
void _COMANDO();
void _CONTROLE();
void _C_EXPR();
void _C_EXPR_P();
void _C_T_AND();
void _C_T_AND_P();
void _C_T_ARIC_T_P();
void _C_T_ARIT();
void _C_T_EXPO();
void _C_T_FATOR();
void _C_T_FATOR_P();
void _C_T_OR();
void _C_T_OR_P();
void _C_T_PAR_ID();
void _C_T_REL();
void _C_T_REL_P();
void _C_T_UN();
void _DECLARACAO();
void _DECLARACOES();
void _DEC_FUNC();
void _DEC_PROC();
void _DEC_TIPO();
void _DEC_VAR();
void _DEFINICAO();
void _DEFINICOES();
void _ENQUANTO();
void _ESCOLHA();
void _ESCOLHA_PADRAO();
void _EXPR();
void _EXPR_FOLHA();
void _EXPR_OU_VAZIO();
void _EXPR_P();
void _FACA_ENQUANTO();
void _IDS_OU_VAZIO();
void _LISTA_COMANDOS_OU_VAZIO();
void _LISTA_DECLARACOES_OU_VAZIO();
void _LISTA_DEC_VAR();
void _LISTA_DEFINICOES_OU_VAZIO();
void _LISTA_EXPR_OU_VAZIO();
void _LISTA_LITERAL_OU_VAZIO();
void _LISTA_PARAMETROS_OU_VAZIO();
void _LITERAL();
void _LITERAL_CARAC();
void _LITERAL_FLUT();
void _LITERAL_INT();
void _LITERAL_LISTA();
void _LITERAL_LOGICO();
void _MODIFICADORES_OU_VAZIO();
void _MOD_TYPE();
void _NOVO_BLOCO();
void _PARA();
void _PARAMETRO();
void _PARAMETROS_OU_VAZIO();
void _PROGRAMA();
void _REGISTRO();
void _REPETICAO();
void _RETORNO();
void _SE();
void _SENAO_OU_VAZIO();
void _TALVEZ_REF();
void _TIPO();
void _TIPO_PREF();
void _TIPO_SIMPLES();
void _T_AND();
void _T_AND_P();
void _T_ARIT();
void _T_ARIT_P();
void _T_EXPO();
void _T_FATOR();
void _T_FATOR_P();
void _T_OR();
void _T_OR_P();
void _T_PAR_ID();
void _T_REL();
void _T_REL_P();
void _T_UN();



void _ARGS_FUNC_OU_VAZIO(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_LISTA_EXPR_OU_VAZIO);
		push_non_terminal(s, E_EXPR);
		break;
		}
	case PAR_DIR:{
		pop(s);
		break;
		}
	default: error();
}} 

void _ATRIBUICAO(){ switch (tok) {
	case ID:{
		pop(s);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,IGUAL);
		push_non_terminal(s, E_MODIFICADORES_OU_VAZIO);
		push_terminal(s,ID);
		break;
		}
	default: error();
}} 

void _BLOCO(){ switch (tok) {
	case CHA_ESQ:{
		pop(s);
		push_terminal(s,CHA_DIR);
		push_non_terminal(s, E_LISTA_COMANDOS_OU_VAZIO);
		push_non_terminal(s, E_COMANDO);
		push_non_terminal(s, E_DECLARACOES);
		push_terminal(s,CHA_ESQ);
		break;
		}
	default: error();
}} 

void _BLOCO_OU_SE(){ switch (tok) {
	case CHA_ESQ:{
		pop(s);
		push_non_terminal(s, E_BLOCO);
		break;
		}
	case SE:{
		pop(s);
		push_non_terminal(s, E_SE);
		break;
		}
	default: error();
}} 

void _CASOS_ESCOLHA(){ switch (tok) {
	case CASO:{
		pop(s);
		push_non_terminal(s, E_CASO_ESCOLHA_P);
		push_non_terminal(s, E_CASO_ESCOLHA);
		break;
		}
	case PADRAO:{
		pop(s);
		push_non_terminal(s, E_ESCOLHA_PADRAO);
		break;
		}
	default: error();
}} 

void _CASO_ESCOLHA(){ switch (tok) {
	case CASO:{
		pop(s);
		push_terminal(s,PONTO_VIRG);
		push_non_terminal(s, E_COMANDO);
		push_terminal(s,DOIS_PONTOS);
		push_non_terminal(s, E_C_EXPR);
		push_terminal(s,CASO);
		break;
		}
	default: error();
}} 

void _CASO_ESCOLHA_P(){ switch (tok) {
	case CHA_DIR:{
		pop(s);
		break;
		}
	case CASO:
	case PADRAO:{
		pop(s);
		push_non_terminal(s, E_CASOS_ESCOLHA);
		break;
		}
	default: error();
}} 

void _CAST(){ switch (tok) {
	case CAST:{
		pop(s);
		push_terminal(s,CAST);
		push_non_terminal(s, E_TIPO);
		push_terminal(s,CAST);
		break;
		}
	default: error();
}} 

void _CHAMADA_FUNC_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:
	case PONTO_VIRG:
	case DOIS_PONTOS:
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
	case PONTO:{
		pop(s);
		break;
		}
	case PAR_ESQ:{
		pop(s);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_ARGS_FUNC_OU_VAZIO);
		push_terminal(s,PAR_ESQ);
		break;
		}
	default: error();
}} 

void _COLCHETES_OU_VAZIO(){ switch (tok) {
	case CHA_ESQ:
	case CHA_DIR:
	case PONTO_VIRG:
	case VIRGULA:
	case PAR_DIR:
	case CAST:{
		pop(s);
		break;
		}
	case COL_ESQ:{
		pop(s);
		push_non_terminal(s, E_COLCHETES_OU_VAZIO);
		push_terminal(s,COL_DIR);
		push_non_terminal(s, E_C_EXPR);
		push_terminal(s,COL_ESQ);
		break;
		}
	default: error();
}} 

void _COMANDO(){ switch (tok) {
	case ID:{
		pop(s);
		push_non_terminal(s, E_ATRIBUICAO);
		break;
		}
	case BLOCO:{
		pop(s);
		push_non_terminal(s, E_NOVO_BLOCO);
		break;
		}
	case CONTINUE:{
		pop(s);
		push_terminal(s,CONTINUE);
		break;
		}
	case PARE:{
		pop(s);
		push_terminal(s,PARE);
		break;
		}
	case ESCREVA:{
		pop(s);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_LISTA_EXPR_OU_VAZIO);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,PAR_ESQ);
		push_terminal(s,ESCREVA);
		break;
		}
	case LEIA:{
		pop(s);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_MODIFICADORES_OU_VAZIO);
		push_terminal(s,ID);
		push_terminal(s,PAR_ESQ);
		push_terminal(s,LEIA);
		break;
		}
	case SE:
	case ESCOLHA:{
		pop(s);
		push_non_terminal(s, E_CONTROLE);
		break;
		}
	case ENQUANTO:
	case FACA:
	case PARA:{
		pop(s);
		push_non_terminal(s, E_REPETICAO);
		break;
		}
	case RETORNE:{
		pop(s);
		push_non_terminal(s, E_RETORNO);
		break;
		}
	default: error();
}} 

void _CONTROLE(){ switch (tok) {
	case SE:{
		pop(s);
		push_non_terminal(s, E_SE);
		break;
		}
	case ESCOLHA:{
		pop(s);
		push_non_terminal(s, E_ESCOLHA);
		break;
		}
	default: error();
}} 

void _C_EXPR(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_C_EXPR_P);
		push_non_terminal(s, E_C_T_OR);
		break;
		}
	default: error();
}} 

void _C_EXPR_P(){ switch (tok) {
	case DOIS_PONTOS:
	case PAR_DIR:
	case COL_DIR:{
		pop(s);
		break;
		}
	case OU:{
		pop(s);
		push_non_terminal(s, E_C_EXPR_P);
		push_non_terminal(s, E_C_T_OR);
		push_terminal(s,OU);
		break;
		}
	default: error();
}} 

void _C_T_AND(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_C_T_AND_P);
		push_non_terminal(s, E_C_T_REL);
		break;
		}
	default: error();
}} 

void _C_T_AND_P(){ switch (tok) {
	case DOIS_PONTOS:
	case PAR_DIR:
	case COL_DIR:
	case OU:
	case E:{
		pop(s);
		break;
		}
	case IGUAL_IGUAL:{
		pop(s);
		push_non_terminal(s, E_C_T_AND_P);
		push_non_terminal(s, E_C_T_REL);
		push_terminal(s,IGUAL_IGUAL);
		break;
		}
	case DIFERENTE:{
		pop(s);
		push_non_terminal(s, E_C_T_AND_P);
		push_non_terminal(s, E_C_T_REL);
		push_terminal(s,DIFERENTE);
		break;
		}
	case MENOR_IGUAL:{
		pop(s);
		push_non_terminal(s, E_C_T_AND_P);
		push_non_terminal(s, E_C_T_REL);
		push_terminal(s,MENOR_IGUAL);
		break;
		}
	case MAIOR_IGUAL:{
		pop(s);
		push_non_terminal(s, E_C_T_AND_P);
		push_non_terminal(s, E_C_T_REL);
		push_terminal(s,MAIOR_IGUAL);
		break;
		}
	case MENOR:{
		pop(s);
		push_non_terminal(s, E_C_T_AND_P);
		push_non_terminal(s, E_C_T_REL);
		push_terminal(s,MENOR);
		break;
		}
	case MAIOR:{
		pop(s);
		push_non_terminal(s, E_C_T_AND_P);
		push_non_terminal(s, E_C_T_REL);
		push_terminal(s,MAIOR);
		break;
		}
	default: error();
}} 

void _C_T_ARIC_T_P(){ switch (tok) {
	case DOIS_PONTOS:
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
	case MENOS:{
		pop(s);
		break;
		}
	case MULT:{
		pop(s);
		push_non_terminal(s, E_C_T_ARIC_T_P);
		push_non_terminal(s, E_C_T_FATOR);
		push_terminal(s,MULT);
		break;
		}
	case DIV:{
		pop(s);
		push_non_terminal(s, E_C_T_ARIC_T_P);
		push_non_terminal(s, E_C_T_FATOR);
		push_terminal(s,DIV);
		break;
		}
	case MOD:{
		pop(s);
		push_non_terminal(s, E_C_T_ARIC_T_P);
		push_non_terminal(s, E_C_T_FATOR);
		push_terminal(s,MOD);
		break;
		}
	default: error();
}} 

void _C_T_ARIT(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_C_T_ARIC_T_P);
		push_non_terminal(s, E_C_T_FATOR);
		break;
		}
	default: error();
}} 

void _C_T_EXPO(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_C_T_UN);
		break;
		}
	default: error();
}} 

void _C_T_FATOR(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_C_T_FATOR_P);
		push_non_terminal(s, E_C_T_EXPO);
		break;
		}
	default: error();
}} 

void _C_T_FATOR_P(){ switch (tok) {
	case DOIS_PONTOS:
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
	case MOD:{
		pop(s);
		break;
		}
	case EXP:{
		pop(s);
		push_non_terminal(s, E_C_T_FATOR);
		push_terminal(s,EXP);
		break;
		}
	default: error();
}} 

void _C_T_OR(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_C_T_OR_P);
		push_non_terminal(s, E_C_T_AND);
		break;
		}
	default: error();
}} 

void _C_T_OR_P(){ switch (tok) {
	case DOIS_PONTOS:
	case PAR_DIR:
	case COL_DIR:
	case OU:{
		pop(s);
		break;
		}
	case E:{
		pop(s);
		push_non_terminal(s, E_C_T_OR_P);
		push_non_terminal(s, E_C_T_AND);
		push_terminal(s,E);
		break;
		}
	default: error();
}} 

void _C_T_PAR_ID(){ switch (tok) {
	case ID:
	case COL_ESQ:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_EXPR_FOLHA);
		break;
		}
	case PAR_ESQ:{
		pop(s);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_C_EXPR);
		push_terminal(s,PAR_ESQ);
		break;
		}
	default: error();
}} 

void _C_T_REL(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_C_T_REL_P);
		push_non_terminal(s, E_C_T_ARIT);
		break;
		}
	default: error();
}} 

void _C_T_REL_P(){ switch (tok) {
	case DOIS_PONTOS:
	case PAR_DIR:
	case COL_DIR:
	case OU:
	case E:
	case IGUAL_IGUAL:
	case DIFERENTE:
	case MENOR_IGUAL:
	case MAIOR_IGUAL:
	case MENOR:
	case MAIOR:{
		pop(s);
		break;
		}
	case MAIS:{
		pop(s);
		push_non_terminal(s, E_C_T_REL_P);
		push_non_terminal(s, E_C_T_ARIT);
		push_terminal(s,MAIS);
		break;
		}
	case MENOS:{
		pop(s);
		push_non_terminal(s, E_C_T_REL_P);
		push_non_terminal(s, E_C_T_ARIT);
		push_terminal(s,MENOS);
		break;
		}
	default: error();
}} 

void _C_T_UN(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_C_T_PAR_ID);
		break;
		}
	case MAIS:{
		pop(s);
		push_non_terminal(s, E_C_T_UN);
		push_terminal(s,MAIS);
		break;
		}
	case MENOS:{
		pop(s);
		push_non_terminal(s, E_C_T_UN);
		push_terminal(s,MENOS);
		break;
		}
	case NAO:{
		pop(s);
		push_non_terminal(s, E_C_T_UN);
		push_terminal(s,NAO);
		break;
		}
	case CAST:{
		pop(s);
		push_non_terminal(s, E_C_T_UN);
		push_non_terminal(s, E_CAST);
		break;
		}
	default: error();
}} 

void _DECLARACAO(){ switch (tok) {
	case VAR:{
		pop(s);
		push_non_terminal(s, E_DEC_VAR);
		break;
		}
	case PROC:{
		pop(s);
		push_non_terminal(s, E_DEC_PROC);
		break;
		}
	case FUNC:{
		pop(s);
		push_non_terminal(s, E_DEC_FUNC);
		break;
		}
	case TIPO:{
		pop(s);
		push_non_terminal(s, E_DEC_TIPO);
		break;
		}
	default: error();
}} 

void _DECLARACOES(){ switch (tok) {
	case DECLRS:{
		pop(s);
		push_terminal(s,CHA_DIR);
		push_non_terminal(s, E_LISTA_DECLARACOES_OU_VAZIO);
		push_non_terminal(s, E_DECLARACAO);
		push_terminal(s,CHA_ESQ);
		push_terminal(s,DECLRS);
		break;
		}
	case ID:
	case BLOCO:
	case CONTINUE:
	case PARE:
	case ESCREVA:
	case LEIA:
	case SE:
	case ESCOLHA:
	case ENQUANTO:
	case FACA:
	case PARA:
	case RETORNE:{
		pop(s);
		break;
		}
	default: error();
}} 

void _DEC_FUNC(){ switch (tok) {
	case FUNC:{
		pop(s);
		push_non_terminal(s, E_BLOCO);
		push_non_terminal(s, E_TIPO);
		push_terminal(s,DOIS_PONTOS);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_PARAMETROS_OU_VAZIO);
		push_terminal(s,PAR_ESQ);
		push_terminal(s,ID);
		push_terminal(s,FUNC);
		break;
		}
	default: error();
}} 

void _DEC_PROC(){ switch (tok) {
	case PROC:{
		pop(s);
		push_non_terminal(s, E_BLOCO);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_PARAMETROS_OU_VAZIO);
		push_terminal(s,PAR_ESQ);
		push_terminal(s,ID);
		push_terminal(s,PROC);
		break;
		}
	default: error();
}} 

void _DEC_TIPO(){ switch (tok) {
	case TIPO:{
		pop(s);
		push_non_terminal(s, E_TIPO);
		push_terminal(s,IGUAL);
		push_terminal(s,ID);
		push_terminal(s,TIPO);
		break;
		}
	default: error();
}} 

void _DEC_VAR(){ switch (tok) {
	case VAR:{
		pop(s);
		push_non_terminal(s, E_TIPO);
		push_terminal(s,DOIS_PONTOS);
		push_non_terminal(s, E_IDS_OU_VAZIO);
		push_terminal(s,ID);
		push_terminal(s,VAR);
		break;
		}
	default: error();
}} 

void _DEFINICAO(){ switch (tok) {
	case ID:{
		pop(s);
		push_non_terminal(s, E_LITERAL);
		push_terminal(s,IGUAL);
		push_terminal(s,ID);
		break;
		}
	default: error();
}} 

void _DEFINICOES(){ switch (tok) {
	case CONST:{
		pop(s);
		push_terminal(s,CHA_DIR);
		push_non_terminal(s, E_LISTA_DEFINICOES_OU_VAZIO);
		push_non_terminal(s, E_DEFINICAO);
		push_terminal(s,CHA_ESQ);
		push_terminal(s,CONST);
		break;
		}
	case DECLRS:
	case BLOCO:{
		pop(s);
		break;
		}
	default: error();
}} 

void _ENQUANTO(){ switch (tok) {
	case ENQUANTO:{
		pop(s);
		push_non_terminal(s, E_BLOCO);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,PAR_ESQ);
		push_terminal(s,ENQUANTO);
		break;
		}
	default: error();
}} 

void _ESCOLHA(){ switch (tok) {
	case ESCOLHA:{
		pop(s);
		push_terminal(s,CHA_DIR);
		push_non_terminal(s, E_CASOS_ESCOLHA);
		push_terminal(s,CHA_ESQ);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,PAR_ESQ);
		push_terminal(s,ESCOLHA);
		break;
		}
	default: error();
}} 

void _ESCOLHA_PADRAO(){ switch (tok) {
	case PADRAO:{
		pop(s);
		push_terminal(s,PONTO_VIRG);
		push_non_terminal(s, E_COMANDO);
		push_terminal(s,DOIS_PONTOS);
		push_terminal(s,PADRAO);
		break;
		}
	default: error();
}} 

void _EXPR(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_EXPR_P);
		push_non_terminal(s, E_T_OR);
		break;
		}
	default: error();
}} 

void _EXPR_FOLHA(){ switch (tok) {
	case ID:{
		pop(s);
		push_non_terminal(s, E_MODIFICADORES_OU_VAZIO);
		push_non_terminal(s, E_CHAMADA_FUNC_OU_VAZIO);
		push_terminal(s,ID);
		break;
		}
	case COL_ESQ:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_LITERAL);
		break;
		}
	default: error();
}} 

void _EXPR_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:
	case PONTO_VIRG:{
		pop(s);
		break;
		}
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_EXPR);
		break;
		}
	default: error();
}} 

void _EXPR_P(){ switch (tok) {
	case CHA_DIR:
	case PONTO_VIRG:
	case VIRGULA:
	case PAR_DIR:
	case COL_DIR:{
		pop(s);
		break;
		}
	case OU:{
		pop(s);
		push_non_terminal(s, E_EXPR_P);
		push_non_terminal(s, E_T_OR);
		push_terminal(s,OU);
		break;
		}
	default: error();
}} 

void _FACA_ENQUANTO(){ switch (tok) {
	case FACA:{
		pop(s);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,PAR_ESQ);
		push_terminal(s,ENQUANTO);
		push_non_terminal(s, E_BLOCO);
		push_terminal(s,FACA);
		break;
		}
	default: error();
}} 

void _IDS_OU_VAZIO(){ switch (tok) {
	case DOIS_PONTOS:{
		pop(s);
		break;
		}
	case VIRGULA:{
		pop(s);
		push_non_terminal(s, E_IDS_OU_VAZIO);
		push_terminal(s,ID);
		push_terminal(s,VIRGULA);
		break;
		}
	default: error();
}} 

void _LISTA_COMANDOS_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:{
		pop(s);
		break;
		}
	case PONTO_VIRG:{
		pop(s);
		push_non_terminal(s, E_LISTA_COMANDOS_OU_VAZIO);
		push_non_terminal(s, E_COMANDO);
		push_terminal(s,PONTO_VIRG);
		break;
		}
	default: error();
}} 

void _LISTA_DECLARACOES_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:{
		pop(s);
		break;
		}
	case PONTO_VIRG:{
		pop(s);
		push_non_terminal(s, E_LISTA_DECLARACOES_OU_VAZIO);
		push_non_terminal(s, E_DECLARACAO);
		push_terminal(s,PONTO_VIRG);
		break;
		}
	default: error();
}} 

void _LISTA_DEC_VAR(){ switch (tok) {
	case CHA_DIR:{
		pop(s);
		break;
		}
	case PONTO_VIRG:{
		pop(s);
		push_non_terminal(s, E_LISTA_DEC_VAR);
		push_terminal(s,PONTO_VIRG);
		break;
		}
	default: error();
}} 

void _LISTA_DEFINICOES_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:{
		pop(s);
		break;
		}
	case PONTO_VIRG:{
		pop(s);
		push_non_terminal(s, E_LISTA_DEFINICOES_OU_VAZIO);
		push_non_terminal(s, E_DEFINICAO);
		push_terminal(s,PONTO_VIRG);
		break;
		}
	default: error();
}} 

void _LISTA_EXPR_OU_VAZIO(){ switch (tok) {
	case VIRGULA:{
		pop(s);
		push_non_terminal(s, E_LISTA_EXPR_OU_VAZIO);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,VIRGULA);
		break;
		}
	case PAR_DIR:{
		pop(s);
		break;
		}
	default: error();
}} 

void _LISTA_LITERAL_OU_VAZIO(){ switch (tok) {
	case VIRGULA:{
		pop(s);
		push_non_terminal(s, E_LISTA_LITERAL_OU_VAZIO);
		push_non_terminal(s, E_LITERAL);
		push_terminal(s,VIRGULA);
		break;
		}
	case COL_DIR:{
		pop(s);
		break;
		}
	default: error();
}} 

void _LISTA_PARAMETROS_OU_VAZIO(){ switch (tok) {
	case VIRGULA:{
		pop(s);
		push_non_terminal(s, E_LISTA_PARAMETROS_OU_VAZIO);
		push_non_terminal(s, E_PARAMETRO);
		push_terminal(s,VIRGULA);
		break;
		}
	case PAR_DIR:{
		pop(s);
		break;
		}
	default: error();
}} 

void _LITERAL(){ switch (tok) {
	case COL_ESQ:{
		pop(s);
		push_non_terminal(s, E_LITERAL_LISTA);
		break;
		}
	case VERDADEIRO:
	case FALSO:{
		pop(s);
		push_non_terminal(s, E_LITERAL_LOGICO);
		break;
		}
	case LIT_CHAR:{
		pop(s);
		push_non_terminal(s, E_LITERAL_CARAC);
		break;
		}
	case LIT_INT:{
		pop(s);
		push_non_terminal(s, E_LITERAL_INT);
		break;
		}
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_LITERAL_FLUT);
		break;
		}
	default: error();
}} 

void _LITERAL_CARAC(){ switch (tok) {
	case LIT_CHAR:{
		pop(s);
		push_terminal(s,LIT_CHAR);
		break;
		}
	default: error();
}} 

void _LITERAL_FLUT(){ switch (tok) {
	case LIT_FLUT:{
		pop(s);
		push_terminal(s,LIT_FLUT);
		break;
		}
	default: error();
}} 

void _LITERAL_INT(){ switch (tok) {
	case LIT_INT:{
		pop(s);
		push_terminal(s,LIT_INT);
		break;
		}
	default: error();
}} 

void _LITERAL_LISTA(){ switch (tok) {
	case COL_ESQ:{
		pop(s);
		push_terminal(s,COL_DIR);
		push_non_terminal(s, E_LISTA_LITERAL_OU_VAZIO);
		push_non_terminal(s, E_LITERAL);
		push_terminal(s,COL_ESQ);
		break;
		}
	default: error();
}} 

void _LITERAL_LOGICO(){ switch (tok) {
	case VERDADEIRO:{
		pop(s);
		push_terminal(s,VERDADEIRO);
		break;
		}
	case FALSO:{
		pop(s);
		push_terminal(s,FALSO);
		break;
		}
	default: error();
}} 

void _MODIFICADORES_OU_VAZIO(){ switch (tok) {
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
	case EXP:{
		pop(s);
		break;
		}
	case COL_ESQ:
	case PONTO:{
		pop(s);
		push_non_terminal(s, E_MODIFICADORES_OU_VAZIO);
		push_non_terminal(s, E_MOD_TYPE);
		break;
		}
	default: error();
}} 

void _MOD_TYPE(){ switch (tok) {
	case COL_ESQ:{
		pop(s);
		push_terminal(s,COL_DIR);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,COL_ESQ);
		break;
		}
	case PONTO:{
		pop(s);
		push_terminal(s,ID);
		push_terminal(s,PONTO);
		break;
		}
	default: error();
}} 

void _NOVO_BLOCO(){ switch (tok) {
	case BLOCO:{
		pop(s);
		push_non_terminal(s, E_BLOCO);
		push_terminal(s,BLOCO);
		break;
		}
	default: error();
}} 

void _PARA(){ switch (tok) {
	case PARA:{
		pop(s);
		push_non_terminal(s, E_BLOCO);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_ATRIBUICAO);
		push_terminal(s,PONTO_VIRG);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,PONTO_VIRG);
		push_non_terminal(s, E_ATRIBUICAO);
		push_terminal(s,PAR_ESQ);
		push_terminal(s,PARA);
		break;
		}
	default: error();
}} 

void _PARAMETRO(){ switch (tok) {
	case ID:
	case REF:{
		pop(s);
		push_non_terminal(s, E_TIPO);
		push_terminal(s,DOIS_PONTOS);
		push_terminal(s,ID);
		push_non_terminal(s, E_TALVEZ_REF);
		break;
		}
	default: error();
}} 

void _PARAMETROS_OU_VAZIO(){ switch (tok) {
	case ID:
	case REF:{
		pop(s);
		push_non_terminal(s, E_LISTA_PARAMETROS_OU_VAZIO);
		push_non_terminal(s, E_PARAMETRO);
		break;
		}
	case PAR_DIR:{
		pop(s);
		break;
		}
	default: error();
}} 

void _PROGRAMA(){ switch (tok) {
	case CONST:
	case DECLRS:
	case BLOCO:{
		pop(s);
		push_non_terminal(s, E_NOVO_BLOCO);
		push_non_terminal(s, E_DECLARACOES);
		push_non_terminal(s, E_DEFINICOES);
		break;
		}
	default: error();
}} 

void _REGISTRO(){ switch (tok) {
	case ESTRUTURA:{
		pop(s);
		push_terminal(s,CHA_DIR);
		push_non_terminal(s, E_LISTA_DEC_VAR);
		push_non_terminal(s, E_DEC_VAR);
		push_terminal(s,CHA_ESQ);
		push_terminal(s,ESTRUTURA);
		break;
		}
	default: error();
}} 

void _REPETICAO(){ switch (tok) {
	case ENQUANTO:{
		pop(s);
		push_non_terminal(s, E_ENQUANTO);
		break;
		}
	case FACA:{
		pop(s);
		push_non_terminal(s, E_FACA_ENQUANTO);
		break;
		}
	case PARA:{
		pop(s);
		push_non_terminal(s, E_PARA);
		break;
		}
	default: error();
}} 

void _RETORNO(){ switch (tok) {
	case RETORNE:{
		pop(s);
		push_non_terminal(s, E_EXPR_OU_VAZIO);
		push_terminal(s,RETORNE);
		break;
		}
	default: error();
}} 

void _SE(){ switch (tok) {
	case SE:{
		pop(s);
		push_non_terminal(s, E_SENAO_OU_VAZIO);
		push_non_terminal(s, E_BLOCO);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,PAR_ESQ);
		push_terminal(s,SE);
		break;
		}
	default: error();
}} 

void _SENAO_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:
	case PONTO_VIRG:{
		pop(s);
		break;
		}
	case SENAO:{
		pop(s);
		push_non_terminal(s, E_BLOCO_OU_SE);
		push_terminal(s,SENAO);
		break;
		}
	default: error();
}} 

void _TALVEZ_REF(){ switch (tok) {
	case ID:{
		pop(s);
		break;
		}
	case REF:{
		pop(s);
		push_terminal(s,REF);
		break;
		}
	default: error();
}} 

void _TIPO(){ switch (tok) {
	case ID:
	case INT:
	case LOGICO:
	case FLUT:
	case CARAC:
	case ESTRUTURA:{
		pop(s);
		push_non_terminal(s, E_COLCHETES_OU_VAZIO);
		push_non_terminal(s, E_TIPO_PREF);
		break;
		}
	default: error();
}} 

void _TIPO_PREF(){ switch (tok) {
	case ID:{
		pop(s);
		push_terminal(s,ID);
		break;
		}
	case INT:
	case LOGICO:
	case FLUT:
	case CARAC:{
		pop(s);
		push_non_terminal(s, E_TIPO_SIMPLES);
		break;
		}
	case ESTRUTURA:{
		pop(s);
		push_non_terminal(s, E_REGISTRO);
		break;
		}
	default: error();
}} 

void _TIPO_SIMPLES(){ switch (tok) {
	case INT:{
		pop(s);
		push_terminal(s,INT);
		break;
		}
	case LOGICO:{
		pop(s);
		push_terminal(s,LOGICO);
		break;
		}
	case FLUT:{
		pop(s);
		push_terminal(s,FLUT);
		break;
		}
	case CARAC:{
		pop(s);
		push_terminal(s,CARAC);
		break;
		}
	default: error();
}} 

void _T_AND(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_T_AND_P);
		push_non_terminal(s, E_T_REL);
		break;
		}
	default: error();
}} 

void _T_AND_P(){ switch (tok) {
	case CHA_DIR:
	case PONTO_VIRG:
	case VIRGULA:
	case PAR_DIR:
	case COL_DIR:
	case OU:
	case E:{
		pop(s);
		break;
		}
	case IGUAL_IGUAL:{
		pop(s);
		push_non_terminal(s, E_T_AND_P);
		push_non_terminal(s, E_T_REL);
		push_terminal(s,IGUAL_IGUAL);
		break;
		}
	case DIFERENTE:{
		pop(s);
		push_non_terminal(s, E_T_AND_P);
		push_non_terminal(s, E_T_REL);
		push_terminal(s,DIFERENTE);
		break;
		}
	case MENOR_IGUAL:{
		pop(s);
		push_non_terminal(s, E_T_AND_P);
		push_non_terminal(s, E_T_REL);
		push_terminal(s,MENOR_IGUAL);
		break;
		}
	case MAIOR_IGUAL:{
		pop(s);
		push_non_terminal(s, E_T_AND_P);
		push_non_terminal(s, E_T_REL);
		push_terminal(s,MAIOR_IGUAL);
		break;
		}
	case MENOR:{
		pop(s);
		push_non_terminal(s, E_T_AND_P);
		push_non_terminal(s, E_T_REL);
		push_terminal(s,MENOR);
		break;
		}
	case MAIOR:{
		pop(s);
		push_non_terminal(s, E_T_AND_P);
		push_non_terminal(s, E_T_REL);
		push_terminal(s,MAIOR);
		break;
		}
	default: error();
}} 

void _T_ARIT(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_T_ARIT_P);
		push_non_terminal(s, E_T_FATOR);
		break;
		}
	default: error();
}} 

void _T_ARIT_P(){ switch (tok) {
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
	case MENOS:{
		pop(s);
		break;
		}
	case MULT:{
		pop(s);
		push_non_terminal(s, E_T_ARIT_P);
		push_non_terminal(s, E_T_FATOR);
		push_terminal(s,MULT);
		break;
		}
	case DIV:{
		pop(s);
		push_non_terminal(s, E_T_ARIT_P);
		push_non_terminal(s, E_T_FATOR);
		push_terminal(s,DIV);
		break;
		}
	case MOD:{
		pop(s);
		push_non_terminal(s, E_T_ARIT_P);
		push_non_terminal(s, E_T_FATOR);
		push_terminal(s,MOD);
		break;
		}
	default: error();
}} 

void _T_EXPO(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_T_UN);
		break;
		}
	default: error();
}} 

void _T_FATOR(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_T_FATOR_P);
		push_non_terminal(s, E_T_EXPO);
		break;
		}
	default: error();
}} 

void _T_FATOR_P(){ switch (tok) {
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
	case MOD:{
		pop(s);
		break;
		}
	case EXP:{
		pop(s);
		push_non_terminal(s, E_T_FATOR);
		push_terminal(s,EXP);
		break;
		}
	default: error();
}} 

void _T_OR(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_T_OR_P);
		push_non_terminal(s, E_T_AND);
		break;
		}
	default: error();
}} 

void _T_OR_P(){ switch (tok) {
	case CHA_DIR:
	case PONTO_VIRG:
	case VIRGULA:
	case PAR_DIR:
	case COL_DIR:
	case OU:{
		pop(s);
		break;
		}
	case E:{
		pop(s);
		push_non_terminal(s, E_T_OR_P);
		push_non_terminal(s, E_T_AND);
		push_terminal(s,E);
		break;
		}
	default: error();
}} 

void _T_PAR_ID(){ switch (tok) {
	case ID:
	case COL_ESQ:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_EXPR_FOLHA);
		break;
		}
	case PAR_ESQ:{
		pop(s);
		push_terminal(s,PAR_DIR);
		push_non_terminal(s, E_EXPR);
		push_terminal(s,PAR_ESQ);
		break;
		}
	default: error();
}} 

void _T_REL(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case MAIS:
	case MENOS:
	case NAO:
	case CAST:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_T_REL_P);
		push_non_terminal(s, E_T_ARIT);
		break;
		}
	default: error();
}} 

void _T_REL_P(){ switch (tok) {
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
	case MAIOR:{
		pop(s);
		break;
		}
	case MAIS:{
		pop(s);
		push_non_terminal(s, E_T_REL_P);
		push_non_terminal(s, E_T_ARIT);
		push_terminal(s,MAIS);
		break;
		}
	case MENOS:{
		pop(s);
		push_non_terminal(s, E_T_REL_P);
		push_non_terminal(s, E_T_ARIT);
		push_terminal(s,MENOS);
		break;
		}
	default: error();
}} 

void _T_UN(){ switch (tok) {
	case ID:
	case PAR_ESQ:
	case COL_ESQ:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		pop(s);
		push_non_terminal(s, E_T_PAR_ID);
		break;
		}
	case MAIS:{
		pop(s);
		push_non_terminal(s, E_T_UN);
		push_terminal(s,MAIS);
		break;
		}
	case MENOS:{
		pop(s);
		push_non_terminal(s, E_T_UN);
		push_terminal(s,MENOS);
		break;
		}
	case NAO:{
		pop(s);
		push_non_terminal(s, E_T_UN);
		push_terminal(s,NAO);
		break;
		}
	case CAST:{
		pop(s);
		push_non_terminal(s, E_T_UN);
		push_non_terminal(s, E_CAST);
		break;
		}
	default: error();
}} 

int main(){
  s = create_stack();

  push_non_terminal(s, E_PROGRAMA);
  advance();


  while(s->size > 0){
    Symbol* s_top = top(s);
    printf("SIZE: %d\n", s->size);
    printf("O PROXIMO TOKEN EH...... %d !!!!\n", tok);
    if(s_top->is_tok == 1){
      printf("EU SOU TOKEN: %d\n", s_top->type.tok);
      eat(s_top->type.tok);
      pop(s);
    }else{ // eh nao terminal
      printf("EU SOU RECURSIVO: %d\n", s_top->type.rule);
      assert(s_top->is_tok == 0);
      switch (s_top->type.rule) {
				case E_ARGS_FUNC_OU_VAZIO: _ARGS_FUNC_OU_VAZIO(); break;
				case E_ATRIBUICAO: _ATRIBUICAO(); break;
				case E_BLOCO: _BLOCO(); break;
				case E_BLOCO_OU_SE: _BLOCO_OU_SE(); break;
				case E_CASOS_ESCOLHA: _CASOS_ESCOLHA(); break;
				case E_CASO_ESCOLHA: _CASO_ESCOLHA(); break;
				case E_CASO_ESCOLHA_P: _CASO_ESCOLHA_P(); break;
				case E_CAST: _CAST(); break;
				case E_CHAMADA_FUNC_OU_VAZIO: _CHAMADA_FUNC_OU_VAZIO(); break;
				case E_COLCHETES_OU_VAZIO: _COLCHETES_OU_VAZIO(); break;
				case E_COMANDO: _COMANDO(); break;
				case E_CONTROLE: _CONTROLE(); break;
				case E_C_EXPR: _C_EXPR(); break;
				case E_C_EXPR_P: _C_EXPR_P(); break;
				case E_C_T_AND: _C_T_AND(); break;
				case E_C_T_AND_P: _C_T_AND_P(); break;
				case E_C_T_ARIC_T_P: _C_T_ARIC_T_P(); break;
				case E_C_T_ARIT: _C_T_ARIT(); break;
				case E_C_T_EXPO: _C_T_EXPO(); break;
				case E_C_T_FATOR: _C_T_FATOR(); break;
				case E_C_T_FATOR_P: _C_T_FATOR_P(); break;
				case E_C_T_OR: _C_T_OR(); break;
				case E_C_T_OR_P: _C_T_OR_P(); break;
				case E_C_T_PAR_ID: _C_T_PAR_ID(); break;
				case E_C_T_REL: _C_T_REL(); break;
				case E_C_T_REL_P: _C_T_REL_P(); break;
				case E_C_T_UN: _C_T_UN(); break;
				case E_DECLARACAO: _DECLARACAO(); break;
				case E_DECLARACOES: _DECLARACOES(); break;
				case E_DEC_FUNC: _DEC_FUNC(); break;
				case E_DEC_PROC: _DEC_PROC(); break;
				case E_DEC_TIPO: _DEC_TIPO(); break;
				case E_DEC_VAR: _DEC_VAR(); break;
				case E_DEFINICAO: _DEFINICAO(); break;
				case E_DEFINICOES: _DEFINICOES(); break;
				case E_ENQUANTO: _ENQUANTO(); break;
				case E_ESCOLHA: _ESCOLHA(); break;
				case E_ESCOLHA_PADRAO: _ESCOLHA_PADRAO(); break;
				case E_EXPR: _EXPR(); break;
				case E_EXPR_FOLHA: _EXPR_FOLHA(); break;
				case E_EXPR_OU_VAZIO: _EXPR_OU_VAZIO(); break;
				case E_EXPR_P: _EXPR_P(); break;
				case E_FACA_ENQUANTO: _FACA_ENQUANTO(); break;
				case E_IDS_OU_VAZIO: _IDS_OU_VAZIO(); break;
				case E_LISTA_COMANDOS_OU_VAZIO: _LISTA_COMANDOS_OU_VAZIO(); break;
				case E_LISTA_DECLARACOES_OU_VAZIO: _LISTA_DECLARACOES_OU_VAZIO(); break;
				case E_LISTA_DEC_VAR: _LISTA_DEC_VAR(); break;
				case E_LISTA_DEFINICOES_OU_VAZIO: _LISTA_DEFINICOES_OU_VAZIO(); break;
				case E_LISTA_EXPR_OU_VAZIO: _LISTA_EXPR_OU_VAZIO(); break;
				case E_LISTA_LITERAL_OU_VAZIO: _LISTA_LITERAL_OU_VAZIO(); break;
				case E_LISTA_PARAMETROS_OU_VAZIO: _LISTA_PARAMETROS_OU_VAZIO(); break;
				case E_LITERAL: _LITERAL(); break;
				case E_LITERAL_CARAC: _LITERAL_CARAC(); break;
				case E_LITERAL_FLUT: _LITERAL_FLUT(); break;
				case E_LITERAL_INT: _LITERAL_INT(); break;
				case E_LITERAL_LISTA: _LITERAL_LISTA(); break;
				case E_LITERAL_LOGICO: _LITERAL_LOGICO(); break;
				case E_MODIFICADORES_OU_VAZIO: _MODIFICADORES_OU_VAZIO(); break;
				case E_MOD_TYPE: _MOD_TYPE(); break;
				case E_NOVO_BLOCO: _NOVO_BLOCO(); break;
				case E_PARA: _PARA(); break;
				case E_PARAMETRO: _PARAMETRO(); break;
				case E_PARAMETROS_OU_VAZIO: _PARAMETROS_OU_VAZIO(); break;
				case E_PROGRAMA: _PROGRAMA(); break;
				case E_REGISTRO: _REGISTRO(); break;
				case E_REPETICAO: _REPETICAO(); break;
				case E_RETORNO: _RETORNO(); break;
				case E_SE: _SE(); break;
				case E_SENAO_OU_VAZIO: _SENAO_OU_VAZIO(); break;
				case E_TALVEZ_REF: _TALVEZ_REF(); break;
				case E_TIPO: _TIPO(); break;
				case E_TIPO_PREF: _TIPO_PREF(); break;
				case E_TIPO_SIMPLES: _TIPO_SIMPLES(); break;
				case E_T_AND: _T_AND(); break;
				case E_T_AND_P: _T_AND_P(); break;
				case E_T_ARIT: _T_ARIT(); break;
				case E_T_ARIT_P: _T_ARIT_P(); break;
				case E_T_EXPO: _T_EXPO(); break;
				case E_T_FATOR: _T_FATOR(); break;
				case E_T_FATOR_P: _T_FATOR_P(); break;
				case E_T_OR: _T_OR(); break;
				case E_T_OR_P: _T_OR_P(); break;
				case E_T_PAR_ID: _T_PAR_ID(); break;
				case E_T_REL: _T_REL(); break;
				case E_T_REL_P: _T_REL_P(); break;
				case E_T_UN: _T_UN(); break;
        default: error();
      }
    }
  } 
}