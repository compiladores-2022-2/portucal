%{

#include "utils/enums.h"

int collumn_counter = 0;

%}
%option yylineno

dig         [0-9]
alpha       [A-Z|a-z]
id          ({alpha}|\_)({alpha}|{dig}|\_)*
num_flut    [-+]?{dig}{dig}*\.{dig}{dig}*
num_int     [-+]?{dig}{dig}*

continue    "continue"
pare        "pare"
se          "se"
senao       "senão"
enquanto    "enquanto"
faca        "faça"
para        "para"
escolha     "escolha"
caso        "caso"
retorne     "retorne"
leia        "leia"
imprima     "imprima"

var         "var"
const       "const"
declrs      "declrs"
proc        "proc"
func        "func"
estrutura   "estrutura"
bloco       "bloco"
tipo        "tipo"

int         "int"
logico      "logico"
flut        "flut"
carac       "carac"
ref         "ref"

verdadeiro  "verdadeiro"
falso       "falso" 
ou          "ou" 			
e           "e"			
nao         "!"

dois_pontos ":"
ponto_virg  ";"
ponto       "."
virgula     ","
par_esq     "("
par_dir     ")"
col_esq     "["
col_dir     "]"
cha_esq     "{"
cha_dir     "}"

menos       "-"					 
mais        "+"					
mult        "*"					
div         "/"					
mod 				"%"
exp         "^"

maior       ">"					
menor       "<"					
maior_igual ">="				
menor_igual "<="				
igual       "="
diferente   "!="

quebra_linha "\n"
comentario "//"(.)*

erro "."

%%

{num_flut} {
  printf(">> Token: NUM_FLUT (id %d), Valor: %s\t\n", NUM_FLUT, yytext);
  collumn_counter += yyleng;
  return NUM_FLUT;
}

{num_int} {
  printf(">> Token: NUM_INT (id %d), Valor: %s\t\n", NUM_INT, yytext);
  collumn_counter += yyleng;
  return NUM_INT;
}

{continue} {
  printf(">> Token: CONTINUE (id %d)\n", CONTINUE);
  collumn_counter += yyleng;
  return CONTINUE;
}

{pare} {
  printf(">> Token: PARE (id %d)\n", PARE);
  collumn_counter += yyleng;
  return PARE;
}

{se} {
  printf(">> Token: SE (id %d)\n", SE);
  collumn_counter += yyleng;
  return SE;
}

{senao} {
  printf(">> Token: SENAO (id %d)\n", SENAO);
  collumn_counter += yyleng;
  return SENAO;
}

{enquanto} {
  printf(">> Token: ENQUANTO (id %d)\n", ENQUANTO);
  collumn_counter += yyleng;
  return ENQUANTO;
}

{faca} {
  printf(">> Token: FACA (id %d)\n", FACA);
  collumn_counter += yyleng;
  return FACA;
}

{para} {
  printf(">> Token: PARA (id %d)\n", PARA);
  collumn_counter += yyleng;
  return PARA;
}

{escolha} {
  printf(">> Token: ESCOLHA (id %d)\n", ESCOLHA);
  collumn_counter += yyleng;
  return ESCOLHA;
}

{caso} {
  printf(">> Token: CASO (id %d)\n", CASO);
  collumn_counter += yyleng;
  return CASO;
}

{retorne} {
  printf(">> Token: RETORNE (id %d)\n", RETORNE);
  collumn_counter += yyleng;
  return RETORNE;
}

{imprima} {
  printf(">> Token: IMPRIMA (id %d)\n", IMPRIMA);
  collumn_counter += yyleng;
  return IMPRIMA;
}

{var} {
  printf(">> Token: VAR (id %d)\n", VAR);
  collumn_counter += yyleng;
  return VAR;
}

{const} {
  printf(">> Token: CONST (id %d)\n", CONST);
  collumn_counter += yyleng;
  return CONST;
}

{declrs} {
  printf(">> Token: DECLRS (id %d)\n", DECLRS);
  collumn_counter += yyleng;
  return DECLRS;
}

{proc} {
  printf(">> Token: PROC (id %d)\n", PROC);
  collumn_counter += yyleng;
  return PROC;
}

{func} {
  printf(">> Token: FUNC (id %d)\n", FUNC);
  collumn_counter += yyleng;
  return FUNC;
}

{estrutura} {
  printf(">> Token: ESTRUTURA (id %d)\n", ESTRUTURA);
  collumn_counter += yyleng;
  return ESTRUTURA;
}

{bloco} {
  printf(">> Token: BLOCO (id %d)\n", BLOCO);
  collumn_counter += yyleng;
  return BLOCO;
}

{tipo} {
  printf(">> Token: TIPO (id %d)\n", TIPO);
  collumn_counter += yyleng;
  return TIPO;
}

{int} {
  printf(">> Token: INT (id %d)\n", INT);
  collumn_counter += yyleng;
  return INT;
}

{logico} {
  printf(">> Token: LOGICO (id %d)\n", LOGICO);
  collumn_counter += yyleng;
  return LOGICO;
}

{flut} {
  printf(">> Token: FLUT (id %d)\n", FLUT);
  collumn_counter += yyleng;
  return FLUT;
}

{carac} {
  printf(">> Token: CARAC (id %d)\n", CARAC);
  collumn_counter += yyleng;
  return CARAC;
}

{ref} {
  printf(">> Token: REF (id %d)\n", REF);
  collumn_counter += yyleng;
  return REF;
}

{dois_pontos} {
  printf(">> Token: DOIS_PONTOS (id %d)\n", DOIS_PONTOS);
  collumn_counter += yyleng;
  return DOIS_PONTOS;
}

{verdadeiro} {
  printf(">> Token: VERDADEIRO (id %d)\n", VERDADEIRO);
  collumn_counter += yyleng;
  return VERDADEIRO;
}

{falso} {
  printf(">> Token: FALSO (id %d)\n", FALSO);
  collumn_counter += yyleng;
  return FALSO;
}

{ou} {
  printf(">> Token: OU (id %d)\n", OU);
  collumn_counter += yyleng;
  return OU;
}

{e} {
  printf(">> Token: E (id %d)\n", E);
  collumn_counter += yyleng;
  return E;
}

{nao} {
  printf(">> Token: NAO (id %d)\n", NAO);
  collumn_counter += yyleng;
  return NAO;
}

{ponto_virg} {
  printf(">> Token: PONTO_VIRG (id %d)\n", PONTO_VIRG);
  collumn_counter += yyleng;
  return PONTO_VIRG;
}

{ponto} {
  printf(">> Token: PONTO (id %d)\n", PONTO);
  collumn_counter += yyleng;
  return PONTO;
}

{virgula} {
  printf(">> Token: VIRGULA (id %d)\n", VIRGULA);
  collumn_counter += yyleng;
  return VIRGULA;
}

{par_esq} {
  printf(">> Token: PAR_ESQ (id %d)\n", PAR_ESQ);
  collumn_counter += yyleng;
  return PAR_ESQ;
}

{par_dir} {
  printf(">> Token: PAR_DIR (id %d)\n", PAR_DIR);
  collumn_counter += yyleng;
  return PAR_DIR;
}

{col_esq} {
  printf(">> Token: COL_ESQ (id %d)\n", COL_ESQ);
  collumn_counter += yyleng;
  return COL_ESQ;
}

{col_dir} {
  printf(">> Token: COL_DIR (id %d)\n", COL_DIR);
  collumn_counter += yyleng;
  return COL_DIR;
}

{cha_esq} {
  printf(">> Token: CHA_ESQ (id %d)\n", CHA_ESQ);
  collumn_counter += yyleng;
  return CHA_ESQ;
}

{cha_dir} {
  printf(">> Token: CHA_DIR (id %d)\n", CHA_DIR);
  collumn_counter += yyleng;
  return CHA_DIR;
}

{id} {
  printf(">> Token: ID (id %d), Valor: %s\t\n", ID, yytext);
  collumn_counter += yyleng;
  return ID;
}

{menos} {
  printf(">> Token: MENOS (id %d)\n", MENOS);
  return MENOS;
}

{mais} {
  printf(">> Token: MAIS (id %d)\n", MAIS);
  return MAIS;
}

{mult} {
  printf(">> Token: MULT (id %d)\n", MULT);
  return MULT;
}

{div} {
  printf(">> Token: DIV (id %d)\n", DIV);
  return DIV;
}

{mod} {
  printf(">> Token: MOD (id %d)\n", MOD);
  return MOD;
}

{exp} {
  printf(">> Token: EXP (id %d)\n", EXP);
  return EXP;
}

{comentario} {
  printf(">> Token: COMENTARIO (id %d)\n", COMENTARIO);
  collumn_counter += yyleng;
  return COMENTARIO;
}

{maior} {
  printf(">> Token: MAIOR (id %d)\n", MAIOR);
  return MAIOR;
}

{menor} {
  printf(">> Token: MENOR (id %d)\n", MENOR);
  return MENOR;
}

{maior_igual} {
  printf(">> Token: MAIOR_IGUAL (id %d)\n", MAIOR_IGUAL);
  return MAIOR_IGUAL;
}

{menor_igual} {
  printf(">> Token: MENOR_IGUAL (id %d)\n", MENOR_IGUAL);
  return MENOR_IGUAL;
}

{igual} {
  printf(">> Token: IGUAL (id %d)\n", IGUAL);
  return IGUAL;
}

{diferente} {
  printf(">> Token: DIFERENTE (id %d)\n", DIFERENTE);
  return DIFERENTE;
}

{quebra_linha} {
  printf(">> Token: QUEBRA_LINHA (id %d)\n", QUEBRA_LINHA);
  collumn_counter = 0;
  return QUEBRA_LINHA;
}

%%

int yywrap(){}
int main(int argc, char **argv){
  yylex();
  return 0;
}