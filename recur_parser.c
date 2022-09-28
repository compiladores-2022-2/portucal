#include "src/token_id.h"
#include "src/lex.yy.c"

enum TOKEN_ID tok;
void advance() {
  tok=yylex();
}
void error() {
  1/0;
  exit(0);
}
void eat(enum TOKEN_ID t) {
  if (tok==t) advance(); 
  else error();
}

void _ARGS_FUNC_OU_VAZIO();
void _ATRIBUICAO();
void _ATRIBUICAO_OU_CHAMADA_PROC();
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
		_EXPR(); _LISTA_EXPR_OU_VAZIO(); break;
	}
	case PAR_DIR:{
		 break;
	}
	default: error();
}} 

void _ATRIBUICAO(){ switch (tok) {
	case ID:{
		eat(ID); _MODIFICADORES_OU_VAZIO(); eat(IGUAL); _EXPR(); break;
	}
	default: error();
}} 

void _ATRIBUICAO_OU_CHAMADA_PROC(){ switch (tok) {
	case IGUAL:
	case COL_ESQ:
	case PONTO:{
		_MODIFICADORES_OU_VAZIO(); eat(IGUAL); _EXPR(); break;
	}
	case PAR_ESQ:{
		eat(PAR_ESQ); _ARGS_FUNC_OU_VAZIO(); eat(PAR_DIR); break;
	}
	default: error();
}} 

void _BLOCO(){ switch (tok) {
	case CHA_ESQ:{
		eat(CHA_ESQ); _DECLARACOES(); _COMANDO(); _LISTA_COMANDOS_OU_VAZIO(); eat(CHA_DIR); break;
	}
	default: error();
}} 

void _BLOCO_OU_SE(){ switch (tok) {
	case CHA_ESQ:{
		_BLOCO(); break;
	}
	case SE:{
		_SE(); break;
	}
	default: error();
}} 

void _CASOS_ESCOLHA(){ switch (tok) {
	case CASO:{
		_CASO_ESCOLHA(); _CASO_ESCOLHA_P(); break;
	}
	case PADRAO:{
		_ESCOLHA_PADRAO(); break;
	}
	default: error();
}} 

void _CASO_ESCOLHA(){ switch (tok) {
	case CASO:{
		eat(CASO); _C_EXPR(); eat(DOIS_PONTOS); _COMANDO(); eat(PONTO_VIRG); break;
	}
	default: error();
}} 

void _CASO_ESCOLHA_P(){ switch (tok) {
	case CHA_DIR:{
		 break;
	}
	case CASO:
	case PADRAO:{
		_CASOS_ESCOLHA(); break;
	}
	default: error();
}} 

void _CAST(){ switch (tok) {
	case CAST:{
		eat(CAST); _TIPO(); eat(CAST); break;
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
		 break;
	}
	case PAR_ESQ:{
		eat(PAR_ESQ); _ARGS_FUNC_OU_VAZIO(); eat(PAR_DIR); break;
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
		 break;
	}
	case COL_ESQ:{
		eat(COL_ESQ); _C_EXPR(); eat(COL_DIR); _COLCHETES_OU_VAZIO(); break;
	}
	default: error();
}} 

void _COMANDO(){ switch (tok) {
	case ID:{
		eat(ID); _ATRIBUICAO_OU_CHAMADA_PROC(); break;
	}
	case BLOCO:{
		_NOVO_BLOCO(); break;
	}
	case CONTINUE:{
		eat(CONTINUE); break;
	}
	case PARE:{
		eat(PARE); break;
	}
	case ESCREVA:{
		eat(ESCREVA); eat(PAR_ESQ); _EXPR(); _LISTA_EXPR_OU_VAZIO(); eat(PAR_DIR); break;
	}
	case LEIA:{
		eat(LEIA); eat(PAR_ESQ); eat(ID); _MODIFICADORES_OU_VAZIO(); eat(PAR_DIR); break;
	}
	case SE:
	case ESCOLHA:{
		_CONTROLE(); break;
	}
	case ENQUANTO:
	case FACA:
	case PARA:{
		_REPETICAO(); break;
	}
	case RETORNE:{
		_RETORNO(); break;
	}
	default: error();
}} 

void _CONTROLE(){ switch (tok) {
	case SE:{
		_SE(); break;
	}
	case ESCOLHA:{
		_ESCOLHA(); break;
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
		_C_T_OR(); _C_EXPR_P(); break;
	}
	default: error();
}} 

void _C_EXPR_P(){ switch (tok) {
	case DOIS_PONTOS:
	case PAR_DIR:
	case COL_DIR:{
		 break;
	}
	case OU:{
		eat(OU); _C_T_OR(); _C_EXPR_P(); break;
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
		_C_T_REL(); _C_T_AND_P(); break;
	}
	default: error();
}} 

void _C_T_AND_P(){ switch (tok) {
	case DOIS_PONTOS:
	case PAR_DIR:
	case COL_DIR:
	case OU:
	case E:{
		 break;
	}
	case IGUAL_IGUAL:{
		eat(IGUAL_IGUAL); _C_T_REL(); _C_T_AND_P(); break;
	}
	case DIFERENTE:{
		eat(DIFERENTE); _C_T_REL(); _C_T_AND_P(); break;
	}
	case MENOR_IGUAL:{
		eat(MENOR_IGUAL); _C_T_REL(); _C_T_AND_P(); break;
	}
	case MAIOR_IGUAL:{
		eat(MAIOR_IGUAL); _C_T_REL(); _C_T_AND_P(); break;
	}
	case MENOR:{
		eat(MENOR); _C_T_REL(); _C_T_AND_P(); break;
	}
	case MAIOR:{
		eat(MAIOR); _C_T_REL(); _C_T_AND_P(); break;
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
		 break;
	}
	case MULT:{
		eat(MULT); _C_T_FATOR(); _C_T_ARIC_T_P(); break;
	}
	case DIV:{
		eat(DIV); _C_T_FATOR(); _C_T_ARIC_T_P(); break;
	}
	case MOD:{
		eat(MOD); _C_T_FATOR(); _C_T_ARIC_T_P(); break;
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
		_C_T_FATOR(); _C_T_ARIC_T_P(); break;
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
		_C_T_UN(); break;
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
		_C_T_EXPO(); _C_T_FATOR_P(); break;
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
		 break;
	}
	case EXP:{
		eat(EXP); _C_T_FATOR(); break;
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
		_C_T_AND(); _C_T_OR_P(); break;
	}
	default: error();
}} 

void _C_T_OR_P(){ switch (tok) {
	case DOIS_PONTOS:
	case PAR_DIR:
	case COL_DIR:
	case OU:{
		 break;
	}
	case E:{
		eat(E); _C_T_AND(); _C_T_OR_P(); break;
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
		_EXPR_FOLHA(); break;
	}
	case PAR_ESQ:{
		eat(PAR_ESQ); _C_EXPR(); eat(PAR_DIR); break;
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
		_C_T_ARIT(); _C_T_REL_P(); break;
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
		 break;
	}
	case MAIS:{
		eat(MAIS); _C_T_ARIT(); _C_T_REL_P(); break;
	}
	case MENOS:{
		eat(MENOS); _C_T_ARIT(); _C_T_REL_P(); break;
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
		_C_T_PAR_ID(); break;
	}
	case MAIS:{
		eat(MAIS); _C_T_UN(); break;
	}
	case MENOS:{
		eat(MENOS); _C_T_UN(); break;
	}
	case NAO:{
		eat(NAO); _C_T_UN(); break;
	}
	case CAST:{
		_CAST(); _C_T_UN(); break;
	}
	default: error();
}} 

void _DECLARACAO(){ switch (tok) {
	case VAR:{
		_DEC_VAR(); break;
	}
	case PROC:{
		_DEC_PROC(); break;
	}
	case FUNC:{
		_DEC_FUNC(); break;
	}
	case TIPO:{
		_DEC_TIPO(); break;
	}
	default: error();
}} 

void _DECLARACOES(){ switch (tok) {
	case DECLRS:{
		eat(DECLRS); eat(CHA_ESQ); _DECLARACAO(); _LISTA_DECLARACOES_OU_VAZIO(); eat(CHA_DIR); break;
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
		 break;
	}
	default: error();
}} 

void _DEC_FUNC(){ switch (tok) {
	case FUNC:{
		eat(FUNC); eat(ID); eat(PAR_ESQ); _PARAMETROS_OU_VAZIO(); eat(PAR_DIR); eat(DOIS_PONTOS); _TIPO(); _BLOCO(); break;
	}
	default: error();
}} 

void _DEC_PROC(){ switch (tok) {
	case PROC:{
		eat(PROC); eat(ID); eat(PAR_ESQ); _PARAMETROS_OU_VAZIO(); eat(PAR_DIR); _BLOCO(); break;
	}
	default: error();
}} 

void _DEC_TIPO(){ switch (tok) {
	case TIPO:{
		eat(TIPO); eat(ID); eat(IGUAL); _TIPO(); break;
	}
	default: error();
}} 

void _DEC_VAR(){ switch (tok) {
	case VAR:{
		eat(VAR); eat(ID); _IDS_OU_VAZIO(); eat(DOIS_PONTOS); _TIPO(); break;
	}
	default: error();
}} 

void _DEFINICAO(){ switch (tok) {
	case ID:{
		eat(ID); eat(IGUAL); _LITERAL(); break;
	}
	default: error();
}} 

void _DEFINICOES(){ switch (tok) {
	case CONST:{
		eat(CONST); eat(CHA_ESQ); _DEFINICAO(); _LISTA_DEFINICOES_OU_VAZIO(); eat(CHA_DIR); break;
	}
	case DECLRS:
	case BLOCO:{
		 break;
	}
	default: error();
}} 

void _ENQUANTO(){ switch (tok) {
	case ENQUANTO:{
		eat(ENQUANTO); eat(PAR_ESQ); _EXPR(); eat(PAR_DIR); _BLOCO(); break;
	}
	default: error();
}} 

void _ESCOLHA(){ switch (tok) {
	case ESCOLHA:{
		eat(ESCOLHA); eat(PAR_ESQ); _EXPR(); eat(PAR_DIR); eat(CHA_ESQ); _CASOS_ESCOLHA(); eat(CHA_DIR); break;
	}
	default: error();
}} 

void _ESCOLHA_PADRAO(){ switch (tok) {
	case PADRAO:{
		eat(PADRAO); eat(DOIS_PONTOS); _COMANDO(); eat(PONTO_VIRG); break;
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
		_T_OR(); _EXPR_P(); break;
	}
	default: error();
}} 

void _EXPR_FOLHA(){ switch (tok) {
	case ID:{
		eat(ID); _CHAMADA_FUNC_OU_VAZIO(); _MODIFICADORES_OU_VAZIO(); break;
	}
	case COL_ESQ:
	case VERDADEIRO:
	case FALSO:
	case LIT_CHAR:
	case LIT_INT:
	case LIT_FLUT:{
		_LITERAL(); break;
	}
	default: error();
}} 

void _EXPR_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:
	case PONTO_VIRG:{
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
		_EXPR(); break;
	}
	default: error();
}} 

void _EXPR_P(){ switch (tok) {
	case CHA_DIR:
	case PONTO_VIRG:
	case VIRGULA:
	case PAR_DIR:
	case COL_DIR:{
		 break;
	}
	case OU:{
		eat(OU); _T_OR(); _EXPR_P(); break;
	}
	default: error();
}} 

void _FACA_ENQUANTO(){ switch (tok) {
	case FACA:{
		eat(FACA); _BLOCO(); eat(ENQUANTO); eat(PAR_ESQ); _EXPR(); eat(PAR_DIR); break;
	}
	default: error();
}} 

void _IDS_OU_VAZIO(){ switch (tok) {
	case DOIS_PONTOS:{
		 break;
	}
	case VIRGULA:{
		eat(VIRGULA); eat(ID); _IDS_OU_VAZIO(); break;
	}
	default: error();
}} 

void _LISTA_COMANDOS_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:{
		 break;
	}
	case PONTO_VIRG:{
		eat(PONTO_VIRG); _COMANDO(); _LISTA_COMANDOS_OU_VAZIO(); break;
	}
	default: error();
}} 

void _LISTA_DECLARACOES_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:{
		 break;
	}
	case PONTO_VIRG:{
		eat(PONTO_VIRG); _DECLARACAO(); _LISTA_DECLARACOES_OU_VAZIO(); break;
	}
	default: error();
}} 

void _LISTA_DEC_VAR(){ switch (tok) {
	case CHA_DIR:{
		 break;
	}
	case PONTO_VIRG:{
		eat(PONTO_VIRG); _LISTA_DEC_VAR(); break;
	}
	default: error();
}} 

void _LISTA_DEFINICOES_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:{
		 break;
	}
	case PONTO_VIRG:{
		eat(PONTO_VIRG); _DEFINICAO(); _LISTA_DEFINICOES_OU_VAZIO(); break;
	}
	default: error();
}} 

void _LISTA_EXPR_OU_VAZIO(){ switch (tok) {
	case VIRGULA:{
		eat(VIRGULA); _EXPR(); _LISTA_EXPR_OU_VAZIO(); break;
	}
	case PAR_DIR:{
		 break;
	}
	default: error();
}} 

void _LISTA_LITERAL_OU_VAZIO(){ switch (tok) {
	case VIRGULA:{
		eat(VIRGULA); _LITERAL(); _LISTA_LITERAL_OU_VAZIO(); break;
	}
	case COL_DIR:{
		 break;
	}
	default: error();
}} 

void _LISTA_PARAMETROS_OU_VAZIO(){ switch (tok) {
	case VIRGULA:{
		eat(VIRGULA); _PARAMETRO(); _LISTA_PARAMETROS_OU_VAZIO(); break;
	}
	case PAR_DIR:{
		 break;
	}
	default: error();
}} 

void _LITERAL(){ switch (tok) {
	case COL_ESQ:{
		_LITERAL_LISTA(); break;
	}
	case VERDADEIRO:
	case FALSO:{
		_LITERAL_LOGICO(); break;
	}
	case LIT_CHAR:{
		_LITERAL_CARAC(); break;
	}
	case LIT_INT:{
		_LITERAL_INT(); break;
	}
	case LIT_FLUT:{
		_LITERAL_FLUT(); break;
	}
	default: error();
}} 

void _LITERAL_CARAC(){ switch (tok) {
	case LIT_CHAR:{
		eat(LIT_CHAR); break;
	}
	default: error();
}} 

void _LITERAL_FLUT(){ switch (tok) {
	case LIT_FLUT:{
		eat(LIT_FLUT); break;
	}
	default: error();
}} 

void _LITERAL_INT(){ switch (tok) {
	case LIT_INT:{
		eat(LIT_INT); break;
	}
	default: error();
}} 

void _LITERAL_LISTA(){ switch (tok) {
	case COL_ESQ:{
		eat(COL_ESQ); _LITERAL(); _LISTA_LITERAL_OU_VAZIO(); eat(COL_DIR); break;
	}
	default: error();
}} 

void _LITERAL_LOGICO(){ switch (tok) {
	case VERDADEIRO:{
		eat(VERDADEIRO); break;
	}
	case FALSO:{
		eat(FALSO); break;
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
		 break;
	}
	case COL_ESQ:
	case PONTO:{
		_MOD_TYPE(); _MODIFICADORES_OU_VAZIO(); break;
	}
	default: error();
}} 

void _MOD_TYPE(){ switch (tok) {
	case COL_ESQ:{
		eat(COL_ESQ); _EXPR(); eat(COL_DIR); break;
	}
	case PONTO:{
		eat(PONTO); eat(ID); break;
	}
	default: error();
}} 

void _NOVO_BLOCO(){ switch (tok) {
	case BLOCO:{
		eat(BLOCO); _BLOCO(); break;
	}
	default: error();
}} 

void _PARA(){ switch (tok) {
	case PARA:{
		eat(PARA); eat(PAR_ESQ); _ATRIBUICAO(); eat(PONTO_VIRG); _EXPR(); eat(PONTO_VIRG); _ATRIBUICAO(); eat(PAR_DIR); _BLOCO(); break;
	}
	default: error();
}} 

void _PARAMETRO(){ switch (tok) {
	case ID:
	case REF:{
		_TALVEZ_REF(); eat(ID); eat(DOIS_PONTOS); _TIPO(); break;
	}
	default: error();
}} 

void _PARAMETROS_OU_VAZIO(){ switch (tok) {
	case ID:
	case REF:{
		_PARAMETRO(); _LISTA_PARAMETROS_OU_VAZIO(); break;
	}
	case PAR_DIR:{
		 break;
	}
	default: error();
}} 

void _PROGRAMA(){ switch (tok) {
	case CONST:
	case DECLRS:
	case BLOCO:{
		_DEFINICOES(); _DECLARACOES(); _NOVO_BLOCO(); break;
	}
	default: error();
}} 

void _REGISTRO(){ switch (tok) {
	case ESTRUTURA:{
		eat(ESTRUTURA); eat(CHA_ESQ); _DEC_VAR(); _LISTA_DEC_VAR(); eat(CHA_DIR); break;
	}
	default: error();
}} 

void _REPETICAO(){ switch (tok) {
	case ENQUANTO:{
		_ENQUANTO(); break;
	}
	case FACA:{
		_FACA_ENQUANTO(); break;
	}
	case PARA:{
		_PARA(); break;
	}
	default: error();
}} 

void _RETORNO(){ switch (tok) {
	case RETORNE:{
		eat(RETORNE); _EXPR_OU_VAZIO(); break;
	}
	default: error();
}} 

void _SE(){ switch (tok) {
	case SE:{
		eat(SE); eat(PAR_ESQ); _EXPR(); eat(PAR_DIR); _BLOCO(); _SENAO_OU_VAZIO(); break;
	}
	default: error();
}} 

void _SENAO_OU_VAZIO(){ switch (tok) {
	case CHA_DIR:
	case PONTO_VIRG:{
		 break;
	}
	case SENAO:{
		eat(SENAO); _BLOCO_OU_SE(); break;
	}
	default: error();
}} 

void _TALVEZ_REF(){ switch (tok) {
	case ID:{
		 break;
	}
	case REF:{
		eat(REF); break;
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
		_TIPO_PREF(); _COLCHETES_OU_VAZIO(); break;
	}
	default: error();
}} 

void _TIPO_PREF(){ switch (tok) {
	case ID:{
		eat(ID); break;
	}
	case INT:
	case LOGICO:
	case FLUT:
	case CARAC:{
		_TIPO_SIMPLES(); break;
	}
	case ESTRUTURA:{
		_REGISTRO(); break;
	}
	default: error();
}} 

void _TIPO_SIMPLES(){ switch (tok) {
	case INT:{
		eat(INT); break;
	}
	case LOGICO:{
		eat(LOGICO); break;
	}
	case FLUT:{
		eat(FLUT); break;
	}
	case CARAC:{
		eat(CARAC); break;
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
		_T_REL(); _T_AND_P(); break;
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
		 break;
	}
	case IGUAL_IGUAL:{
		eat(IGUAL_IGUAL); _T_REL(); _T_AND_P(); break;
	}
	case DIFERENTE:{
		eat(DIFERENTE); _T_REL(); _T_AND_P(); break;
	}
	case MENOR_IGUAL:{
		eat(MENOR_IGUAL); _T_REL(); _T_AND_P(); break;
	}
	case MAIOR_IGUAL:{
		eat(MAIOR_IGUAL); _T_REL(); _T_AND_P(); break;
	}
	case MENOR:{
		eat(MENOR); _T_REL(); _T_AND_P(); break;
	}
	case MAIOR:{
		eat(MAIOR); _T_REL(); _T_AND_P(); break;
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
		_T_FATOR(); _T_ARIT_P(); break;
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
		 break;
	}
	case MULT:{
		eat(MULT); _T_FATOR(); _T_ARIT_P(); break;
	}
	case DIV:{
		eat(DIV); _T_FATOR(); _T_ARIT_P(); break;
	}
	case MOD:{
		eat(MOD); _T_FATOR(); _T_ARIT_P(); break;
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
		_T_UN(); break;
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
		_T_EXPO(); _T_FATOR_P(); break;
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
		 break;
	}
	case EXP:{
		eat(EXP); _T_FATOR(); break;
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
		_T_AND(); _T_OR_P(); break;
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
		 break;
	}
	case E:{
		eat(E); _T_AND(); _T_OR_P(); break;
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
		_EXPR_FOLHA(); break;
	}
	case PAR_ESQ:{
		eat(PAR_ESQ); _EXPR(); eat(PAR_DIR); break;
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
		_T_ARIT(); _T_REL_P(); break;
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
		 break;
	}
	case MAIS:{
		eat(MAIS); _T_ARIT(); _T_REL_P(); break;
	}
	case MENOS:{
		eat(MENOS); _T_ARIT(); _T_REL_P(); break;
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
		_T_PAR_ID(); break;
	}
	case MAIS:{
		eat(MAIS); _T_UN(); break;
	}
	case MENOS:{
		eat(MENOS); _T_UN(); break;
	}
	case NAO:{
		eat(NAO); _T_UN(); break;
	}
	case CAST:{
		_CAST(); _T_UN(); break;
	}
	default: error();
}} 


int main(){
  advance();
  _PROGRAMA();
}