#include "tree.h"
#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test_print()
{
    int i, tmp;
    srand((unsigned)time(NULL));

    BTree *root = NULL;
    for (i = 0; i < 50; ++i) {
        tmp = rand() % 1000;
        root = bst_insert(tmp, root);
    }
    print_ascii_tree(root);
	
	make_empty(root);
}

int main()
{
    test_print();
    getchar();
    return 0;
}
