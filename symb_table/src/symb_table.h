#ifndef SYMB_TABLE
#define SYMB_TABLE

#include <stdlib.h>
#include <string.h>

#include "linked_trie_node.h"

/*
lex: pra inserir coisas
sint: pra ver se as coisas inseridas estao como esperados
seman: todas as variaveis definidas estao sendo usadas
seman: todas as variaveis usadas estao sendo definidas
*/

typedef struct SymbTable{
  TrieNode* root;
} SymbTable;

Entry* _get(SymbTable* symb_table, char* name, int size, int create) {
  if(symb_table == NULL || size <= 0) return NULL;

  TrieNode* curr_node = symb_table->root;

  
  for(int i = 0; (i < size) && curr_node; ++i){
    char next_char = name[i];

    if(curr_node->to[next_char] == NULL && create == 1){
      curr_node->to[next_char] = create_trie_node();
      curr_node->active_child_cnt++;
    }

    curr_node = curr_node->to[next_char];
  }

  if(curr_node == NULL || curr_node->last == NULL) return NULL;
  if(create == 0){
    if(curr_node->head == curr_node->last || curr_node->last->entry == NULL)
      return NULL; 
    else return curr_node->last->entry;
  }else{
    LinkedNode* last_node = append_linked_node(curr_node);
    if(last_node == NULL) return NULL;
    else return last_node->entry;
  }
}

int _remove(SymbTable* symb_table, char *name, int size){
  if(symb_table == NULL || size <= 0) return 0;

  TrieNode *start = symb_table->root->to[name[0]];
  if(start) return _remove_from_trie(name, size, 1, symb_table->root, start);
  else return 0;  
}

void build_table(SymbTable** symb_table) {
  *symb_table = (SymbTable*) malloc(sizeof(struct SymbTable));
  (*symb_table)->root = create_trie_node();
}

#endif