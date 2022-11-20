#ifndef LINKED_TRIE_NODE
#define LINKED_TRIE_NODE

#include <stdlib.h>
#include <string.h>

#include "entry.hpp"

#define ALPHA_SIZE 256

struct LinkedNode {
  struct LinkedNode *next, *prev;
  Entry* entry;

  LinkedNode():next(nullptr), prev(nullptr), entry(nullptr){};

};

struct TrieNode {
  struct TrieNode* to[ALPHA_SIZE];
  LinkedNode *head, *last;
  // int active_child_cnt;

  TrieNode(): head(new LinkedNode()), last(head)
  // , active_child_cnt(0)
  {
    memset(to, 0, sizeof to);
  }

  static TrieNode* get(string* name, TrieNode* root, bool create_if_needed) {
    TrieNode* curr_node = root;
    for(int i = 0; (i < name->size()) && curr_node; ++i){
      char next_char = (*name)[i];

      if(curr_node->to[next_char] == nullptr && create_if_needed){
        curr_node->to[next_char] = new TrieNode();
        // curr_node->active_child_cnt++;
      }

      curr_node = curr_node->to[next_char];
    }

    if(curr_node == NULL || curr_node->last == NULL) return NULL;
    return curr_node;    
  }

  /*
  // nao vai ser usado se sair do escopo for so popback
  void remove(string *name, int i, TrieNode* prev_node){
    char char_to_curr = (*name)[i - 1];

    if(i == name->size()) pop_back();
    else{
      char char_to_nxt = (*name)[i];
      if(to[char_to_nxt]){
        to[char_to_nxt]->remove(name, i, this);
      }else exit(1);
    }

    if((head == last) && (active_child_cnt == 0)) {
      delete head->entry;
      delete head;

      delete prev_node->to[char_to_curr];
      prev_node->to[char_to_curr] = NULL;
      prev_node->active_child_cnt--;
    }
  }
  */

  LinkedNode* push_back(Entry* entry) {
    if(last == NULL) return NULL;

    LinkedNode* new_node =  new LinkedNode();

    new_node->prev = last;
    new_node->entry = entry;
    last->next = new_node;
    last = new_node;

    return new_node;
  }

  void pop_back() {
    if(last == head) exit(1);
      
    LinkedNode* new_last = last->prev;

    switch(last->entry->entry_type){
      case CONSTANT:
        delete ((Constant*) last->entry);
        break;
      case VARIABLE:
        delete ((Variable*) last->entry);
        break;
      case FUNCTION:
        delete ((Function*) last->entry);
        break;
      case PROCEDURE:
        delete ((Procedure*) last->entry);
        break;
      case TYPE:
        delete ((Type*) last->entry);
        break;
    }
    delete last;

    new_last->next = nullptr;
    last = new_last;
  }
};

#endif