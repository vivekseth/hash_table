#include <string.h>
#include <stdio.h>
#include <HashTable.h>

int equal_string(void * a, void * b) {
	char * str1 = (char *) a;
	char * str2 = (char *) b;
	int res = strcmp(str1, str2);
	if (res == 0) {return 1;}
	else {return 0;}
}

// useful for non-heap allocated data
void destroy_nop(void * a) {
	return;
}

int main() {
	HashTable * h_table = hashtable_new_default(
		equal_string, 
		destroy_nop, 
		destroy_nop
	);

	hashtable_put(h_table, "abc", 4, "def", 4);
	hashtable_put(h_table, "ghi", 4, "jkl", 4);
	hashtable_put(h_table, "mno", 4, "pqr", 4);
	hashtable_put(h_table, "stu", 4, "vwx", 4);

	hashtable_put(h_table, "def", 4, "abc", 4);
	hashtable_put(h_table, "jkl", 4, "ghi", 4);
	hashtable_put(h_table, "pqr", 4, "mno", 4);
	hashtable_put(h_table, "vwx", 4, "stu", 4);

	printf("%s\n", (char *) hashtable_get(h_table, "abc", 4));
	printf("%s\n", (char *) hashtable_get(h_table, "ghi", 4));
	printf("%s\n", (char *) hashtable_get(h_table, "mno", 4));
	printf("%s\n", (char *) hashtable_get(h_table, "stu", 4));
	
	printf("%s\n", (char *) hashtable_get(h_table, "def", 4));
	printf("%s\n", (char *) hashtable_get(h_table, "jkl", 4));
	printf("%s\n", (char *) hashtable_get(h_table, "pqr", 4));
	printf("%s\n", (char *) hashtable_get(h_table, "vwx", 4));

	hashtable_delete(h_table);
	return 0;
}