# Pastas
incdir = include/
srcdir = src/
tmpdir = tmp/

#Vars
input_grammar = grammar.y
input_lexer = lexer.l

.DEFAULT_GOAL := all

lexico = $(tmpdir)lex.yy.cpp
yacc = $(tmpdir)y.tab.cpp


CFLAGS = -lm -I$(incdir)
# CFLAGS = -I$(incdir) -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

all: $(lexico) $(yacc) 
	g++ $(lexico) $(yacc) $(srcdir)tree_nodes.cpp $(srcdir)entry.cpp $(srcdir)main.cpp $(srcdir)symble_table.cpp  $(CFLAGS) -o parser

$(lexico): $(input_lexer)
	mkdir -p $(tmpdir)
	lex -o $(lexico) $(input_lexer)

$(yacc): $(input_grammar)
	mkdir -p $(tmpdir)
	yacc -d $(input_grammar) -o $(yacc)