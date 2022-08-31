#include <stdio.h>
#include "symb_table.h"

void recur_dump(TrieNode* node, char* curr_name, int d){
  LinkedNode *curr = node->head->next;
  if(curr){
    printf("%s: ", curr_name);
    while(curr != NULL){
      printf("%d, ", curr->entry->x);
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


char in[100];
SymbTable* symb_table;

int main(){
  build_table(&symb_table);
  int q; scanf("%d", &q);
  while(q--){
    int t; scanf("%d", &t);
    int n; scanf("%d", &n);
    scanf("%s", in);

    // printf("s: %s\n", in);

    if(t == 0){
      Entry* e = _get(symb_table, in, n, 1);

      int x; scanf("%d", &x);
      e->x = x;
    }else{
      _remove(symb_table, in, n);
    }

    dump(symb_table);
  }
}