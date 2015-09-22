# Read Me

## Description

This is a generic hashtable implementation in C. Once you create the table the key and value type is fixed, but you can use any type you want so long as you provide the appropriate functions to handle equality checks and memory deallocation (destroy). In `test.c` you will see an example of this hash table usage with strings (char *) as both the key and value type. 

## Usage

Example makefile that uses HashTable project as library: 

	# Variavles
	COMPILER = gcc
	GCC_FLAGS = -g -Wall -pthread

	INCLUDE_PATHS = \
	  -I ./include/ \
	  -I ./source/hash_table/include/ \

	OBJECT_FILES = \
	  book_order.o \
	  util.o \
	  string_builder.o \
	  node.o \
	  person.o \
	  linked_list.o \
	  request.o \
	  order.o \
	  file_tok.o \
	  parser.o \
	  queue.o \
	  ref_count_pointer.o \

	LIBRARY_PATHS = \
	  source/hash_table/hash_table.a \

	#Included Projects
	PROJ_hash_table = ./source/hash_table/

	# Convenience Rules
	all: book_order

	# External Libraries
	.PHONY: $(LIBRARY_PATHS) submit

	# Library Compilation
	source/hash_table/hash_table.a:
		make -C $(PROJ_hash_table) hash_table.a

	# Object Files
	%.o: ./source/%.c ./include/%.h
		$(COMPILER) $(INCLUDE_PATHS) $(GCC_FLAGS) -c $< -o $@	

	# Executables
	book_order: $(OBJECT_FILES) $(LIBRARY_PATHS)
		$(COMPILER) $(INCLUDE_PATHS) $(GCC_FLAGS) $^ -o $@

	# Clean
	clean:
		rm -rf book_order
		rm -rf $(OBJECT_FILES)
		make -C $(PROJ_hash_table) clean

