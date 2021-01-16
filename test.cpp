#include <stdio.h>

#include "util/llist.hpp"

int main() {
	printf("Hello llist!\n");
	
	int v0 = 1;
	int v1 = 2;
	int v2 = 3;
	
	llist<int*> a;
	a.append(&v0);
	a.append(&v1);
	a.append(&v2);
	
	llist<int*> b(a);
	
	*(a[1]) = 5;
	
	// 5, 6, 2, 1, 8, 7
	
	a.validate();
	
	char* buf = new char[100];
	int writ;
	
	writ = a.debug(buf, 100);
	printf("%s\n%d\n", buf, writ);
	
	writ = b.debug(buf, 100);
	printf("%s\n%d\n", buf, writ);
	
	delete[] buf;
	
	return 0;
}
