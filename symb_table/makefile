CXXFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold

# Pastas
srcdir = ./src

#Vars
objects = $(objdir)/tester.o
# CFLAGS = -I$(srcdir) -W -g -lm 
CFLAGS = -I$(srcdir) -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts #-fuse-ld=gold


catarata: $(objects)
	gcc -o catarata $(objects) $(CFLAGS)
$(objdir)/tester.o: $(srcdir)/entry.h $(srcdir)/linked_trie_node.h $(srcdir)/symb_table.c
	mkdir -p obj
	gcc -c tester.c -o $(objdir)/tester.o $(CFLAGS)
