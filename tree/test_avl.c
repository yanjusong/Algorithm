#include "tree.h"
#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test_avl()
{
    int i, tmp;
    bool issorted;
    bool isbalanced;
    int unsorted = 0;
    int unbalanced = 0;

    srand((unsigned)time(NULL));

    BTree *root = NULL;
    for (i = 0; i < 50; ++i) {
        tmp = rand() % 50;
        root = avl_insert(tmp, root);
        issorted = check_sorted(root);
        isbalanced = check_balanced(root);
        if (issorted == false)
            ++unsorted;
        if (isbalanced == false)
            ++unbalanced;

        printf("-------------------------------------------------------\t%d: inserted(%d), sorted(%d), balanced(%d)\n", i + 1, tmp, issorted, isbalanced);
        print_ascii_tree(root);
    }

    for (i = 0; i < 50; ++i) {
        tmp = rand() % 50;
        root = avl_delete(tmp, root);
        issorted = check_sorted(root);
        isbalanced = check_balanced(root);
        if (issorted == false)
            ++unsorted;
        if (isbalanced == false)
            ++unbalanced;

        printf("-------------------------------------------------------\t%d: deleted(%d), sorted(%d), balanced(%d)\n", i + 1, tmp, issorted, isbalanced);
        print_ascii_tree(root);
    }

    make_empty(root);
    printf("\n\nAVL Tree performance: unsorted(%d), unbalanced(%d)\n", unsorted, unbalanced);
}

int main()
{
    test_avl();
    getchar();
    return 0;
}
