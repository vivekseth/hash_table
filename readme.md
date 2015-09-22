# Read Me

## Description

This is a thread-safe, generic hashtable implementation in C. 

See `test.c` for usage. 

## Features

- Custom key and value types
- Thread-safe
- Simple, consistent API
- Compiles to .a library for use in other project

## Integratation

1. Use `make hash_table.a` to compile project to library
2. Add `./include/` to your header search path
3. When compiling project ling against `./hash_table.a`