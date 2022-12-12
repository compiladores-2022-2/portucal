#ifndef CODE_GEN
#define CODE_GEN

#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;

namespace code_gen{

stack<pair<int,int>> loop_goto;

int next_label = 1;
int get_next_label(){
  return next_label++;
}

string gen_label(int label_id){
  return "G" + to_string(label_id);
}

string concat_code(const vector<string> strs){
  string code = "";
  for(auto str : strs) code += str;
  return code;
}

vector<pair<string, string>> var_types;
int next_var_id = 0;
string gen_var(pair<string,string> type){
  var_types.push_back(type);
  return "t" + to_string(next_var_id++);
}

string print_vars(){
  std::map<pair<string,string>,vector<int>> type2ids;
  for(int i = 0; i < next_var_id; ++i){
    type2ids[var_types[i]].push_back(i);
  }

  string code = "";
  for(auto &[type, ids] : type2ids){
    string line = type.first;
    for(int i = 0; i < ids.size(); ++i){
      line += " t" + to_string(ids[i]) + type.second;
      if(i + 1 < ids.size()) line += ",";
    }
    line += ";";
    code += line + "\n";
  }
  return code;
}

string get_op_name(OP operand){
  switch(operand)
  {
    case PLUS: return "+";
    case MINUS: return "-";
    case TIMES: return "*";
    case MODOP: return "%";
    case DIV: return "/";
    // case EXP
    case EQ: return "==";
    case DIF: return "!=";
    case LEQ: return "<=";
    case GEQ: return ">=";
    case LESS: return "<";
    case GREATER: return ">";
    case AND: return "&&";
    case OR: return "||";
    case UNARY_PLUS: return "+";
    case UNARY_MINUS: return "-";
    case NOT: return "!";
    default:
      exit(1);
  }
}

bool is_op_rel(OP op){
  switch(op){
    case EQ: case DIF: case LEQ: case GEQ: case LESS: case GREATER: return true;
    default: return false;
  }
}

}

#endif