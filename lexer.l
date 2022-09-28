%{

#include "token_id.h"
#include "symb_table.h"

int collumn_counter = 0;

SymbTable* symb_table;

void recur_dump(TrieNode* node, char* curr_name, int d){
  LinkedNode *curr = node->head->next;
  if(curr){
    printf("%s: ", curr_name);
    while(curr != NULL){
      printf("%s, ", curr->entry->x);
      curr = curr->next;
    }
    printf("\n");
  }

  for(int i = 0; i < ALPHA_SIZE; ++i){
    if(node->to[i] != NULL){
      curr_name[d] = i;
      recur_dump(node->to[i], curr_name, d + 1);
    }
  }
  curr_name[d] = '\0';
}

void dump(SymbTable* symb_table){
  printf("=========== START ==========\n");
  if(symb_table == NULL) return;
  int MAXSIZE = 100;
  char* temp = malloc(MAXSIZE * sizeof(char));
  memset(temp, '\0', MAXSIZE);
  recur_dump(symb_table->root, temp, 0);
  printf("============ END ===========\n\n");
  free(temp);
}

%}
%option yylineno
%option noyywrap

dig         [0-9]
alpha       [A-Z|a-z]
id          ({alpha}|\_)({alpha}|{dig}|\_)*
num_flut    [-+]?{dig}{dig}*\.{dig}{dig}*
num_int     [-+]?{dig}{dig}*

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
igual       "="
diferente   "!="

quebra_linha "\n"
comentario "//"(.)*

erro "."

%%

{num_flut} {
  printf(">> Token: LIT_FLUT (id %d), Valor: %s\t\n", LIT_FLUT, yytext);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return LIT_FLUT;
}

{num_int} {
  printf(">> Token: LIT_INT (id %d), Valor: %s\t\n", LIT_INT, yytext);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return LIT_INT;
}

{continue} {
  printf(">> Token: CONTINUE (id %d)\n", CONTINUE);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return CONTINUE;
}

{pare} {
  printf(">> Token: PARE (id %d)\n", PARE);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return PARE;
}

{se} {
  printf(">> Token: SE (id %d)\n", SE);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return SE;
}

{senao} {
  printf(">> Token: SENAO (id %d)\n", SENAO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return SENAO;
}

{enquanto} {
  printf(">> Token: ENQUANTO (id %d)\n", ENQUANTO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return ENQUANTO;
}

{faca} {
  printf(">> Token: FACA (id %d)\n", FACA);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return FACA;
}

{para} {
  printf(">> Token: PARA (id %d)\n", PARA);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return PARA;
}

{escolha} {
  printf(">> Token: ESCOLHA (id %d)\n", ESCOLHA);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return ESCOLHA;
}

{caso} {
  printf(">> Token: CASO (id %d)\n", CASO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return CASO;
}

{retorne} {
  printf(">> Token: RETORNE (id %d)\n", RETORNE);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return RETORNE;
}

{escreva} {
  printf(">> Token: ESCREVA (id %d)\n", ESCREVA);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return ESCREVA;
}

{var} {
  printf(">> Token: VAR (id %d)\n", VAR);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return VAR;
}

{const} {
  printf(">> Token: CONST (id %d)\n", CONST);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return CONST;
}

{mod} {
  printf(">> Token: MOD (id %d)\n", MOD);
  printf("token position: %d\n", collumn_counter);
  return MOD;
}

{declrs} {
  printf(">> Token: DECLRS (id %d)\n", DECLRS);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return DECLRS;
}

{proc} {
  printf(">> Token: PROC (id %d)\n", PROC);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return PROC;
}

{func} {
  printf(">> Token: FUNC (id %d)\n", FUNC);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return FUNC;
}

{estrutura} {
  printf(">> Token: ESTRUTURA (id %d)\n", ESTRUTURA);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return ESTRUTURA;
}

{bloco} {
  printf(">> Token: BLOCO (id %d)\n", BLOCO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return BLOCO;
}

{tipo} {
  printf(">> Token: TIPO (id %d)\n", TIPO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return TIPO;
}

{int} {
  printf(">> Token: INT (id %d)\n", INT);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return INT;
}

{logico} {
  printf(">> Token: LOGICO (id %d)\n", LOGICO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return LOGICO;
}

{flut} {
  printf(">> Token: FLUT (id %d)\n", FLUT);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return FLUT;
}

{carac} {
  printf(">> Token: CARAC (id %d)\n", CARAC);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return CARAC;
}

{ref} {
  printf(">> Token: REF (id %d)\n", REF);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return REF;
}

{dois_pontos} {
  printf(">> Token: DOIS_PONTOS (id %d)\n", DOIS_PONTOS);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return DOIS_PONTOS;
}

{verdadeiro} {
  printf(">> Token: VERDADEIRO (id %d)\n", VERDADEIRO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return VERDADEIRO;
}

{falso} {
  printf(">> Token: FALSO (id %d)\n", FALSO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return FALSO;
}

{ou} {
  printf(">> Token: OU (id %d)\n", OU);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return OU;
}

{e} {
  printf(">> Token: E (id %d)\n", E);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return E;
}

{nao} {
  printf(">> Token: NAO (id %d)\n", NAO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return NAO;
}

{ponto_virg} {
  printf(">> Token: PONTO_VIRG (id %d)\n", PONTO_VIRG);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return PONTO_VIRG;
}

{ponto} {
  printf(">> Token: PONTO (id %d)\n", PONTO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return PONTO;
}

{virgula} {
  printf(">> Token: VIRGULA (id %d)\n", VIRGULA);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return VIRGULA;
}

{par_esq} {
  printf(">> Token: PAR_ESQ (id %d)\n", PAR_ESQ);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return PAR_ESQ;
}

{cast} {
  printf(">> Token: CAST (id %d)\n", CAST);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return CAST;
}


{par_dir} {
  printf(">> Token: PAR_DIR (id %d)\n", PAR_DIR);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return PAR_DIR;
}

{col_esq} {
  printf(">> Token: COL_ESQ (id %d)\n", COL_ESQ);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return COL_ESQ;
}

{col_dir} {
  printf(">> Token: COL_DIR (id %d)\n", COL_DIR);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return COL_DIR;
}

{cha_esq} {
  printf(">> Token: CHA_ESQ (id %d)\n", CHA_ESQ);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return CHA_ESQ;
}

{cha_dir} {
  printf(">> Token: CHA_DIR (id %d)\n", CHA_DIR);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return CHA_DIR;
}

{id} {
  printf(">> Token: ID (id %d), Valor: %s\t\n", ID, yytext);
  printf("token position: %d\n", collumn_counter);

  // Entry* e = _get(symb_table, yytext, yyleng, 1);
  // strcpy(e->x, yytext);

  // dump(symb_table);
  
  collumn_counter += yyleng;
  return ID;
}

{menos} {
  printf(">> Token: MENOS (id %d)\n", MENOS);
  printf("token position: %d\n", collumn_counter);
  return MENOS;
}

{mais} {
  printf(">> Token: MAIS (id %d)\n", MAIS);
  printf("token position: %d\n", collumn_counter);
  return MAIS;
}


{mult} {
  printf(">> Token: MULT (id %d)\n", MULT);
  printf("token position: %d\n", collumn_counter);
  return MULT;
}

{div} {
  printf(">> Token: DIV (id %d)\n", DIV);
  printf("token position: %d\n", collumn_counter);
  return DIV;
}

{exp} {
  printf(">> Token: EXP (id %d)\n", EXP);
  printf("token position: %d\n", collumn_counter);
  return EXP;
}

{comentario} {
  printf(">> Token: COMENTARIO (id %d)\n", COMENTARIO);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return COMENTARIO;
}

{maior} {
  printf(">> Token: MAIOR (id %d)\n", MAIOR);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return MAIOR;
}

{menor} {
  printf(">> Token: MENOR (id %d)\n", MENOR);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return MENOR;
}

{maior_igual} {
  printf(">> Token: MAIOR_IGUAL (id %d)\n", MAIOR_IGUAL);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return MAIOR_IGUAL;
}

{menor_igual} {
  printf(">> Token: MENOR_IGUAL (id %d)\n", MENOR_IGUAL);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return MENOR_IGUAL;
}

{igual} {
  printf(">> Token: IGUAL (id %d)\n", IGUAL);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return IGUAL;
}

{diferente} {
  printf(">> Token: DIFERENTE (id %d)\n", DIFERENTE);
  printf("token position: %d\n", collumn_counter);
  collumn_counter += yyleng;
  return DIFERENTE;
}

{quebra_linha} {
  printf(">> Token: QUEBRA_LINHA (id %d)\n", QUEBRA_LINHA);
  printf("token position: %d\n", collumn_counter);
  collumn_counter = 0;
  // return QUEBRA_LINHA;
}

{espaco_branco} {
  collumn_counter += yyleng;
}

%%