#ifndef H_NODE
#define H_NODE

#include <stdlib.h>

typedef void (* DeleteData)(void *);

typedef struct H_Node {
	void * key;
	size_t key_len;
	void * value;
	size_t value_len;
	DeleteData deleteKey;
	DeleteData deleteValue;
	struct H_Node * next;
} H_Node;

// returns pointer to h_Node on success. 0 on failure
H_Node * new_H_Node(
	void * key,
	size_t key_len,
	void * value, 
	size_t value_len,
	DeleteData deleteKey, 
	DeleteData deleteValue
);

void deleteList_H_Node(H_Node * node);
void deleteSingle_H_Node(H_Node * node);

#endif