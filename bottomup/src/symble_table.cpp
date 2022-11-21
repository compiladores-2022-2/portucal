#include "symble_table.hpp"
#include <iostream>

SymbleTable::SymbleTable() {
  root = new TrieNode();
  scope.push({});
}

void SymbleTable::add_scope(){
  scope.push({});
}

void SymbleTable::pop_scope(){
  for(auto node : scope.top()) node->pop_back();
  scope.pop();
}

// ler variavel
// pegar tipo
// acessar argumentos de funcao/proc
// acessar retorno de funcao
// acessar valor de funcao
Entry* SymbleTable::get(string* name) {
  TrieNode* node = TrieNode::get(name, root, false);

  if(node == nullptr) return nullptr;
  else return node->last->entry;
}

// declaracao de variavel
// declaracao de constante
// declaracao de funcao
// declaracao de procedimento
void SymbleTable::add_entry(string *name, Entry* entry){
  TrieNode* node = TrieNode::get(name, root, true);

  if(node == nullptr){
    yyerror("Error");
    exit(1);
  }
  for(auto past_node : scope.top())
    if(past_node == node){
      yyerror("Name already being used");
      exit(1);
    }
  
  scope.top().push_back(node);
  
  node->push_back(entry);
}

// create type estrutura
// Type* SymbleTable::create_type(vector<pair<Type*, string*>> attr_list){
//   scope.top().push_back(root);

//   Entry* entry = new Type(attr_list);
//   root->push_back(entry);
//   return (Type*) entry;
// }

extern SymbleTable symble_table;
