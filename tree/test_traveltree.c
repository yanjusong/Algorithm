#include "tree.h"
#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_node(BTree *t, void *udata)
{
    UNUSED(udata);

    if (t)
        printf("%d ", t->element);
}

void test_preorder_travel(BTree *t)
{
    printf("\n-------- 先序遍历 --------\n");

    printf("递归遍历:\n");
    preorder_travel_recur(t, print_node, NULL);
    printf("\n");

    printf("用栈辅助:\n");
    preorder_travel_stack(t, print_node, NULL);
    printf("\n");
}

void test_inorder_travel(BTree *t)
{
    printf("\n-------- 中序遍历 --------\n");

    printf("递归遍历:\n");
    inorder_travel_recur(t, print_node, NULL);
    printf("\n");

    printf("用栈辅助:\n");
    inorder_travel_stack(t, print_node, NULL);
    printf("\n");
}

void test_postorder_travel(BTree *t)
{
    printf("\n-------- 后序遍历 --------\n");

    printf("递归遍历:\n");
    postorder_travel_recur(t, print_node, NULL);
    printf("\n");

    printf("用栈辅助:\n");
    postorder_travel_stack(t, print_node, NULL);
    printf("\n");
}

void test_levelorder_travel(BTree *t)
{
    printf("\n-------- 层次遍历 --------\n");

    printf("队列辅助:\n");
    levelorder_trabel(t, print_node, NULL);
    printf("\n");
}

void test()
{
    int i, tmp;
    srand((unsigned)time(NULL));

    BTree *root = NULL;
    for (i = 0; i < 10; ++i) {
        tmp = rand() % 100;
        root = bst_insert(tmp, root);
    }
    print_ascii_tree(root);
    
    // test start.
    test_preorder_travel(root);
    test_inorder_travel(root);
    test_postorder_travel(root);
    test_levelorder_travel(root);

    make_empty(root);
}

int main()
{
    test();
    getchar();
    return 0;
}
