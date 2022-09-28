d_str2token_enum = {
  "id" : "ID",
  "!" : "NAO",
  "%" : "CAST",
  "." : "PONTO",
  "," : "VIRGULA",
  "(" : "PAR_ESQ",
  ")" : "PAR_DIR",
  "[" : "COL_ESQ",
  "]" : "COL_DIR",
  "{" : "CHA_ESQ",
  "}" : "CHA_DIR",
  ":" : "DOIS_PONTOS",
  ";" : "PONTO_VIRG",
  "-" : "MENOS",
  "+" : "MAIS",
  "*" : "MULT",
  "/" : "DIV",
  "mod" : "MOD",
  "^" : "EXP",
  ">" : "MAIOR",
  "<" : "MENOR",
  ">=" : "MAIOR_IGUAL",
  "==" : "IGUAL_IGUAL",
  "<=" : "MENOR_IGUAL",
  "=" : "IGUAL",
  "!=" : "DIFERENTE",
}

def str2token_enum(x):
  if "\"" in x: x = x[1:-1]
  if x in d_str2token_enum:
    return d_str2token_enum[x]
  else:
    return x.upper()