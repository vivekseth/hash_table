#include <stdio.h>
#include <stdlib.h>

#include <HNode.h>

// returns pointer to HNode on success. 0 on failure
HNode * hnode_new(
	void * key,
	size_t key_len,
	void * value, 
	size_t value_len,
	DeleteData deleteKey, 
	DeleteData deleteValue
) {
	HNode * hn = malloc(sizeof(HNode));
	if (hn != 0) {
		hn->key = key;
		hn->key_len = key_len;
		hn->value = value;
		hn->value_len = value_len;
		hn->deleteKey = deleteKey;
		hn->deleteValue = deleteValue;
		hn->next = 0;
	}
	return hn;
}

//  returns 1 on success, 0 on failure
//  deletes nodes in list
void hnode_delete_list(HNode * node) {
	HNode * curr = node;
	while (curr) {
		HNode * prev = curr;
		curr = curr->next;		
		hnode_delete_single(prev);
	}
}
void hnode_delete_single(HNode * node) {	
	node->deleteKey(node->key);
	node->deleteValue(node->value);
	node->key = 0;
	node->key_len = 0;
	node->value = 0;
	node->value_len = 0;
	node->deleteKey = 0;
	node->deleteValue = 0;
	node->next = 0;
	
	free(node);
}
