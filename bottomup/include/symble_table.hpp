#ifndef SYMB_TABLE
#define SYMB_TABLE

#include <string>
#include <stack>

#include "linked_trie_node.hpp"

/*
lex: pra inserir coisas
sint: pra ver se as coisas inseridas estao como esperados
seman: todas as variaveis definidas estao sendo usadas
seman: todas as variaveis usadas estao sendo definidas
*/

typedef struct SymbTable{
  TrieNode* root;
} SymbTable;

class SymbleTable{
public:
  TrieNode* root;

  stack<vector<TrieNode*>> scope;

  SymbleTable();

  void add_scope();

  void pop_scope();
  // ler variavel
  // pegar tipo
  // acessar argumentos de funcao/proc
  // acessar retorno de funcao
  // acessar valor de funcao
  Entry* get(string* name);

  // void remove(string *name){
  //   return root->remove(name, 0, nullptr);
  // }

  // declaracao de variavel
  // declaracao de constante
  // declaracao de funcao
  // declaracao de procedimento
  void add_entry(string *name, Entry* entry);
  
  // create type estrutura
  Type* create_type(vector<pair<Type*, string*>> attr_list);
};

extern SymbleTable symble_table;

#endif