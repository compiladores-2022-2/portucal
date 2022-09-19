#ifndef LINKED_TRIE_NODE
#define LINKED_TRIE_NODE

#include <stdlib.h>
#include <string.h>

#include "entry.h"

#define ALPHA_SIZE 256

typedef struct LinkedNode {
  struct LinkedNode *next, *prev;
  Entry* entry;
} LinkedNode;

typedef struct TrieNode {
  struct TrieNode* to[ALPHA_SIZE];
  LinkedNode *head, *last;
  int active_child_cnt;
} TrieNode;

LinkedNode* create_linked_node(){
  LinkedNode* node = (LinkedNode*) malloc(sizeof(struct LinkedNode));
  node->next = node->prev = NULL;
  node->entry = NULL;
  return node;
}

TrieNode* create_trie_node() {
  TrieNode* node = (TrieNode*) malloc(sizeof(struct TrieNode));
  memset(node->to, 0, sizeof node->to);
  node->head = create_linked_node();
  node->last = node->head;
  node->active_child_cnt = 0;
  return node;
}

LinkedNode* append_linked_node(TrieNode* trie_node) {
  if(trie_node == NULL || trie_node->last == NULL) 
    return NULL;

  LinkedNode* new_node = create_linked_node();

  new_node->prev = trie_node->last;
  new_node->entry = (Entry*) malloc(sizeof(struct Entry));
  trie_node->last->next = new_node;
  trie_node->last = new_node;

  return new_node;
}

int delete_last_node(TrieNode* trie_node) {
  if(trie_node == NULL || trie_node->last == trie_node->head)
    return 0;
  
  LinkedNode* new_last = trie_node->last->prev;

  free(trie_node->last->entry);
  free(trie_node->last);

  new_last->next = NULL;
  trie_node->last = new_last;
  return 1;
}

int _remove_from_trie(char* name, int size, int i, TrieNode* prev_node, TrieNode* curr_node){
  char char_to_curr = name[i - 1];

  if(i == size) delete_last_node(curr_node);
  else{
    char char_to_nxt = name[i];
    if(curr_node->to[char_to_nxt]){
      _remove_from_trie(name, size, i + 1, curr_node, curr_node->to[char_to_nxt]);
    }else return 0;
  }

  if((curr_node->head == curr_node->last) && (curr_node->active_child_cnt == 0)) {
    free(curr_node->head->entry);
    free(curr_node->head);
    free(prev_node->to[char_to_curr]);
    prev_node->to[char_to_curr] = NULL;
    prev_node->active_child_cnt--;
  }

  return 1;
}

#endif