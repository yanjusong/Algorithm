#include "tree.h"
#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test_avl()
{
    int i, tmp;
    srand((unsigned)time(NULL));

    BTree *root = NULL;
    for (i = 0; i < 50; ++i) {
        tmp = rand() % 50;
        root = avl_insert(tmp, root);
        printf("-------------------------------------------------------\t%d: inserted(%d)\n", i, tmp);
        print_ascii_tree(root);
    }

    for (i = 0; i < 50; ++i) {
        tmp = rand() % 50;
        root = avl_delete(tmp, root);
        printf("-------------------------------------------------------\t%d: deleted(%d)\n", i, tmp);
        print_ascii_tree(root);
    }

    make_empty(root);
}

int main()
{
    test_avl();
    getchar();
    return 0;
}
