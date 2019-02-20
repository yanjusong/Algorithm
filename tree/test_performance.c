#include <stdio.h>
#include <stdlib.h>
#include <time.h>   

#include "tree.h"
#include "bst.h"
#include "avl.h"
#include "rb.h"

#define INSTERT_NUM 10000000
#define DELETE_NUM  10000000
#define SEARCH_NUM  10000000

int *g_insert_nums;
int *g_delete_nums;
int *g_search_nums;

typedef BSTree *(*TestFunc)(int, BSTree *);

void test_insert_and_delete_and_search(TestFunc inserted_func, TestFunc deleted_func, const char *desc)
{
    long begintime, endtime;
    int insert_cost, delete_cost, search_cost;
    int i;
    BSTree *pfound;
    BSTree *root = NULL;

    // 插入
    begintime = clock();
    for (i = 0; i < INSTERT_NUM; ++i) {
        root = inserted_func(g_insert_nums[i], root);
    }
    endtime = clock();
    insert_cost = endtime - begintime;

    // 查找
    begintime = clock();
    for (i = 0; i < SEARCH_NUM; ++i) {
        pfound = find(g_search_nums[i], root);
    }
    
    endtime = clock();
    search_cost = endtime - begintime;

    // 删除
    begintime = clock();
    for (i = 0; i < DELETE_NUM; ++i) {
        root = deleted_func(g_delete_nums[i], root);
    }
    endtime = clock();
    delete_cost = endtime - begintime;

    make_empty(root);

    printf("%s: inserted(%dms), deleted(%dms), search(%dms)\n", desc, insert_cost, delete_cost, search_cost);
}

int test()
{
    int i = 0;
    srand((unsigned)time(NULL));

    g_insert_nums = (int *)malloc(sizeof(int) * INSTERT_NUM);
    if (!g_insert_nums)
        return -1;

    g_delete_nums = (int *)malloc(sizeof(int) * DELETE_NUM);
    if (!g_delete_nums)
        return -1;

    g_search_nums = (int *)malloc(sizeof(int) * DELETE_NUM);
    if (!g_search_nums)
        return -1;

    for (i = 0; i < INSTERT_NUM; ++i)
        g_insert_nums[i] = rand() % 5000000;

    for (i = 0; i < DELETE_NUM; ++i)
        g_delete_nums[i] = rand() % 5000000;

    for (i = 0; i < SEARCH_NUM; ++i)
        g_search_nums[i] = g_insert_nums[i];

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

    printf("插入数据: %d, 查找数据: %d, 删除数据: %d\n", INSTERT_NUM, SEARCH_NUM, DELETE_NUM);
    test_insert_and_delete_and_search(bst_insert, bst_delete, "Binary Search Tree");
    test_insert_and_delete_and_search(avl_insert, avl_delete, "AVL Tree");
    test_insert_and_delete_and_search(rb_insert, rb_delete, "Red-Black Tree");

    return 0;
}

int main()
{
    if (test() != 0) {
        printf("malloc failed.\n");
    }

    if (g_insert_nums)
        free(g_insert_nums);

    if (g_delete_nums)
        free(g_delete_nums);

    if (g_search_nums)
        free(g_search_nums);

    getchar();
    return 0;
}
