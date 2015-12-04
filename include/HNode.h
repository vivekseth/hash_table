#ifndef __HNode
#define __HNode

typedef void (* DeleteData)(void *);

// This struct and the functions declared in this file are not to be used by clients of HashTable. 
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
