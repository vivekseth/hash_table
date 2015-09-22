#ifndef HASH_TABLE
#define HASH_TABLE

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

HashTable * hashtable_new(
	int init_size,
	double max_load,
	double resize_factor,
	EqualityFunc equal,
	HashFunc hash,
	DeleteData deleteKey,
	DeleteData deleteValue
);

HashTable * hashtable_new_default(
	EqualityFunc equal,
	DeleteData deleteKey,
	DeleteData deleteValue
);
void hashtable_delete(HashTable * h_table);

void hashtable_iterate(HashTable * h_table, IteratorCallback callback);
void hashtable_put(HashTable * h_table, void * key, size_t key_len, void * value, size_t value_len);
void * hashtable_get(HashTable * h_table, void * key, size_t key_len);
void hashtable_remove(HashTable * h_table, void * key, size_t key_len);
int hashtable_key_exists(HashTable * h_table, void * key, size_t key_len);
void hashtable_print(HashTable * h_table);


#endif
