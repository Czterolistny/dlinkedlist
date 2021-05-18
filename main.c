#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dlinklist.h"

typedef void (*print_t)(void*);
void print(void * x)
{
	printf("%d ", *(int*) x);
}

int main(int argc, char **argv)
{
	DoubleLinkList *dl = (DoubleLinkList *) malloc(sizeof(DoubleLinkList));
	init(dl);
	
	push_end(dl, 1);
	push_end(dl, 2);

	push_beg(dl, 30);
	push_beg(dl, 40);
	
	print_t p = &print;
	print_all(dl, p); printf("\n");
	
	insert_item(dl, 2, 100);
	insert_item(dl, 2, 101);
	insert_item(dl, 2, 102);
	print_all(dl, p); printf("\n");
	
	remove_item(dl, find_item(dl, 0, 100));
	remove_item(dl, find_item(dl, 0, 101));
	remove_item(dl, find_item(dl, 0, 102));
	print_all(dl, p); printf("\n");
	
	free_all(dl);

return 0;
}