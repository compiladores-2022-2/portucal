#include "src/token_id.h"
#include "lex.yy.c"

enum TOKEN_ID tok;
void advance() {
  tok=yylex();
}
void error() {
  1/0;
}
void eat(enum TOKEN_ID t) {
  if (tok==t) advance(); 
  else error();
}

void S();
void PROGRAMA();
void DEFINICOES();
void DECLARACOES();
void DEFINICAO();
void DECLARACAO();
void LISTA_DEFINICOES_OU_VAZIO();
void LISTA_DECLARACOES_OU_VAZIO();
void IDS_OU_VAZIO();
void DEC_VAR();
void DEC_PROC();
void TIPO_();
void DEC_FUNC();
void DEC_TIPO();
void TIPO_PREF();
void COLCHETES_OU_VAZIO();
void PARAMETRO();
void TIPO_SIMPLES();
void NOVO_BLOCO();
void LISTA_DEC_VAR();
void BLOCO_();
void ATRIBUICAO();
void LISTA_COMANDOS_OU_VAZIO();
void REGISTRO();
void COMANDO();
void CONTROLE();
void RETORNO();
void SE_();
void SENAO_OU_VAZIO();
void BLOCO_OU_SE();
void CASOS_ESCOLHA();
void CASO_ESCOLHA();
void CASO_ESCOLHA_P();
void ESCOLHA_PADRAO();
void REPETICAO();
void ESCOLHA_();
void ENQUANTO_();
void FACA_ENQUANTO();
void PARA_();
void EXPR_OU_VAZIO();
void EXPR();
void T_OR();
void EXPR_P();
void T_AND();
void T_OR_P();
void T_REL();
void T_AND_P();
void T_ARIT();
void T_REL_P();
void T_FATOR();
void T_ARIT_P();
void T_EXPO();
void T_FATOR_P();
void T_UN();
void T_PAR_ID();
void CAST_();
void EXPR_FOLHA();
void TIPO_();
void CHAMADA_FUNC_OU_VAZIO();
void MODIFICADORES_OU_VAZIO();
void MOD_TYPE();
void ARGS_FUNC_OU_VAZIO();
void EXPR();
void ARGS_FUNC_OU_VAZIO();
void ARGS_FUNC();
void LITERAL();
void LITERAL_LOGICO();
void LITERAL_CARAC();
void LITERAL_INT();
void LITERAL_FLUT();
void C_EXPR();
void C_EXPR_P();
void C_T_OR();
void C_T_OR_P();
void C_T_AND();
void C_T_AND_P();
void C_T_REL();
void C_T_REL_P();
void C_T_ARIT();
void C_T_ARIT_T_P();
void C_T_FATOR();
void C_T_FATOR_P();
void C_T_EXPO();
void C_T_UN();
void C_T_PAR_ID();


void S() { switch (tok) {
  case CONST: case DECLRS: case BLOCO:{
    PROGRAMA();
    break;
  }
 default: error();
}}

void PROGRAMA() { switch (tok) {
  case CONST: case DECLRS: case BLOCO:{
    DEFINICOES(); DECLARACOES(); NOVO_BLOCO();
    break;
  }
  default: error();
}}

void DEFINICOES() { switch (tok) {
  case CONST:{
    eat(CONST); eat(CHA_ESQ); DEFINICAO(); LISTA_DEFINICOES_OU_VAZIO(); eat(CHA_DIR);
    break;
  }
  case DECLRS: case BLOCO:{ break; }
  default: error();
}}

void LISTA_DEFINICOES_OU_VAZIO() { switch (tok) {
  case CHA_DIR:{ break; }
  case PONTO_VIRG: {
    eat(PONTO_VIRG); DEFINICAO(); LISTA_DEFINICOES_OU_VAZIO();
    break;
  }
  default: error();
}}

void DEFINICAO() { switch (tok) {
  case ID: {
    eat(ID); eat(IGUAL); LITERAL();
  }
  default: error();
}}

void DECLARACOES() { switch (tok) {
  case DECLRS: {
    eat(DECLRS); eat(CHA_ESQ); DECLARACAO(); LISTA_DECLARACOES_OU_VAZIO(); eat(CHA_DIR);
    break;
  }
  case ID: case BLOCO: case CONTINUE: case PARE: case SE: case ESCOLHA: case ENQUANTO: case FACA: case PARA: case RETORNE:{
    break;
  }
  default: error();
}}

void LISTA_DECLARACOES_OU_VAZIO() { switch (tok) {
  case CHA_DIR: { break; }
  case PONTO_VIRG: { 
    eat(PONTO_VIRG); DECLARACAO(); LISTA_DECLARACOES_OU_VAZIO();
  }
  default: error();
}}

void DECLARACAO() { switch (tok) {
  case VAR: {
    DEC_VAR();
    break;
  }
  case PROC: {
    DEC_PROC();
    break;
  }
  case FUNC: {
    DEC_FUNC();
    break;
  }
  case TIPO: {
    DEC_TIPO();
    break;
  }
  default: error();
}}

void DEC_VAR() { switch (tok) {
  case VAR: {
    eat(VAR); eat(ID); IDS_OU_VAZIO(); eat(DOIS_PONTOS); TIPO_();
  }
  default: error();
}}

void IDS_OU_VAZIO() { switch (tok) {
  case DOIS_PONTOS: { break; }
  case VIRGULA: {
    eat(VIRGULA); eat(ID); IDS_OU_VAZIO();
  }
  default: error();
}}

void LISTA_PARAMETROS_OU_VAZIO() { switch (tok) {
  case VIRGULA: {
    eat(VIRGULA); PARAMETRO(); LISTA_PARAMETROS_OU_VAZIO();
  }
  case PAR_DIR: { break; }
  default: error();
}}

void TALVEZ_REF() { switch (tok) {
  case ID: { break; }
  case REF: { 
    eat(REF); 
    break;
  }
  default: error();
}}

void PARAMETRO() { switch (tok) {
  case ID: case REF: {
    TALVEZ_REF(); eat(ID); eat(DOIS_PONTOS); TIPO_();
    break;
  }
  default: error();
}}

void PARAMETROS_OU_VAZIO() { switch (tok) {
  case ID: case REF: {
    PARAMETRO(); LISTA_PARAMETROS_OU_VAZIO();
    break;
  }
  case PAR_DIR: { break; }
  default: error();
}}

void DEC_PROC() { switch (tok) {
  case PROC: {
    eat(PROC); eat(ID); eat(PAR_ESQ); PARAMETROS_OU_VAZIO(); 
    eat(PAR_DIR); eat(DOIS_PONTOS); BLOCO_();
    break;
  }
  default: error();
}}

void DEC_FUNC() { switch (tok) {
  case FUNC: {
    eat(FUNC); eat(ID); eat(PAR_ESQ); PARAMETROS_OU_VAZIO(); 
    eat(PAR_DIR); eat(DOIS_PONTOS); TIPO_(); BLOCO_();
    break;
  }
  default: error();
}}

void DEC_TIPO() { switch (tok) {
  case TIPO: {
    eat(TIPO); eat(ID); eat(IGUAL); TIPO_();
    break;
  }
  default: error();
}}

void TIPO_() { switch (tok) {
  case ID: case INT: case LOGICO: case FLUT: case CARAC: case ESTRUTURA: {
    TIPO_PREF(); COLCHETES_OU_VAZIO();
    break;
  }
  default: error();
}}

void COLCHETES_OU_VAZIO() { switch (tok) {
  case CHA_ESQ: case CHA_DIR: case PONTO_VIRG: case VIRGULA: case PAR_DIR: case CAST: {
    break;
  }
  case COL_ESQ: {
    eat(COL_ESQ); C_EXPR(); eat(COL_DIR); COLCHETES_OU_VAZIO();
  }
  default: error();
}}

void TIPO_PREF() { switch (tok) {
  case ID: {
    eat(ID);
    break;
  }
  case INT: case LOGICO: case FLUT: case CARAC: {
    TIPO_SIMPLES();
    break;
  } 
  case ESTRUTURA: {
    REGISTRO();
    break;
  }
  default: error();
}}

void TIPO_SIMPLES() { switch (tok) {
  case INT: {
    eat(INT);
    break;
  }
  case LOGICO: {
    eat(LOGICO);
    break;
  }
  case FLUT: {
    eat(FLUT);
    break;
  }
  case CARAC: {
    eat(CARAC);
    break;
  }
  default: error();
}}

void REGISTRO() { switch (tok) {
  case ESTRUTURA: {
    eat(ESTRUTURA); eat(CHA_ESQ); DEC_VAR(); LISTA_DEC_VAR(); eat(CHA_DIR);
    break;
  }
  default: error();
}}

void LISTA_DEC_VAR() { switch (tok) {
  case CHA_DIR: { break; }
  case PONTO_VIRG: {
    eat(PONTO_VIRG); LISTA_DEC_VAR();
  }
  default: error();
}}

void NOVO_BLOCO() { switch (tok) {
  case BLOCO: {
    eat(BLOCO); BLOCO_();
    break;
  }
  default: error();
}}

void BLOCO_() { switch (tok) {
  case CHA_ESQ: {
    eat(CHA_ESQ); DECLARACOES(); COMANDO(); LISTA_COMANDOS_OU_VAZIO(); eat(CHA_DIR);
    break;
  }
  default: error();
}}

void LISTA_COMANDOS_OU_VAZIO() { switch (tok) {
  case CHA_DIR: { break; }
  case PONTO_VIRG: {
    eat(PONTO_VIRG); COMANDO(); LISTA_COMANDOS_OU_VAZIO();
    break;
  }
  default: error();
}}

void COMANDO() { switch (tok) {
  case ID: {
    ATRIBUICAO();
    break;
  }
  case BLOCO: {
    NOVO_BLOCO();
    break;
  }
  case CONTINUE: {
    eat(CONTINUE);
    break;
  }
  case PARE: {
    eat(PARE);
    break;
  }
  case SE: case ESCOLHA: {
    CONTROLE();
    break;
  }
  case ENQUANTO: case FACA: case PARA: {
    REPETICAO();
    break;
  }
  case RETORNE: {
    RETORNO();
    break;
  }
  default: error();
}}

void CONTROLE() { switch (tok) {
  case SE: {
    SE_();
    break;
  }
  case ESCOLHA: {
    ESCOLHA_();
    break;
  }
  default: error();
}}

void SE_() { switch (tok) {
  case SE: {
    eat(SE); eat(PAR_ESQ); EXPR(); eat(PAR_DIR); BLOCO_(); SENAO_OU_VAZIO();
    break;
  }
  default: error();
}}

void SENAO_OU_VAZIO() { switch (tok) {
  case CHA_DIR: case PONTO_VIRG: { break; }
  case SENAO: {
    eat(SENAO); BLOCO_OU_SE();
    break;;
  }
  default: error();
}}

void BLOCO_OU_SE() { switch (tok) {
  case CHA_ESQ: {
    BLOCO_();
    break;
  }
  case SE: {
    SE_();
    break;
  }
  default: error();
}}

void ESCOLHA_() { switch (tok) {
  case ESCOLHA: {
    eat(ESCOLHA); eat(PAR_ESQ); EXPR(); eat(PAR_DIR); eat(CHA_ESQ);
    CASOS_ESCOLHA(); eat(CHA_DIR);
    break;
  }
  default: error();
}}

void CASOS_ESCOLHA() { switch (tok) {
  case CASO: {
    CASO_ESCOLHA(); CASO_ESCOLHA_P();
    break;
  }
  case PADRAO: {
    ESCOLHA_PADRAO();
    break;
  }
  default: error();
}}

void CASO_ESCOLHA_P() { switch (tok) {
  case CHA_DIR: { break; }
  case CASO: case PADRAO: { 
    CASOS_ESCOLHA();
    break;
  }
  default: error();
}}

void CASO_ESCOLHA() { switch (tok) {
  case CASO: {
    eat(CASO); C_EXPR(); eat(DOIS_PONTOS); COMANDO(); eat(PONTO_VIRG);
    break;
  }
  default: error();
}}

void ESCOLHA_PADRAO() { switch (tok) {
  case PADRAO: {
    eat(PADRAO); eat(DOIS_PONTOS); COMANDO(); eat(PONTO_VIRG);
    break;
  }
  default: error();
}}

void REPETICAO() { switch (tok) {
  case ENQUANTO: {
    ENQUANTO_();
    break;
  }
  case FACA: {
    FACA_ENQUANTO();
    break;
  }
  case PARA: {
    PARA_();
    break;
  }
  default: error();
}}

void ENQUANTO_() { switch (tok) {
  case ENQUANTO: {
    eat(ENQUANTO); eat(PAR_ESQ); EXPR(); eat(PAR_DIR); BLOCO_();
    break;
  }
  default: error();
}}

void FACA_ENQUANTO() { switch (tok) {
  case FACA: {
    eat(FACA); BLOCO_(); COMANDO(); eat(ENQUANTO); eat(PAR_ESQ);
    EXPR(); eat(PAR_DIR);
    break;
  }
  default: error();
}}

void PARA_() { switch (tok) {
  case PARA: {
    eat(PARA); eat(PAR_ESQ); ATRIBUICAO(); eat(PONTO_VIRG);
    EXPR(); eat(PONTO_VIRG); ATRIBUICAO(); eat(PAR_DIR); BLOCO_();
    break;
  }
  default: error();
}}

void ATRIBUICAO() { switch (tok) {
  case ID: {
    eat(ID); MODIFICADORES_OU_VAZIO(); eat(IGUAL); EXPR();
    break;
  }
  default: error();
}}

void RETORNO() { switch (tok) {
  case RETORNE: {
    eat(RETORNE); EXPR_OU_VAZIO();
    break;
  }
  default: error();
}}

void EXPR_OU_VAZIO() { switch (tok) {
    case CHA_DIR: case PONTO_VIRG : {
        break;
    }
    case ID: case PAR_ESQ: case MAIS:
    case MENOS: case NAO: case CAST: case VERDADEIRO:
    case FALSO: case ALPHA: case NUM_INT: case NUM_FLUT : {
        EXPR();
        break;
    }
    default: error();
}}

void EXPR() { switch (tok) {
    case ID: case PAR_ESQ: case MAIS:
    case MENOS: case NAO: case CAST: case VERDADEIRO:
    case FALSO: case ALPHA: case NUM_INT: case NUM_FLUT : {
        T_OR(); EXPR_P();
        break;
    }
    default: error();
}}

void EXPR_P() { switch (tok) {
    case CHA_DIR: case PONTO_VIRG: case VIRGULA:
    case PAR_DIR: case COL_DIR : {
        break;
    }
    case OU : {
        eat(OU); T_OR(); EXPR_P();
        break;
    }
    default: error();
}}

void T_OR() { switch (tok) {
    case ID: case PAR_ESQ: case MAIS:
    case MENOS: case NAO: case CAST: case VERDADEIRO:
    case FALSO: case ALPHA: case NUM_INT: case NUM_FLUT : {
        T_AND(); T_OR_P();
        break;
    }
    default: error();
}}

void T_OR_P() { switch (tok) {
    case CHA_DIR: case PONTO_VIRG: case VIRGULA:
    case PAR_DIR: case COL_DIR : case OU : {
        break;
    }
    case E : {
        eat(E); T_AND(); T_OR_P();
        break;
    }
    default: error();
}}

void T_AND() { switch (tok) {
    case ID: case PAR_ESQ: case MAIS:
    case MENOS: case NAO: case CAST: case VERDADEIRO:
    case FALSO: case ALPHA: case NUM_INT: case NUM_FLUT : {
        T_REL(); T_AND_P();
        break;
    }
    default: error();
}}

void T_AND_P() { switch (tok) {
    case CHA_DIR: case PONTO_VIRG: case VIRGULA:
    case PAR_DIR: case COL_DIR : case OU : case E : {
        break;
    }  
    case IGUAL_IGUAL : {
        eat(IGUAL_IGUAL); T_REL(); T_AND_P();
        break;
    }
    case DIFERENTE : {
        eat(DIFERENTE); T_REL(); T_AND_P();
        break;
    }
    case MENOR_IGUAL : {
        eat(MENOR_IGUAL); T_REL(); T_AND_P();
        break;
    }
    case MAIOR_IGUAL : {
        eat(MAIOR_IGUAL); T_REL(); T_AND_P();
        break;
    }
    case MENOR : {
        eat(MENOR); T_REL(); T_AND_P();
        break;
    }
    case MAIOR : {
        eat(MAIOR); T_REL(); T_AND_P();
        break;
    }
    default: error();
}}

void T_REL() { switch (tok) {
    case ID: case PAR_ESQ: case MAIS:
    case MENOS: case NAO: case CAST: case VERDADEIRO:
    case FALSO: case ALPHA: case NUM_INT: case NUM_FLUT : {
        T_ARIT(); T_REL_P();
        break;
    }
    default: error();
}}

void T_REL_P() { switch (tok) {
    case CHA_DIR: case PONTO_VIRG: case VIRGULA :
    case PAR_DIR: case COL_DIR : case OU : case E :
    case IGUAL_IGUAL: case DIFERENTE: case MENOR_IGUAL:
    case MAIOR_IGUAL: case MENOR: case MAIOR : {
        break;
    }  
    case MAIS : {
        eat(MAIS); T_ARIT(); T_REL_P();
        break;
    }
    case MENOS : {
        eat(MENOS); T_ARIT(); T_REL_P();
        break;
    }
    default: error();
}}

void T_ARIT() { switch (tok) {
    case ID: case PAR_ESQ: case MAIS:
    case MENOS: case NAO: case CAST: case VERDADEIRO:
    case FALSO: case ALPHA: case NUM_INT: case NUM_FLUT : {
        T_FATOR(); T_ARIT_P();
        break;
    }
    default: error();
}}

void T_ARIT_P() { switch (tok) {
    case CHA_DIR: case PONTO_VIRG: case VIRGULA :
    case PAR_DIR: case COL_DIR : case OU : case E :
    case IGUAL_IGUAL: case DIFERENTE: case MENOR_IGUAL:
    case MAIOR_IGUAL: case MENOR: case MAIOR :
    case MAIS: case MENOS : {
        break;
    }
    case MULT : {
        eat(MULT); T_FATOR(); T_ARIT_P();
        break;
    }
    case DIV : {
        eat(DIV); T_FATOR(); T_ARIT_P();
        break;
    }
    case MOD : {
        eat(MOD); T_FATOR(); T_ARIT_P();
        break;
    }
    default: error();
}}

void T_FATOR() { switch (tok) {
    case ID: case PAR_ESQ: case MAIS:
    case MENOS: case NAO: case CAST: case VERDADEIRO:
    case FALSO: case ALPHA: case NUM_INT: case NUM_FLUT : {
        T_EXPO(); T_FATOR_P();
        break;
    }
    default: error();
}}

void T_FATOR_P() { switch (tok) {
    case CHA_DIR: case PONTO_VIRG: case VIRGULA :
    case PAR_DIR: case COL_DIR : case OU : case E :
    case IGUAL_IGUAL: case DIFERENTE: case MENOR_IGUAL:
    case MAIOR_IGUAL: case MENOR: case MAIOR : case MAIS :
    case MENOS : case MULT: case DIV: case MOD : {
        break;
    }
    case EXP : {
        eat(EXP); T_FATOR();
        break;
    }
    default: error();
}}

void T_EXPO() { switch (tok) {
    case ID: case PAR_ESQ: case MAIS:
    case MENOS: case NAO: case CAST: case VERDADEIRO:
    case FALSO: case ALPHA: case NUM_INT: case NUM_FLUT : {
        T_UN();
        break;
    }
    default: error();
}}

void T_UN() { switch (tok) {
    case ID : case PAR_ESQ : case VERDADEIRO: case FALSO :
    case ALPHA : case NUM_INT : case NUM_FLUT : {
        T_PAR_ID();
        break;
    }
    case MAIS : {
        eat(MAIS); T_UN();
        break;
    }
    case MENOS : {
        eat(MENOS); T_UN();
        break;
    }
    case NAO : {
        eat(NAO); T_UN();
        break;
    }
    case CAST : {
        CAST_(); T_UN();
        break;
    }
    default: error();
}}

void T_PAR_ID() { switch (tok) {
    case ID : case VERDADEIRO: case FALSO :
    case ALPHA : case NUM_INT : case NUM_FLUT : {
        EXPR_FOLHA();
        break;
    }
    case PAR_ESQ : {
        eat(PAR_ESQ); EXPR(); eat(PAR_DIR);
        break;
    }
    default: error();
}}

void CAST_() { switch (tok) {
    case CAST : {
      eat(CAST); TIPO_(); eat(CAST);
      break;
    }
    default: error();
}}

void EXPR_FOLHA() { switch (tok) {
  case ID : {
    eat(ID); CHAMADA_FUNC_OU_VAZIO(); MODIFICADORES_OU_VAZIO();
    break;
  }
  case VERDADEIRO: case FALSO : case ALPHA :
  case NUM_INT : case NUM_FLUT : {
    LITERAL();
    break;
  }
  default: error();
}}

void MOD_TYPE() { switch (tok) {
  case CHA_ESQ : {
    eat(CHA_ESQ); EXPR(); eat(CHA_DIR);
    break;
  }
  case PONTO : {
    eat(PONTO); eat(ID);
    break;
  }
  default: error();
}}

void MODIFICADORES_OU_VAZIO() { switch (tok) {
  case CHA_DIR: case PONTO_VIRG: case DOIS_PONTOS: 
  case VIRGULA : case PAR_DIR : case COL_ESQ: case COL_DIR: 
  case OU: case E: case IGUAL_IGUAL : case DIFERENTE : 
  case MENOR_IGUAL : case MAIOR_IGUAL : case MENOR : 
  case MAIOR: case MAIS: case MENOS : case MULT : case DIV : 
  case MOD : case EXP : case PONTO : {
      break;
  }
  case PAR_ESQ : {
    eat(PAR_ESQ); ARGS_FUNC_OU_VAZIO(); eat(PAR_DIR);
    break;
  }
  default: error();
}}

void CHAMADA_FUNC_OU_VAZIO() { switch (tok) {
  case CHA_DIR: case PONTO_VIRG: case IGUAL :
  case DOIS_PONTOS: case VIRGULA : case PAR_DIR :
  case COL_DIR: case OU: case E: case IGUAL_IGUAL:
  case DIFERENTE: case MENOR_IGUAL : case MAIOR_IGUAL :
  case MENOR : case MAIOR: case MAIS: case MENOS :
  case MULT : case DIV : case MOD : case EXP : {
    break;
  }
  case COL_ESQ : case PONTO : {
    MOD_TYPE(); MODIFICADORES_OU_VAZIO();
    break;
  }
  default: error();
}}


void ARGS_FUNC_OU_VAZIO(){ switch(tok){
    case PAR_DIR:
        break;
    case ID: case PAR_ESQ: case MAIS: case MENOS: case NAO: case CAST: case VERDADEIRO: case FALSO: case CARAC: case NUM_INT: case NUM_FLUT:
        EXPR(); ARGS_FUNC();
        break;
    default: error();
}}

void ARGS_FUNC(){ switch (tok){
    case VIRGULA: 
        eat(VIRGULA); EXPR(); ARGS_FUNC();
    case PAR_DIR:
        break;
    default: error();
}}

void LITERAL(){ switch(tok){
    case VERDADEIRO: case FALSO:
        LITERAL_LOGICO();
        break;
    case CARAC:
        LITERAL_CARAC();
        break;
    case NUM_FLUT:
        LITERAL_FLUT();
        break;
    case NUM_INT:
        LITERAL_INT();
        break;
    default: error();
}}

void LITERAL_LOGICO(){ switch (tok){
    case VERDADEIRO:
        eat(VERDADEIRO);
        break;
    case FALSO:
        eat(FALSO);
        break;
    default: error();
}}

void LITERAL_CARAC(){ switch(tok){
    case CARAC:
        eat(CARAC);
        break;
    default: error();
}}

void LITERAL_FLUT(){ switch(tok){
    case NUM_FLUT:
        eat(NUM_FLUT);
        break;
    default: error();
}}

void LITERAL_INT(){ switch(tok){
    case NUM_INT:
        eat(NUM_INT);
        break;
    default: error();
}}

void C_EXPR(){
switch(tok){
    case ID: case PAR_ESQ: case MAIS: case MENOS: case NAO: case CAST: case VERDADEIRO: case FALSO: case CARAC: case NUM_INT: case NUM_FLUT:
        C_T_OR(); C_EXPR_P();
    default: error();
}}

void C_EXPR_P(){
switch (tok){
    case DOIS_PONTOS: case PAR_DIR: case COL_DIR:
        break;
    case OU:
        eat(OU); C_T_OR(); C_EXPR_P();
        break;
    default: error();
}}

void C_T_OR(){
switch (tok){
    case ID: case PAR_ESQ: case MAIS: case MENOS: case NAO: case CAST: case VERDADEIRO: case FALSO: case CARAC: case NUM_INT: case NUM_FLUT:
        C_T_AND(); C_T_OR_P();
        break;
    default: error();
}}

void C_T_OR_P(){ switch(tok){
    case DOIS_PONTOS: case PAR_DIR: case COL_DIR: case OU:
        break;
    case E:
        eat(E); C_T_AND(); C_T_OR_P();
        break;
    default: error();
}}

void C_T_AND(){
switch (tok){
    case ID: case PAR_ESQ: case MAIS: case MENOS: case NAO: case CAST: case VERDADEIRO: case FALSO: case CARAC: case NUM_INT: case NUM_FLUT:
        C_T_REL(); C_T_AND_P();
        break;
    default: error();
}}

void C_T_AND_P(){ switch(tok){
    case DOIS_PONTOS: case PAR_DIR: case COL_DIR: case OU: case E:
        break;
    case IGUAL: 
        eat(IGUAL); C_T_REL(); C_T_AND_P();
        break;
    case DIFERENTE: 
        eat(DIFERENTE); C_T_REL(); C_T_AND_P();
        break;
    case MENOR: 
        eat(MENOR); C_T_REL(); C_T_AND_P();
        break;
    case MAIOR: 
        eat(MAIOR); C_T_REL(); C_T_AND_P();
        break;
    case MENOR_IGUAL: 
        eat(MENOR_IGUAL); C_T_REL(); C_T_AND_P();
        break;
    case MAIOR_IGUAL:
        eat(MAIOR_IGUAL); C_T_REL(); C_T_AND_P();
        break;
    default: error();
}}

void C_T_REL(){ switch (tok){
    case ID: case PAR_ESQ: case MAIS: case MENOS: case NAO: case CAST: case VERDADEIRO: case FALSO: case CARAC: case NUM_INT: case NUM_FLUT:
        C_T_ARIT(); C_T_REL_P();
        break;
    default: error();
}}

void C_T_REL_P(){switch(tok){
    case DOIS_PONTOS: case PAR_DIR: case COL_DIR: case OU: case E: case IGUAL: case DIFERENTE: case MENOR: case MAIOR: case MENOR_IGUAL: case MAIOR_IGUAL:
        break;
    case MAIS: 
        eat(MAIS);
        C_T_ARIT(); C_T_REL_P();
        break;
    case MENOS:
        eat(MENOS);
        C_T_ARIT(); C_T_REL_P();
        break;
    default: error();
}}

void C_T_ARIT_T_P(){ switch(tok){
    case DOIS_PONTOS: case PAR_DIR: case COL_DIR: case OU: case E: case IGUAL: case DIFERENTE: case MENOR: case MAIOR: case MENOR_IGUAL: case MAIOR_IGUAL: case MAIS: case MENOS:
        break;
    case MULT: 
        eat(MULT); C_T_FATOR(); C_T_ARIT_T_P();
        break;
    case DIV: 
        eat(DIV); C_T_FATOR(); C_T_ARIT_T_P();
        break;
    case MOD:
        eat(MOD); C_T_FATOR(); C_T_ARIT_T_P();
        break;
    default: error();
}}

void C_T_FATOR(){ switch (tok){
    case ID: case PAR_ESQ: case MAIS: case MENOS: case NAO: case CAST: case VERDADEIRO: case FALSO: case CARAC: case NUM_INT: case NUM_FLUT:
        C_T_EXPO(); C_T_FATOR_P();
        break;
    default: error();
}}

void C_T_FAOTR_P(){ switch(tok){
    case DOIS_PONTOS: case PAR_DIR: case COL_DIR: case OU: case E: case IGUAL: case DIFERENTE: case MENOR: case MAIOR: case MENOR_IGUAL: case MAIOR_IGUAL: case MAIS: case MENOS: case MULT: case DIV: case MOD:
        break;
    case EXP:
        eat(EXP); C_T_FATOR();
        break;
    default: error();
}}

void C_T_EXPO(){switch (tok){
    case ID: case PAR_ESQ: case MAIS: case MENOS: case NAO: case CAST: case VERDADEIRO: case FALSO: case CARAC: case NUM_INT: case NUM_FLUT:
        C_T_UN();
        break;
    default: error();
}}

void C_T_UN(){ switch(tok){
    case ID: case PAR_ESQ: case VERDADEIRO: case FALSO: case CARAC: case NUM_FLUT: case NUM_INT:
        C_T_PAR_ID();
        break;
    case MAIS:
        eat(MAIS); C_T_UN();
        break;
    case MENOS:
        eat(MENOS); C_T_UN();
        break;
    case NAO:
        eat(NAO); C_T_UN();
        break;
    case CAST:
        CAST_(); C_T_UN();
        break;
    default: error();
}}

void C_T_PAR_ID(){ switch(tok){
    case ID: case VERDADEIRO: case FALSO: case CARAC: case NUM_FLUT: case NUM_INT:
        EXPR_FOLHA();
        break;
    case PAR_ESQ:
        eat(PAR_ESQ); C_EXPR(); eat(PAR_DIR);
        break;
    default: error();
}}

void C_T_ARIT(){ switch (tok){
    case ID: case PAR_ESQ: case MAIS: case MENOS: case NAO: case CAST: case VERDADEIRO: case FALSO: case CARAC: case NUM_INT: case NUM_FLUT:
        C_T_FATOR(); C_T_ARIT_T_P();
        break;
    default: error();
}}

void C_T_FATOR_P(){ switch(tok){
    case DOIS_PONTOS: case PAR_DIR: case COL_DIR: case OU: case E: case IGUAL: case DIFERENTE: case MENOR: case MAIOR: case MENOR_IGUAL: case MAIOR_IGUAL: case MAIS: case MENOS: case MULT: case DIV: case MOD:
        break;
    case EXP:
        eat(EXP); C_T_FATOR();
        break;
    default: error();
}}


int main(){
  advance();
  S();
}