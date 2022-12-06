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
objs = $(tmpdir)tree_nodes.o $(tmpdir)type.o $(tmpdir)main.o $(tmpdir)symble_table.o 

CFLAGS = -lm -I$(incdir)
# CFLAGS = -I$(incdir) -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

all: $(lexico) $(yacc) tree_nodes.o type.o main.o symble_table.o
	g++ $(lexico) $(yacc) $(objs) $(CFLAGS) -o parser

$(lexico): $(input_lexer)
	mkdir -p $(tmpdir)
	lex -o $(lexico) $(input_lexer)

$(yacc): $(input_grammar)
	mkdir -p $(tmpdir)
	yacc -d $(input_grammar) -o $(yacc)

%.o: $(srcdir)%.cpp
	g++ -c $< -o $(tmpdir)$@ $(CFLAGS)