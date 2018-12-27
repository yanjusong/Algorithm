#include "tree.h"
#include "bst.h"

#include <stdio.h>
#include <stdlib.h>

void test()
{
    int i, tmp;
    srand((unsigned)time(NULL));

    Tree *root = NULL;
    for (i = 0; i < 50; ++i) {
        tmp = rand() % 1000;
        root = insert(tmp, root);
    }
    print_ascii_tree(root);
}

int main()
{
    test();
    getchar();
    return 0;
}
