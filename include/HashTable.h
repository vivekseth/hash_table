#ifndef HASH_TABLE
#define HASH_TABLE

#include <H_Node.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

typedef uint32_t (* HashFunc)(const void *, size_t);
typedef int (* EqualityFunc)(void *, void *);
typedef void (* IteratorCallback)(void *, size_t, void *, size_t);

typedef struct HashTable {
	H_Node ** table;
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

HashTable * new_HashTable(
	int init_size,
	double max_load,
	double resize_factor,
	EqualityFunc equal,
	HashFunc hash,
	DeleteData deleteKey,
	DeleteData deleteValue
);

HashTable * new_HashTable_default(
	EqualityFunc equal,
	DeleteData deleteKey,
	DeleteData deleteValue
);
void delete_HashTable(HashTable * h_table);

void iterate_HashTable(HashTable * h_table, IteratorCallback callback);
void put_HT(HashTable * h_table, void * key, size_t key_len, void * value, size_t value_len);
void * get_HT(HashTable * h_table, void * key, size_t key_len);
void remove_HT(HashTable * h_table, void * key, size_t key_len);
int keyExists_HT(HashTable * h_table, void * key, size_t key_len);
void print_HashTable(HashTable * h_table);


#endif
