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

    BSTree *root = NULL;

    for (i = 0; i < 50; ++i) {
        tmp = rand() % 50;
        root = rb_insert(tmp, root);
        isrb = check_rb_tree(root);
        if (isrb == false)
            ++unrb;

        printf("-------------------------------------------------------\t%d: inserted(%d), rb(%d)\n", i + 1, tmp, isrb);
        print_ascii_tree(root);
    }

    for (i = 0; i < 200; ++i) {
        tmp = rand() % 50;
        root = rb_delete(tmp, root);

        isrb = check_rb_tree(root);
        if (isrb == false)
            ++unrb;

        printf("-------------------------------------------------------\t%d: deleted(%d), rb(%d)\n", i + 1, tmp, isrb);
        print_ascii_tree(root);
    }

    make_empty(root);
    printf("\n\nRB Tree performance: unrb(%d)\n", unrb);
}

int main()
{
    test_rb();
    getchar();
    return 0;
}
