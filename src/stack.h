#ifndef STACK
#define STACK

#include <stdlib.h>
#include <string.h>

#include "token_id.h"
#include "rule_id.h"

typedef struct Symbol{
  int is_tok;
  union{
    enum TOKEN_ID tok;
    enum RULE_ID rule;
  } type;
} Symbol;

typedef struct LinkedNodeStack {
  struct LinkedNodeStack *next, *prev;
  Symbol *symb;
} LinkedNodeStack;

typedef struct SymbolStack{
  int size;
  LinkedNodeStack* last;
} SymbolStack;

SymbolStack* create_stack(){
  SymbolStack* s = (SymbolStack*) malloc(sizeof(struct SymbolStack));
  s->last = (LinkedNodeStack*) malloc(sizeof(struct LinkedNodeStack));
  s->last->next = s->last->prev = NULL;
  s->size = 0;
  return s;
}

Symbol* top(SymbolStack *s){
  if(s->size == 0) return NULL;
  return s->last->symb;
}

void pop(SymbolStack *s){
  if(s->size > 0){
    // salvo ponteiro para no q vai ser deletado
    LinkedNodeStack *to_del = s->last; 

    // atualizo topo da pilha
    s->last = s->last->prev;

    // digo que topo nao tem nxt
    s->last->next = NULL;

    free(to_del->symb);
    free(to_del);
  }
}

void push(SymbolStack *s, Symbol *symb){
  // adicione o novo no como nxt do topo da pilha
  s->last->next = (LinkedNodeStack*) malloc(sizeof(struct LinkedNodeStack));

  // adicione o topo da pilha como anterior ao novo no
  s->last->next->prev = s->last;

  // atualize o topo da pilha
  s->last = s->last->next;

  // adicione o simbolo criado ao topo da pilha
  s->last->symb = symb;

  // diga que o topo da pilha nao tem next
  s->last->next = NULL;

  s->size++;
}

void push_terminal(SymbolStack *s, enum TOKEN_ID token){
  Symbol* symb = (Symbol*) malloc(sizeof(struct Symbol));
  symb->is_tok = 1;
  symb->type.tok = token;
  push(s, symb);
}

void push_non_terminal(SymbolStack *s, enum RULE_ID rule){
  Symbol* symb = (Symbol*) malloc(sizeof(struct Symbol));
  symb->is_tok = 0;
  symb->type.rule = rule;
  push(s, symb);
}


#endif