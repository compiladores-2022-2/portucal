%{
#include <iostream>
#include "yacc_types.hpp"

using namespace std;
using namespace node;

int yylex(void);
void yyerror (const char *msg);
extern int yylineno, yyleng;
extern char * yytext;
int collumn_counter = 0;



%}

%type <_programa> programa
%type <_definicoes> definicoes
%type <_listadefinicoes> lista_definicoes
%type <_definicao> definicao
%type <_variavelconstante> variavel_constante
%type <_declaracoes> declaracoes
%type <_listadeclaracoes> lista_declaracoes
%type <_declaracao> declaracao
%type <_novobloco> novo_bloco
%type <_bloco> bloco
%type <_listacomandos> lista_comandos
%type <_decvar> dec_var
%type <_listaidvars> lista_id_vars
%type <_decproc> dec_proc
%type <_decfunc> dec_func
%type <_listaparametros> lista_parametros
%type <_parametro> parametro
%type <_dectipo> dec_tipo
%type <_tipo> tipo
%type <_tiposimples> tipo_simples
%type <_colchetesouvazio> colchetes_ou_vazio
%type <_registro> registro
%type <_listadecatr> lista_dec_atr
%type <_decatr> dec_atr
%type <_comando> comando
%type <_atribuicao> atribuicao
%type <_listaexpr> lista_expr
%type <_controle> controle
%type <_se> se
%type <_senao> senao
%type <_escolha> escolha
%type <_listacasos> lista_casos
%type <_escolhapadrao> escolha_padrao
%type <_casoescolha> caso_escolha
%type <_repeticao> repeticao
%type <_enquanto> enquanto
%type <_facaenquanto> faca_enquanto
%type <_para> para
%type <_retorno> retorno
%type <_variavel> variavel
%type <_listamodificadores> lista_modificadores
%type <_modificadorvariavel> modificador_variavel
%type <_literal> literal
%type <_literallogico> literal_logico
%type <_literalarray> literal_array
%type <_listaliterais> lista_literais
%type <_expr> expr
%type <_folhaexpr> folha_expr
%type <_exprconst> expr_const
%type <_folhaexprconst> folha_expr_const

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
%token <name> ID

%left OU 'e'
%nonassoc IGUAL_IGUAL DIFERENTE MENOR_IGUAL MAIOR_IGUAL '<' '>'
%left '+' '-'
%left '*' '/' MOD
%right '^'
%right UMINUS UPLUS '!' CASTING

%start programa

%% /* Inicio da segunda seção, onde colocamos as regras BNF */

programa : definicoes declaracoes novo_bloco                      { $$ = new Programa($1, $2, $3); }
  ;

definicoes :                                                      { $$ = new Definicoes(); }
  | CONST '{' lista_definicoes '}'                                { $$ = new Definicoes($3); }
  ;

lista_definicoes : definicao                                      {$$ = new ListaDefinicoes($1);}
  | definicao ';' lista_definicoes                                {$$ = new ListaDefinicoes($1, $3); }
  ;

definicao : variavel_constante '=' literal                {$$ = new Definicao($1, $3);}
  ;

variavel_constante : ID                                    {$$ = new VariavelConstante($1);}
  ;

declaracoes :                                             {$$ = new Declaracoes(); }
  | DECLRS '{' lista_declaracoes '}'                      {$$ = new Declaracoes($3); }
  ;

lista_declaracoes : declaracao                            {$$ = new ListaDeclaracoes($1); }
  | declaracao ';' lista_declaracoes                      {$$ = new ListaDeclaracoes($1, $3); }
  ;

declaracao : dec_var                                      {$$ = new Declaracao($1);}
  | dec_proc                                              {$$ = new Declaracao($1);}
  | dec_func                                              {$$ = new Declaracao($1);}
  | dec_tipo                                              {$$ = new Declaracao($1);}
  ;

novo_bloco : BLOCO bloco                                  {$$ = new NovoBloco($2);}
  ;

bloco : '{' declaracoes lista_comandos '}'                {$$ = new Bloco($2, $3);}
  ;

lista_comandos : comando                                  {$$ = new ListaComandos($1);}
  | comando ';' lista_comandos                            {$$ = new ListaComandos($1, $3);}
  ;

dec_var : VAR lista_id_vars ':' tipo                      {$$ = new DecVar($2, $4); }
  ;

lista_id_vars : ID                                        {$$ = new ListaIdVars($1); }
  | ID ',' lista_id_vars                                  {$$ = new ListaIdVars($1, $3); }
  ;

dec_proc : PROC ID '(' ')' bloco                          {$$ = new DecProc($2, $5, nullptr);}
  | PROC ID '('lista_parametros ')' bloco                 {$$ = new DecProc($2, $6, $4);}
  ;

dec_func : FUNC ID '(' ')' ':' tipo bloco                 {$$ = new DecFunc($2, $6, $7, nullptr);}
  | FUNC ID '(' lista_parametros ')' ':' tipo bloco       {$$ = new DecFunc($2, $7, $8, $4);}
  ;

lista_parametros : parametro                              {$$ = new ListaParametros($1);}
  | parametro ',' lista_parametros                        {$$ = new ListaParametros($1, $3);}
  ;

parametro : ID ':' tipo                                   {$$ = new Parametro($1, $3, false);}
  | REF ID ':' tipo                                       {$$ = new Parametro($2, $4, true);}
  ;

dec_tipo : TIPO ID '=' tipo                               {$$ = new DecTipo($2, $4); }
  ;

tipo : ID colchetes_ou_vazio                              {$$ = new Tipo($1, $2); }
  | tipo_simples colchetes_ou_vazio                       {$$ = new Tipo($1, $2); }
  | registro colchetes_ou_vazio                           {$$ = new Tipo($1, $2); }
  ;

tipo_simples : INT                                        {$$ = new TipoSimples(PINT); }
  | LOGICO                                                {$$ = new TipoSimples(PLOGICO); }
  | FLUT                                                  {$$ = new TipoSimples(PFLUT); }
  | CARAC                                                 {$$ = new TipoSimples(PCARAC); }
  ;

colchetes_ou_vazio :                                      {$$ = new ColchetesOuVazio(); }
  | '[' expr_const ']'colchetes_ou_vazio                  {$$ = new ColchetesOuVazio($2, $4); }
  ;

registro : ESTRUTURA '{' lista_dec_atr '}'                {$$ = new Registro($3);}
  ;

lista_dec_atr : dec_atr                                   {$$ = new ListaDecAtr($1);}
  | dec_atr ',' lista_dec_atr                             {$$ = new ListaDecAtr($1, $3);}    
  ;

dec_atr : lista_id_vars ':' tipo                          {$$ = new DecAtr($1, $3);}
  ;

comando : CONTINUE                                         {$$ = new Comando(ECONTINUE); }
  | PARE                                                   {$$ = new Comando(EPARE); }
  | retorno                                                {$$ = new Comando($1); }
  | novo_bloco                                             {$$ = new Comando($1); }
  | controle                                               {$$ = new Comando($1); }
  | repeticao                                              {$$ = new Comando($1); }
  | ESCREVA '(' lista_expr ')'                             {$$ = new Comando($3); }
  | LEIA '(' variavel ')'                                  {$$ = new Comando($3); }
  | atribuicao                                             {$$ = new Comando($1); }
  | ID '(' ')'                                             {$$ = new Comando($1); }
  | ID '(' lista_expr ')'                                  {$$ = new Comando($1, $3); }
  ;

atribuicao : variavel '=' expr                          {$$ = new Atribuicao($1, $3);}
  ;

lista_expr : expr                                       {$$ = new ListaExpr($1);}
  | expr ',' lista_expr                                 {$$ = new ListaExpr($1, $3);}
  ;

controle : se                                           {$$ = new Controle($1);}
  | escolha                                             {$$ = new Controle($1);}
  ;

se : SE '(' expr ')' bloco senao                        {$$ = new Se($3, $5, $6);}
  | SE '(' expr ')' bloco                               {$$ = new Se($3, $5);} 
  ;

senao : SENAO bloco                                     {$$ = new Senao($2);}
  | SENAO se                                            {$$ = new Senao($2);}
  ;

escolha : ESCOLHA '(' expr ')' '{' lista_casos '}'      {$$ = new Escolha($3, $6);}
  ;

lista_casos : escolha_padrao                            {$$ = new ListaCasos($1);}
  | caso_escolha                                        {$$ = new ListaCasos($1);}
  | caso_escolha ';' lista_casos                        {$$ = new ListaCasos($1, $3);}
  ;

escolha_padrao : PADRAO ':' comando                     {$$ = new EscolhaPadrao($3);}
  ;

caso_escolha : CASO expr_const ':' comando              {$$ = new CasoEscolha($2, $4);}
  ;

repeticao : enquanto                                    {$$ = new Repeticao($1);}
  | faca_enquanto                                       {$$ = new Repeticao($1);}
  | para                                                {$$ = new Repeticao($1);}
  ;

enquanto : ENQUANTO '(' expr ')' bloco                  {$$ = new Enquanto($3, $5);}
  ;

faca_enquanto : FACA bloco ENQUANTO '(' expr ')'        {$$ = new FacaEnquanto($2, $5);}
  ;

para : PARA '(' atribuicao ';' expr ';' atribuicao ')' bloco {$$ = new Para($3, $5, $7, $9);}
  ;

retorno : RETORNE                                     {$$ = new Retorno();}
  | RETORNE expr                                      {$$ = new Retorno($2);}
  ;

variavel : ID                                         {$$ = new Variavel($1);}
  | ID lista_modificadores                            {$$ = new Variavel($1, $2);}
  ;

lista_modificadores : modificador_variavel            {$$ = new ListaModificadores($1);}
  | modificador_variavel lista_modificadores          {$$ = new ListaModificadores($1, $2);}
  ;

modificador_variavel : '.' ID                         {$$ = new ModificadorVariavel($2); }
  | '[' expr ']'                                      {$$ = new ModificadorVariavel($2); }
  ;

literal : literal_logico                              {$$ = new Literal($1);}
  | LIT_INT                                           {$$ = new Literal(stoi(yytext));}
  | LIT_FLUT                                          {$$ = new Literal(stof(yytext));}
  | LIT_CHAR                                          {$$ = new Literal(yytext[1]);}
  | literal_array                                     {$$ = new Literal($1);}
  ;

literal_logico : VERDADEIRO                           {$$ = new LiteralLogico(true);}
  | FALSO                                             {$$ = new LiteralLogico(false);}
  ;

literal_array : LIT_STRING                            {$$ = new LiteralArray();}
  | '[' lista_literais']'                             {$$ = new LiteralArray($2);}
  ;

lista_literais : literal                              {$$ = new ListaLiterais($1);}
  | literal ',' lista_literais                        {$$ = new ListaLiterais($1, $3);}
  ;

expr : expr '+' expr                                  {$$ = new Expr($1, PLUS, $3);}
  | expr '-' expr                                     {$$ = new Expr($1, MINUS, $3);}
  | expr '*' expr                                     {$$ = new Expr($1, TIMES, $3);}
  | expr MOD expr                                     {$$ = new Expr($1, MODOP, $3);}
  | expr '/' expr                                     {$$ = new Expr($1, DIV, $3);}
  | expr '^' expr                                     {$$ = new Expr($1, EXP, $3);}
  | expr IGUAL_IGUAL expr                             {$$ = new Expr($1, EQ, $3);}
  | expr DIFERENTE expr                               {$$ = new Expr($1, DIF, $3);}
  | expr MENOR_IGUAL expr                             {$$ = new Expr($1, LEQ, $3);}
  | expr MAIOR_IGUAL expr                             {$$ = new Expr($1, GEQ, $3);}
  | expr '<' expr                                     {$$ = new Expr($1, LESS, $3);}
  | expr '>' expr                                     {$$ = new Expr($1, GREATER, $3);}
  | expr 'e' expr                                     {$$ = new Expr($1, AND, $3);}
  | expr OU expr                                      {$$ = new Expr($1, OR, $3);}
  | '+' expr %prec UPLUS                              {$$ = new Expr(UNARY_PLUS, $2);}
  | '-' expr %prec UMINUS                             {$$ = new Expr(UNARY_MINUS, $2);}
  | '!' expr                                          {$$ = new Expr(NOT, $2);}
  | '%' tipo '%' expr %prec CASTING                   {$$ = new Expr($2, $4);}
  | '(' expr ')'                                      {$$ = new Expr($2);}
  | folha_expr                                        {$$ = new Expr($1);}
  ;

folha_expr : literal                                  {$$ = new FolhaExpr($1);}
  | variavel                                          {$$ = new FolhaExpr($1);}
  | ID '(' ')'                                        {$$ = new FolhaExpr($1);}
  | ID '(' lista_expr ')'                             {$$ = new FolhaExpr($1, $3); }
  | ID '(' ')' lista_modificadores                    {$$ = new FolhaExpr($1, nullptr, $4); }
  | ID '(' lista_expr ')' lista_modificadores         {$$ = new FolhaExpr($1, $3, $5); }
  ;

expr_const : expr_const '+' expr_const                                  {$$ = new ExprConst($1, PLUS, $3);}
  | expr_const '-' expr_const                                     {$$ = new ExprConst($1, MINUS, $3);}
  | expr_const '*' expr_const                                     {$$ = new ExprConst($1, TIMES, $3);}
  | expr_const MOD expr_const                                     {$$ = new ExprConst($1, MODOP, $3);}
  | expr_const '/' expr_const                                     {$$ = new ExprConst($1, DIV, $3);}
  | expr_const '^' expr_const                                     {$$ = new ExprConst($1, EXP, $3);}
  | expr_const IGUAL_IGUAL expr_const                             {$$ = new ExprConst($1, EQ, $3);}
  | expr_const DIFERENTE expr_const                               {$$ = new ExprConst($1, DIF, $3);}
  | expr_const MENOR_IGUAL expr_const                             {$$ = new ExprConst($1, LEQ, $3);}
  | expr_const MAIOR_IGUAL expr_const                             {$$ = new ExprConst($1, GEQ, $3);}
  | expr_const '<' expr_const                                     {$$ = new ExprConst($1, LESS, $3);}
  | expr_const '>' expr_const                                     {$$ = new ExprConst($1, GREATER, $3);}
  | expr_const 'e' expr_const                                     {$$ = new ExprConst($1, AND, $3);}
  | expr_const OU expr_const                                      {$$ = new ExprConst($1, OR, $3);}
  | '+' expr_const %prec UPLUS                              {$$ = new ExprConst(UNARY_PLUS, $2);}
  | '-' expr_const %prec UMINUS                             {$$ = new ExprConst(UNARY_MINUS, $2);}
  | '!' expr_const                                          {$$ = new ExprConst(NOT, $2);}
  | '%' tipo '%' expr_const %prec CASTING                   {$$ = new ExprConst($2, $4);}
  | '(' expr_const ')'                                      {$$ = new ExprConst($2);}
  | folha_expr_const                                        {$$ = new ExprConst($1);}
  ;

folha_expr_const : literal                                  {$$ = new FolhaExprConst($1);}
  ;

%% /* Fim da segunda seção */

void yyerror (const char *msg) {
	fprintf (stderr, "\033[1mLine %d (in column %d):\033[91m %s\033[0m\n", yylineno, collumn_counter - yyleng, msg);
}