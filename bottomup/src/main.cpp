
#include <iostream>
using namespace std;

#include "symble_table.hpp"

void yyparse();

int main(){
  CHAR_TYPE = new PrimitiveType();
  BOOL_TYPE = new PrimitiveType();
  INT_TYPE = new PrimitiveType();
  FLUT_TYPE = new PrimitiveType();
	yyparse();
}