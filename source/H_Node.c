#include <H_Node.h>
#include <stdio.h>

// returns pointer to h_Node on success. 0 on failure
H_Node * new_H_Node(
	void * key,
	size_t key_len,
	void * value, 
	size_t value_len,
	DeleteData deleteKey, 
	DeleteData deleteValue
) {
	H_Node * hn = malloc(sizeof(H_Node));
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
void deleteList_H_Node(H_Node * node) {
	H_Node * curr = node;
	while (curr) {
		H_Node * prev = curr;
		curr = curr->next;		
		deleteSingle_H_Node(prev);
	}
}
void deleteSingle_H_Node(H_Node * node) {	
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