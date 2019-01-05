#include "b.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i, tmp;
    BTree *root = new_bnode(3);
    bool isbtree;
    int unbcnt = 0;

    //for (i = 5; i >= 1; --i) {
    //    root = b_insert(i, root);
    //    printf("\n\n-----------------------------------------------------------------------------------------\n");
    //    isb = check_btree(root, root->m);
    //    printf("is b tree: %d\n", isb);

    //    print_bnode(root);
    //}

    for (i = 0; i < 100; ++i) {
        tmp = rand() % 100;
        root = b_insert(tmp, root);
        isbtree = check_btree(root, root->m);
        if (!isbtree)
            ++unbcnt;

        printf("-------------------------------------------------------\t%d: inserted(%d), isbtree(%d)\n", i + 1, tmp, isbtree);
        print_bnode(root);
    }
    printf("\n\nB Tree performance: unbtree(%d)\n", unbcnt);

    getchar();
    return 0;
}