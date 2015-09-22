#ifndef __HASH_TABLE
#define __HASH_TABLE

#include <HNode.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

typedef uint32_t (* HashFunc)(const void *, size_t);
typedef int (* EqualityFunc)(void *, void *);
typedef void (* IteratorCallback)(void *, size_t, void *, size_t);

typedef struct HashTable {
	HNode ** table;
	int size;
	int count;
	double max_load;
	double resize_factor;
	EqualityFunc equal;
	HashFunc hash;
	DeleteData deleteKey;
	DeleteData deleteValue;
	pthread_mutex_t * ht_mutex;
} HashTable;

// Designated initializer. Allows for control over max_load percentage, resize_factor, and init_size.
HashTable * hashtable_new(
	int init_size,
	double max_load,
	double resize_factor,
	EqualityFunc equal,
	HashFunc hash,
	DeleteData deleteKey,
	DeleteData deleteValue
);

// Convenience initializer. Uses default values for initial size, max load percentage, and resize factor. 
HashTable * hashtable_new_default(
	EqualityFunc equal,
	DeleteData deleteKey,
	DeleteData deleteValue
);

// frees memory for all keys, values and table its self. 
void hashtable_delete(HashTable * h_table);

// Iterates through all keys and values in the hashtable
void hashtable_iterate(HashTable * h_table, IteratorCallback callback);

// Adds entry to hashtable. If entry already exists for given key, value is replaced with new value. 
void hashtable_put(HashTable * h_table, void * key, size_t key_len, void * value, size_t value_len);

// Gets value for key. If no entry exists, returns NULL
void * hashtable_get(HashTable * h_table, void * key, size_t key_len);

// Removes entry with given key. If no entry exists, does nothing.
void hashtable_remove(HashTable * h_table, void * key, size_t key_len);

// Checks whether an entry with given key exists in hashtable.
int hashtable_key_exists(HashTable * h_table, void * key, size_t key_len);

// Prints hashtable in user readable format. Interprets key as string and prints value as pointer. If you are not using string keys, you should create your own print function using the hashtable_iterate() function. 
void hashtable_print(HashTable * h_table);

#endif
