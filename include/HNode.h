#ifndef __HNode
#define __HNode

#include <stdlib.h>

typedef void (* DeleteData)(void *);

typedef struct HNode_ {
	void * key;
	size_t key_len;
	void * value;
	size_t value_len;
	DeleteData deleteKey;
	DeleteData deleteValue;
	struct HNode_ * next;
} HNode;

// returns pointer to HNode on success. 0 on failure
HNode * hnode_new(
	void * key,
	size_t key_len,
	void * value, 
	size_t value_len,
	DeleteData deleteKey, 
	DeleteData deleteValue
);

void hnode_delete_list(HNode * node);
void hnode_delete_single(HNode * node);

#endif