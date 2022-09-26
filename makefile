CXXFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

# Pastas
srcdir = ./src
objdir = ./obj

#Vars
objects = $(objdir)/tester.o
# CFLAGS = -I$(srcdir) -W -g -lm 
CFLAGS = -I$(srcdir) -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold


tester: $(objects)
	gcc -o tester $(objects) $(CFLAGS)
$(objdir)/tester.o: $(srcdir)/token_id.h $(srcdir)/rule_id.h $(srcdir)/entry.h $(srcdir)/linked_trie_node.h $(srcdir)/symb_table.h
	mkdir -p obj
	lex lex.l
	gcc -c lex.yy.c -o $(objdir)/tester.o $(CFLAGS)
