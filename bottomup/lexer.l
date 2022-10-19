%{

#include "y.tab.h"

int collumn_counter = 0;

#define INC_COL collumn_counter += yyleng

%}
%option yylineno
%option noyywrap

dig         [0-9]
alpha       [A-Z|a-z]
id          ({alpha}|\_)({alpha}|{dig}|\_)*

lit_flut    [-+]?{dig}{dig}*\.{dig}{dig}*
lit_int     [-+]?{dig}{dig}*
lit_char    \'.\'
lit_string  \".*\"

continue    "continue"
pare        "pare"
se          "se"
senao       "senao"
enquanto    "enquanto"
faca        "faca"
para        "para"
escolha     "escolha"
caso        "caso"
padrao      "padrao"

retorne     "retorne"
leia        "leia"
escreva     "escreva"

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

espaco_branco [ \t]+

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
cast        "%"

menos       "-"					 
mais        "+"					
mult        "*"					
div         "/"					
mod 				"mod"
exp         "^"

maior       ">"					
menor       "<"					
maior_igual ">="				
menor_igual "<="				
igual_igual "=="
igual       "="
diferente   "!="

quebra_linha "\n"
comentario "//"(.)*

erro "."

%%

{lit_flut}    { INC_COL; return LIT_FLUT; }
{lit_int}     { INC_COL; return LIT_INT; }
{lit_char}    { INC_COL; return LIT_CHAR; }
{lit_string}  { INC_COL; return LIT_STRING; }

{enquanto}    { INC_COL; return ENQUANTO; }
{faca}        { INC_COL; return FACA; }
{para}        { INC_COL; return PARA; }

{pare}        { INC_COL; return PARE; }
{continue}    { INC_COL; return CONTINUE; }

{se}          { INC_COL; return SE; }
{senao}       { INC_COL; return SENAO; }
{escolha}     { INC_COL; return ESCOLHA; }
{caso}        { INC_COL; return CASO; }
{padrao}      { INC_COL; return PADRAO; }

{const}       { INC_COL; return CONST; }
{declrs}      { INC_COL; return DECLRS; }

{escreva}     { INC_COL; return ESCREVA; }
{leia}        { INC_COL; return LEIA; }

{var}         { INC_COL; return VAR; }
{ref}         { INC_COL; return REF; }
{igual}       { INC_COL; return '='; }

{proc}        { INC_COL; return PROC; }
{func}        { INC_COL; return FUNC; }
{retorne}     { INC_COL; return RETORNE; }

{estrutura}   { INC_COL; return ESTRUTURA; }
{bloco}       { INC_COL; return BLOCO; }
{tipo}        { INC_COL; return TIPO; }

{int}         { INC_COL; return INT; }
{logico}      { INC_COL; return LOGICO; }
{flut}        { INC_COL; return FLUT; }
{carac}       { INC_COL; return CARAC; }

{verdadeiro}  { INC_COL; return VERDADEIRO; }
{falso}       { INC_COL; return FALSO; }

{ou}          { INC_COL; return OU; }
{e}           { INC_COL; return 'e'; }
{nao}         { INC_COL; return '!'; }

{maior}       { INC_COL; return '>'; }
{menor}       { INC_COL; return '<'; }
{maior_igual} { INC_COL; return MAIOR_IGUAL; }
{menor_igual} { INC_COL; return MENOR_IGUAL; }
{igual_igual} { INC_COL; return IGUAL_IGUAL; }
{diferente}   { INC_COL; return DIFERENTE; }

{menos}       { INC_COL; return '-'; }
{mais}        { INC_COL; return '+'; }
{mult}        { INC_COL; return '*'; }
{div}         { INC_COL; return '/'; }
{exp}         { INC_COL; return '^'; }
{mod}         { INC_COL; return MOD; }

{dois_pontos} { INC_COL; return ':'; }
{ponto_virg}  { INC_COL; return ';'; }
{ponto}       { INC_COL; return '.'; }
{virgula}     { INC_COL; return ','; }

{par_esq}     { INC_COL; return '('; }
{par_dir}     { INC_COL; return ')'; }
{col_esq}     { INC_COL; return '['; }
{col_dir}     { INC_COL; return ']'; }
{cha_esq}     { INC_COL; return '{'; }
{cha_dir}     { INC_COL; return '}'; }

{cast}        { INC_COL; return '%'; }
{id}          { INC_COL; return ID; }

{comentario}  { INC_COL; }
{quebra_linha} { collumn_counter = 0; }
{espaco_branco} { INC_COL; }
%%