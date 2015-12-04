# hash\_table

## Description

This is a thread-safe, generic hashtable implementation in C. 

See `source/test.c` for usage.

## Features

- Custom key and value types
- Thread-safe
- Simple, consistent API
- Compiles to .a library for use in other projects

## Compiling

1. Use `make` to create the static library. (`libhashtable.a`)
2. Use `sudo make install` to install the library and header files to PREFIX.
3. Use the clean rule to remove the new files: `make clean`.

## Usage

You can get the headers from the `hashtable` folder like this:

```C
#include <hashtable/HashTable.h>
#include <hashtable/HNode.h>
```

When compiling your files, add the library to your flags: `-lhashtable`.

## Uninstalling

Use the makefile's uninstall rule: `sudo make uninstall`. It'll remove the
files from PREFIX.
