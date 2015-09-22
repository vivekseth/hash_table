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

void do_nothing(void * a) {
	return;
}

int main() {
	HashTable * h_table = new_HashTable_default(
		equal_string, 
		do_nothing, 
		do_nothing
	);

	put_HT(h_table, "abc", 4, "def", 4);
	put_HT(h_table, "ghi", 4, "jkl", 4);
	put_HT(h_table, "mno", 4, "pqr", 4);
	put_HT(h_table, "stu", 4, "vwx", 4);

	put_HT(h_table, "def", 4, "abc", 4);
	put_HT(h_table, "jkl", 4, "ghi", 4);
	put_HT(h_table, "pqr", 4, "mno", 4);
	put_HT(h_table, "vwx", 4, "stu", 4);

	printf("%s\n", (char *) get_HT(h_table, "abc", 4));
	printf("%s\n", (char *) get_HT(h_table, "ghi", 4));
	printf("%s\n", (char *) get_HT(h_table, "mno", 4));
	printf("%s\n", (char *) get_HT(h_table, "stu", 4));
	
	printf("%s\n", (char *) get_HT(h_table, "def", 4));
	printf("%s\n", (char *) get_HT(h_table, "jkl", 4));
	printf("%s\n", (char *) get_HT(h_table, "pqr", 4));
	printf("%s\n", (char *) get_HT(h_table, "vwx", 4));

	delete_HashTable(h_table);
	return 0;
}