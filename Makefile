#Shortcuts
#	$<		first prereq
#	$@		target
#	$^		all prereqs
#	$(X)	expansion of variable X
# 	make -C lets you specify a directory to call `make` in

.DEFAULT_GOAL := libhashtable.a
PREFIX = /usr/local

CC 		= gcc
CFLAGS 	= -g -Wall -Iinclude
ARFLAGS	= rvs

override CFLAGS += -Iinclude

OBJ = HashTable.o HNode.o 
BIN = test

.PHONY: all clean install uninstall
all: $(.DEFAULT_GOAL) install $(BIN)

# Object Compilation
%.o: source/%.c include/%.h
	$(CC) $(CFLAGS) -c $< -o $@	

# Executables
test: source/test.c
	$(CC) $(CFLAGS) $< -o $@ -lhashtable

# Library
libhashtable.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

install:
	install -d $(PREFIX)/lib $(PREFIX)/include/hashtable
	install -m 0644 libhashtable.a $(PREFIX)/lib
	install -m 0644 include/*.h $(PREFIX)/include/hashtable

uninstall:
	rm -f $(PREFIX)/lib/libhashtable.a
	rm -rf $(PREFIX)/include/hashtable

clean:
	rm -f libhashtable.a
	rm -rf $(BIN) $(OBJ)
