#Shortcuts
#	$<		first prereq
#	$@		target
#	$^		all prereqs
#	$(X)	expansion of variable X
# 	make -C lets you specify a directory to call `make` in

# Variables
COMPILER = gcc
GCC_FLAGS = -g -Wall
ARCHIVE = ar
AR_FLAGS = rvs

INCLUDE_PATHS = \
-I ./include/ \

EXECUTABLES = \
test

LIBRARY_PATHS = \
hash_table.a

OBJECT_FILES = \
HashTable.o \
HNode.o 

# Convenience Rules
all: target
target: test

# Object Compilation
%.o: ./source/%.c ./include/%.h
	$(COMPILER) $(INCLUDE_PATHS) $(GCC_FLAGS) -c $< -o $@	

# Executables
test: test.o $(OBJECT_FILES)
	$(COMPILER) $(INCLUDE_PATHS) $(GCC_FLAGS) $^ -o $@

# Library
hash_table.a: $(OBJECT_FILES)
	$(ARCHIVE) $(AR_FLAGS) $@ $^

# Clean
clean:
	rm -rf test.o
	rm -rf $(EXECUTABLES)
	rm -rf $(LIBRARY_PATHS)
	rm -rf $(OBJECT_FILES)