%{

#include "utils/enums.h"

%}

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

dois_pontos ":"
ponto_virg  ";"

erro "."

%%

{num_flut} {
  printf(">> Token: NUM_FLUT (id %d), Valor: %s\t\n", NUM_FLUT, yytext);
  return NUM_FLUT;
}

{num_int} {
  printf(">> Token: NUM_INT (id %d), Valor: %s\t\n", NUM_INT, yytext);
  return NUM_INT;
}

{continue} {
  printf(">> Token: CONTINUE (id %d)\n", CONTINUE);
  return CONTINUE;
}

{pare} {
  printf(">> Token: PARE (id %d)\n", PARE);
  return PARE;
}

{se} {
  printf(">> Token: SE (id %d)\n", SE);
  return SE;
}

{senao} {
  printf(">> Token: SENAO (id %d)\n", SENAO);
  return SENAO;
}

{enquanto} {
  printf(">> Token: ENQUANTO (id %d)\n", ENQUANTO);
  return ENQUANTO;
}

{faca} {
  printf(">> Token: FACA (id %d)\n", FACA);
  return FACA;
}

{para} {
  printf(">> Token: PARA (id %d)\n", PARA);
  return PARA;
}

{escolha} {
  printf(">> Token: ESCOLHA (id %d)\n", ESCOLHA);
  return ESCOLHA;
}

{caso} {
  printf(">> Token: CASO (id %d)\n", CASO);
  return CASO;
}

{retorne} {
  printf(">> Token: RETORNE (id %d)\n", RETORNE);
  return RETORNE;
}

{imprima} {
  printf(">> Token: IMPRIMA (id %d)\n", IMPRIMA);
  return IMPRIMA;
}

{var} {
  printf(">> Token: VAR (id %d)\n", VAR);
  return VAR;
}

{const} {
  printf(">> Token: CONST (id %d)\n", CONST);
  return CONST;
}

{declrs} {
  printf(">> Token: DECLRS (id %d)\n", DECLRS);
  return DECLRS;
}

{proc} {
  printf(">> Token: PROC (id %d)\n", PROC);
  return PROC;
}

{func} {
  printf(">> Token: FUNC (id %d)\n", FUNC);
  return FUNC;
}

{estrutura} {
  printf(">> Token: ESTRUTURA (id %d)\n", ESTRUTURA);
  return ESTRUTURA;
}

{bloco} {
  printf(">> Token: BLOCO (id %d)\n", BLOCO);
  return BLOCO;
}

{tipo} {
  printf(">> Token: TIPO (id %d)\n", TIPO);
  return TIPO;
}

{int} {
  printf(">> Token: INT (id %d)\n", INT);
  return INT;
}

{logico} {
  printf(">> Token: LOGICO (id %d)\n", LOGICO);
  return LOGICO;
}

{flut} {
  printf(">> Token: FLUT (id %d)\n", FLUT);
  return FLUT;
}

{carac} {
  printf(">> Token: CARAC (id %d)\n", CARAC);
  return CARAC;
}

{ref} {
  printf(">> Token: REF (id %d)\n", REF);
  return REF;
}

{dois_pontos} {
  printf(">> Token: DOIS_PONTOS (id %d)\n", DOIS_PONTOS);
  return DOIS_PONTOS;
}

{ponto_virg} {
  printf(">> Token: PONTO_VIRG (id %d)\n", PONTO_VIRG);
  return PONTO_VIRG;
}

{id} {
  printf(">> Token: ID (id %d), Valor: %s\t\n", ID, yytext);
  return ID;
}

%%

int yywrap(){}
int main(int argc, char **argv){
  yylex();
  return 0;
}