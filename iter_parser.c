#include "src/token_id.h"
#include "src/rule_id.h"
#include "src/stack.h"

#include "lex.yy.c"


enum TOKEN_ID tok;
void advance() {tok=yylex();}
void error(){ 1/0; }
void eat(enum TOKEN_ID t) {if (tok==t) advance(); else error();}

SymbolStack *s;

void PROGRAMA() { switch (tok) {
  case CONST: case DECLRS: case BLOCO:{
    pop(s);
    push_non_terminal(s, E_NOVO_BLOCO);
    push_non_terminal(s, E_DECLARACOES);
    push_non_terminal(s, E_DEFINICOES);
    break;
  }
  default: error();
}}


int main(){
  s = create_stack();
  push_non_terminal(s, E_PROGRAMA);

  while(s->size > 0){
    Symbol* s_top = top(s);
    if(s_top->is_tok == 1){
      eat(s_top->type.tok);
    }else{ // eh nao terminal
      // assert(s_top->is_tok);
      switch (s_top->type.rule) {
        case E_PROGRAMA: PROGRAMA(); break;
        default: error();
      }
    }
  } 
}