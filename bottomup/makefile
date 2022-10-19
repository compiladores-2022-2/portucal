# Pastas
srcdir = src

#Vars
input_grammar = grammar.y
input_lexer = lexer.l

.DEFAULT_GOAL := all

lexico = $(srcdir)/lex.yy.c
yacc = $(srcdir)/y.tab.c
CFLAGS = -W -g -lm 
# CFLAGS = -I$(srcdir) -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

all: $(lexico) $(yacc)
	gcc $(lexico) $(yacc) $(CFLAGS) -o parser

$(lexico): $(input_lexer)
	mkdir -p $(srcdir)
	lex -o $(lexico) $(input_lexer)

$(yacc): $(input_grammar)
	mkdir -p $(srcdir)
	yacc -d $(input_grammar) -o $(yacc)