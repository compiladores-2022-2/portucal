
#include <iostream>
using namespace std;

#include "symble_table.hpp"

void yyparse();

int main(){
  CHAR_TYPE = new PrimitiveType("char");
  BOOL_TYPE = new PrimitiveType("bool");
  INT_TYPE = new PrimitiveType("int");
  FLUT_TYPE = new PrimitiveType("float");
	yyparse();
}