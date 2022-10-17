# Pastas
srcdir = ../src
objdir = ../obj

#Vars
lexico = $(srcdir)/lex.yy.c
imports = $(srcdir)/token_id.h $(srcdir)/rule_id.h $(srcdir)/entry.h $(srcdir)/linked_trie_node.h $(srcdir)/symb_table.h
CFLAGS = -I$(srcdir) -W -g -lm 
# CFLAGS = -I$(srcdir) -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

all: recur iter

recur: $(lexico) $(imports) recur_parser.c
	gcc recur_parser.c $(CFLAGS) -o recur

iter: $(lexico) $(imports) iter_parser.c
	gcc iter_parser.c $(CFLAGS) -o iter

$(lexico): lexer.l
	lex -o $(lexico) lexer.l