#include <HashTable.h>
#include <stdio.h>
//private declarations
void _resize(HashTable * h_table);
uint32_t adler32(const void *buf, size_t buflength);
uint32_t string_hash(const void *buf, size_t buflength) {
	char c = * (char *)buf;
	uint32_t i = 0;
	i = i | c;
	return i;
}
int _replace_HT(
	HashTable * h_table, 
	void * key, size_t key_len, 
	void * value, size_t value_len
);

//implementations
HashTable * new_HashTable(
	int init_size,
	double max_load,
	double resize_factor,
	EqualityFunc equal,
	HashFunc hash,
	DeleteData deleteKey,
	DeleteData deleteValue
) {
	HashTable * ht = calloc(sizeof(HashTable), 1);
	if (ht != 0) {
		ht->table = calloc(sizeof(H_Node *), init_size);
		ht->size = init_size;
		ht->count = 0;
		ht->equal = equal;
		ht->hash = hash;
		ht->max_load = max_load;
		ht->resize_factor = resize_factor;
		ht->deleteKey = deleteKey;
		ht->deleteValue = deleteValue;
		ht->ht_mutex = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(ht->ht_mutex, 0);
	}
	return ht;
}
HashTable * new_HashTable_default(
	EqualityFunc equal,
	DeleteData deleteKey,
	DeleteData deleteValue
) {
	return new_HashTable(
		10, 0.7, 1.5, 
		equal, adler32, 
		deleteKey, deleteValue
	);
}
void delete_HashTable(HashTable * h_table) {
	pthread_mutex_t * ht_mutex = h_table->ht_mutex;
	pthread_mutex_lock(ht_mutex);

	int size = h_table->size;
	H_Node ** table = h_table->table;
	int i;
	for (i = 0; i < size; i++) {
		H_Node * curr = table[i];
		deleteList_H_Node(curr);
	}
	free(table);
	free(h_table);

	pthread_mutex_unlock(ht_mutex);
	pthread_mutex_destroy(ht_mutex);
}


void put_HT(
	HashTable * h_table, 
	void * key, size_t key_len, 
	void * value, size_t value_len) 
{
	//try to replace existing key's value if possible
	pthread_mutex_t * ht_mutex = h_table->ht_mutex;
	pthread_mutex_lock(ht_mutex);
	
	int res = _replace_HT(h_table, key, key_len, value, value_len);
	if (res == 0) {
		//  resize if needed. 
		double load = ((double) h_table->count) / ((double) h_table->size);
		if (load > h_table->max_load) {
			_resize(h_table);
		}

		//code to add key and value in O(1) time.
		uint32_t hash_val = h_table->hash(key, key_len);
		uint32_t index = hash_val % h_table->size;
		H_Node * prev_head = h_table->table[index];
		H_Node * new_head = new_H_Node(
			key, key_len,
			value, value_len,
			h_table->deleteKey,
			h_table->deleteValue
		);

		new_head->next = prev_head;
		h_table->table[index] = new_head;
		h_table->count = h_table->count + 1;
	}
	
	pthread_mutex_unlock(ht_mutex);
	//printf("inserting, {%s => %p}\n", key, value);
	//print_HashTable(h_table);
}
void * get_HT(HashTable * h_table, void * key, size_t key_len) {
	pthread_mutex_t * ht_mutex = h_table->ht_mutex;
	pthread_mutex_lock(ht_mutex);
	
	uint32_t hash_val = h_table->hash(key, key_len);
	uint32_t index = hash_val % h_table->size;
	H_Node * curr = h_table->table[index];
	void * ret_val = 0;
	while (curr) {
		int res = h_table->equal(curr->key, key);
		if (res == 1) {
			ret_val = curr->value;
		}
		curr = curr->next;
	}
	
	pthread_mutex_unlock(ht_mutex);
	return ret_val;
}
int _replace_HT(
	HashTable * h_table, 
	void * key, size_t key_len, 
	void * value, size_t value_len
) {
	uint32_t hash_val = h_table->hash(key, key_len);
	uint32_t index = hash_val % h_table->size;
	H_Node * curr = h_table->table[index];
	while (curr) {
		int res = h_table->equal(curr->key, key);
		if (res == 1) {
			curr->value = value;
			curr->value_len = value_len;
			return 1;
		}
		curr = curr->next;
	}
	return 0;
}
void remove_HT(HashTable * h_table, void * key, size_t key_len) {
	pthread_mutex_t * ht_mutex = h_table->ht_mutex;
	pthread_mutex_lock(ht_mutex);

	uint32_t hash_val = h_table->hash(key, key_len);
	uint32_t index = hash_val % h_table->size;
	H_Node ** table = h_table->table;
	H_Node * curr = table[index];
	H_Node * prev = 0;

	//elem to delete is first in list
	if (h_table->equal(curr->key, key)) {
		table[index] = curr->next;
		deleteSingle_H_Node(curr);
		h_table->count = h_table->count - 1;
		pthread_mutex_unlock(ht_mutex);
		return;
	}

	//if elem to delete is NOT first
	while (curr != 0) {
		if (h_table->equal(curr->key, key)) {
			prev->next = curr->next;
			deleteSingle_H_Node(curr);
			h_table->count = h_table->count - 1;
			return;
		}
		//below code must trigger once
		prev = curr;
		curr = curr->next;
	}

	pthread_mutex_unlock(ht_mutex);
}



void _resize(HashTable * h_table) {
	int size = h_table->size;
	int new_size = (int)(h_table->size * h_table->resize_factor);
	H_Node ** new_table = calloc(sizeof(H_Node *), new_size);
	H_Node ** old_table = h_table->table;

	h_table->table = new_table;
	h_table->size = new_size;
	h_table->count = 0;

	int i = 0;
	for (i = 0; i < size; i++) {
		H_Node * curr = old_table[i];
		while (curr != 0) {
			H_Node * prev = curr;
			curr = curr->next;

			put_HT(h_table, prev->key, prev->key_len, prev->value, prev->value_len);
			//free the memory for only the struct
			//note, this does NOT free the key or the value
			free(prev);
		}
	}
	//free the memory for the old array
	free(old_table);
}
void iterate_HashTable(HashTable * h_table, IteratorCallback callback) {
	pthread_mutex_t * ht_mutex = h_table->ht_mutex;
	pthread_mutex_lock(ht_mutex);

	int size = h_table->size;
	H_Node ** table = h_table->table;
	int i = 0;
	for (i = 0; i < size; i++) {
		H_Node * curr = table[i];
		while (curr != 0) {
			callback(curr->key, curr->key_len, curr->value, curr->value_len);
			curr = curr->next;
		}
	}

	pthread_mutex_unlock(ht_mutex);
}

void print_HashTable(HashTable * h_table) {
	int size = h_table->size;
	H_Node ** table = h_table->table;
	int i = 0;
	for (i = 0; i < size; i++) {
		H_Node * curr = table[i];
		while (curr != 0) {
			// callback(curr->key, curr->key_len, curr->value, curr->value_len);
			printf("'%s' => %p,\n", (char *)curr->key, curr->value);
			curr = curr->next;
		}
	}
}

/*
adler32 code taken from Stack Overflow post

http://stackoverflow.com/a/14409947/3158248

Please note, that the rest of the code is my own.
*/
uint32_t adler32(const void *buf, size_t buflength) {
     const uint8_t *buffer = (const uint8_t*)buf;

     uint32_t s1 = 1;
     uint32_t s2 = 0;
     
     size_t n;
     
     for (n = 0; n < buflength; n++) {
        s1 = (s1 + buffer[n]) % 65521;
        s2 = (s2 + s1) % 65521;
     }     
     return (s2 << 16) | s1;
}


