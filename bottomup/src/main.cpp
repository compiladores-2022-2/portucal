
#include <iostream>
using namespace std;

#include "symble_table.hpp"

void yyparse();

int main(){
  CHAR_TYPE = new Type({}, nullptr, true);
  BOOL_TYPE = new Type({}, nullptr, true);
  INT_TYPE = new Type({}, nullptr, true);
  FLUT_TYPE = new Type({}, nullptr, true);

  

	yyparse();
}