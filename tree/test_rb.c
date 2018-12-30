#include "tree.h"
#include "rb.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test_rb()
{
    int i, tmp;
    bool isrb;
    int unrb = 0;

    srand((unsigned)time(NULL));

    BTree *root = NULL;
    for (i = 0; i < 100; ++i) {
        tmp = rand() % 100;
        root = rb_insert(tmp, root);
        isrb = check_rb_tree(root);
        if (isrb == false)
            ++unrb;

        printf("-------------------------------------------------------\t%d: inserted(%d), rb(%d)\n", i + 1, tmp, isrb);
        print_ascii_tree(root);
    }
    printf("\n\nRB Tree performance: unrb(%d)\n", unrb);

    //for (i = 0; i < 50; ++i) {
    //    tmp = rand() % 50;
    //    root = avl_delete(tmp, root);
    //    issorted = check_sorted(root);
    //    isbalanced = check_balanced(root);
    //    if (issorted == false)
    //        ++unsorted;
    //    if (isbalanced == false)
    //        ++unbalanced;

    //    printf("-------------------------------------------------------\t%d: deleted(%d), sorted(%d), balanced(%d)\n", i, tmp, issorted, isbalanced);
    //    print_ascii_tree(root);
    //}

    make_empty(root);
}

int main()
{
    test_rb();
    getchar();
    return 0;
}
