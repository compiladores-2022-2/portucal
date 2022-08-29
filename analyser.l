%{

enum TOKEN_ID{
  // NUM_..
  // CONTNUE ...
  ID,
  CONTINUE
};


%}
  

dig         [0-9]
alpha       [A-Z|a-z]
id          ({alpha}|\_)({alpha}|{dig}|\_)*
num_flut    [-+]?{dig}{dig}*\.{dig}{dig}*
num_int     [-+]?{dig}{dig}*

continue    "continue"
pare        "pare"
se          "se"
senao       "senão"
enquanto    "enquanto"
faca        "faça"
para        "para"
escolha     "escolha"
caso        "caso"
padrao      "padrao"
retorne     "retorne"
leia        "leia"
imprima     "imprima"

var         "var"
const       "const"
declrs      "declrs"
proc        "proc"
func        "func"
estrutura   "estrutura"
bloco       "bloco"
tipo        "tipo"

int         "int"
logico      "logico"
flut        "flut"
carac       "carac"
ref         "ref"

verdadeiro  "verdadeiro"
falso       "falso" 
ou          "ou" 			
e           "e"			
nao         "!"

dois_pontos ":"
ponto_virg  ";"
left_p      "("
right_p     ")"
left_b      "["
right_b     "]"
left_k      "{"
right_k     "}"
ponto       "."
virgula     ","

menos       "-"					 
mais        "+"					
mult        "*"					
div         "/"					
mod 				"%"
exp         "^"

maior       ">"					
menor       "<"					
maior_igual ">="				
menor_igual "<="				
igual       "="
diferente   "!="				
					


resto/defacult/erro "."


%%

{num_flut} {
  printf("TOKEN: FLUTUANTE\t");
  printf("VALOR: %s\t", yytext);
  printf("\n");
}

{num_int} {
  printf("TOKEN: INTEIRO\t");
  printf("VALOR: %s\t", yytext);
  printf("\n");
}

{continue} { printf("TOKEN: CONTINUE\n");
  return TOKEN_ID::CONTINUE;
}
{pare} { printf("TOKEN: PARE\n");}
{se} { printf("TOKEN: SE\n");}
{senao} { printf("TOKEN: SENAO\n");}
{enquanto} { printf("TOKEN: ENQUANTO\n");}
{faca} { printf("TOKEN: FACA\n");}

{para} { printf("TOKEN: PARA\n");}
{escolha} { printf("TOKEN: ESCOLHA\n");}
{caso} { printf("TOKEN: CASO\n");}
{padrao} { printf("TOKEN: CASO\n");}
{retorne} { printf("TOKEN: RETORNE\n");}
{imprima} { printf("TOKEN: IMPRIMA\n");}

{var} { printf("TOKEN: VAR\n");}


{var}  { printf("TOKEN: VAR\n");}
{const} { printf("TOKEN: VAR\n");}
{declrs} { printf("TOKEN: VAR\n");}
{proc} { printf("TOKEN: VAR\n");}
{func} { printf("TOKEN: VAR\n");}
{estrutura} { printf("TOKEN: VAR\n");}
{bloco} { printf("TOKEN: VAR\n");}
{tipo} { printf("TOKEN: VAR\n");}

{int} { printf("TOKEN: VAR\n");}
{logico} { printf("TOKEN: VAR\n");}
{flut} { printf("TOKEN: VAR\n");}
{carac} { printf("TOKEN: VAR\n");}
{ref} { printf("TOKEN: VAR\n");}

{verdadeiro} { printf("TOKEN: VAR\n");}
{falso}  { printf("TOKEN: VAR\n");}
{ou}  { printf("TOKEN: VAR\n");} 			
{e}  { printf("TOKEN: VAR\n");}		
{nao} { printf("TOKEN: VAR\n");}

{dois_pontos} { printf("TOKEN: VAR\n");}
{ponto_virg} { printf("TOKEN: VAR\n");}
{left_p} { printf("TOKEN: VAR\n");}
{right_p} { printf("TOKEN: VAR\n");}
{left_b} { printf("TOKEN: VAR\n");}
{right_b} { printf("TOKEN: VAR\n");}
{left_k} { printf("TOKEN: VAR\n");}
{right_k} { printf("TOKEN: VAR\n");}
{ponto} { printf("TOKEN: VAR\n");}
{virgula} { printf("TOKEN: VAR\n");}

{menos} { printf("TOKEN: VAR\n");}
{mais} { printf("TOKEN: VAR\n");}
{mult} { printf("TOKEN: VAR\n");}
{div} { printf("TOKEN: VAR\n");}
{mod} { printf("TOKEN: VAR\n");}
{exp} { printf("TOKEN: VAR\n");}

{maior} { printf("TOKEN: VAR\n");}				
{menor} { printf("TOKEN: VAR\n");}					
{maior_igual} { printf("TOKEN: VAR\n");}				
{menor_igual} { printf("TOKEN: VAR\n");}				
{igual} { printf("TOKEN: VAR\n");}
{diferente} { printf("TOKEN: VAR\n");}				
					

{id} {
  printf("TOKEN: ID\t");
  printf("VALOR: %s\t", yytext);
  printf("\n");
}


%%

int yywrap(){}
int main(int argc, char **argv){
  yylex();
  return 0;
}
