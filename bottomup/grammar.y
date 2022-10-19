%{
#include <stdio.h>

int yylex(void);
void yyerror (const char *msg);
extern int yylineno;
extern char * yytext;

%}

%union {
	int iValue;
	char cValue;
	char* sValue;
};

// %token <iValue> INTEGER_LITERAL

%token LIT_FLUT LIT_INT LIT_CHAR LIT_STRING
%token ENQUANTO FACA PARA
%token PARE CONTINUE
%token SE SENAO ESCOLHA CASO PADRAO
%token CONST DECLRS
%token ESCREVA LEIA
%token VAR REF '='
%token PROC FUNC RETORNE
%token ESTRUTURA BLOCO TIPO
%token INT LOGICO FLUT CARAC
%token VERDADEIRO FALSO
%token ':' ';' '.' ','
%token '(' ')' '[' ']' '{' '}'
%token '%'
%token <sValue> ID

%left OU 'e'
%nonassoc IGUAL_IGUAL DIFERENTE MENOR_IGUAL MAIOR_IGUAL '<' '>'
%left '+' '-'
%left '*' '/' MOD
%right '^'
%right UMINUS UPLUS '!' CASTING

%start programa

%% /* Inicio da segunda seção, onde colocamos as regras BNF */

programa : definicoes declaracoes novo_bloco
  ;

definicoes : 
  | CONST '{' lista_definicoes '}'
  ;

lista_definicoes : definicao 
  | definicao ';' lista_definicoes
  ;

definicao : variavel_constante '=' literal
  ;

variavel_constante : ID
  ;

declaracoes : 
  | DECLRS '{' lista_declaracoes '}'
  ;

lista_declaracoes : declaracao
  | declaracao ';' lista_declaracoes
  ;

declaracao : dec_var
  | dec_proc
  | dec_func
  | dec_tipo
  ;

novo_bloco : BLOCO bloco
  ;

bloco : '{' declaracoes lista_comandos '}'
  ;

lista_comandos : comando
  | comando ';' lista_comandos
  ;

dec_var : VAR lista_id_vars ':' tipo
  ;

lista_id_vars : ID
  | ID ',' lista_id_vars
  ;

dec_proc : PROC ID '(' ')' bloco
  | PROC ID '('lista_parametros ')' bloco
  ;

dec_func : FUNC ID '(' ')' ':' tipo bloco
  | FUNC ID '(' lista_parametros ')' ':' tipo bloco
  ;

lista_parametros : parametro
  | parametro ',' lista_parametros
  ;

parametro : ID ':' TIPO
  | REF ID ':' TIPO
  ;

dec_tipo : TIPO ID '=' tipo
  ;

tipo : ID colchetes_ou_vazio
  | tipo_simples colchetes_ou_vazio
  | registro colchetes_ou_vazio
  ;

tipo_simples : INT
  | LOGICO
  | FLUT
  | CARAC
  ;

colchetes_ou_vazio : 
  | '[' expr_const ']'colchetes_ou_vazio
  ;

registro : ESTRUTURA '{' lista_dec_var '}'
  ;

lista_dec_var : dec_var
  | dec_var ',' lista_dec_var
  ;

comando : CONTINUE
  | PARE
  | retorno
  | novo_bloco
  | controle
  | repeticao
  | ESCREVA '(' lista_expr ')'
  | LEIA '(' variavel ')'
  | atribuicao
  | ID '(' ')'
  | ID '(' lista_expr ')'
  ;

atribuicao : variavel '=' expr
  ;

lista_expr : expr
  | expr ',' lista_expr
  ;

controle : se
  | escolha
  ;

se : SE '(' expr ')' bloco senao
  | SE '(' expr ')' bloco
  ;

senao : SENAO bloco
  | SENAO se
  ;

escolha : ESCOLHA '(' expr ')' '{' lista_casos '}'
  ;

lista_casos : escolha_padrao
  | caso_escolha
  | caso_escolha ';' lista_casos
  ;

escolha_padrao : PADRAO ':' comando
  ;

caso_escolha : CASO expr_const ':' comando
  ;

repeticao : enquanto
  | faca_enquanto
  | para
  ;

enquanto : ENQUANTO '(' expr ')' bloco
  ;

faca_enquanto : FACA bloco ENQUANTO '(' expr ')'
  ;

para : PARA '(' atribuicao ';' expr ';' atribuicao ')' bloco
  ;

retorno : RETORNE 
  | RETORNE expr
  ;

variavel : ID
  | ID lista_modificadores
  ;

lista_modificadores : modificador_variavel
  | modificador_variavel lista_modificadores
  ;

modificador_variavel : '.' ID
  | '[' expr ']'
  ;

literal : literal_logico
  | LIT_INT
  | LIT_FLUT
  | LIT_CHAR
  | literal_array
  ;

literal_logico : VERDADEIRO
  | FALSO
  ;

literal_array : LIT_STRING
  | '[' lista_literais']'
  ;

lista_literais : literal
  | literal ',' lista_literais
  ;

expr : expr '+' expr
  | expr '-' expr
  | expr '*' expr
  | expr MOD expr
  | expr '/' expr
  | expr '^' expr
  | expr IGUAL_IGUAL expr
  | expr DIFERENTE expr
  | expr MENOR_IGUAL expr
  | expr MAIOR_IGUAL expr
  | expr '<' expr
  | expr '>' expr
  | expr 'e' expr
  | expr OU expr
  | '+' expr %prec UPLUS
  | '-' expr %prec UMINUS
  | '!' expr
  | '%' tipo '%' expr %prec CASTING
  | '(' expr ')'
  | folha_expr
  ;

folha_expr : literal
  | variavel
  | ID '(' ')'
  | ID '(' lista_expr ')'
  | ID '(' ')' lista_modificadores
  | ID '(' lista_expr ')' lista_modificadores
  ;

expr_const : expr_const '+' expr_const
  | expr_const '-' expr_const
  | expr_const '*' expr_const
  | expr_const MOD expr_const
  | expr_const '/' expr_const
  | expr_const '^' expr_const
  | expr_const IGUAL_IGUAL expr_const
  | expr_const DIFERENTE expr_const
  | expr_const MENOR_IGUAL expr_const
  | expr_const MAIOR_IGUAL expr_const
  | expr_const '<' expr_const
  | expr_const '>' expr_const
  | expr_const 'e' expr_const
  | expr_const OU expr_const
  | '+' expr_const %prec UPLUS
  | '-' expr_const %prec UMINUS
  | '!' expr_const
  | '%' tipo '%' expr_const %prec CASTING
  | '(' expr_const ')'
  | folha_expr_const
  ;

folha_expr_const : literal
  ;

%% /* Fim da segunda seção */

int main (void) {
	return yyparse();
}

void yyerror (const char *msg) {
	fprintf (stderr, "%d: %s at '%s'\n", yylineno, msg, yytext);
}