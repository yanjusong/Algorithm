#ifndef BAYER_H_20190103
#define BAYER_H_20190103

#include "tree.h"
#include <stdlib.h>

#define MAX_STR_SIZE 5000

typedef struct BTree BTree;
typedef struct BTree* PBTree;

struct BTree
{
    size_t m;
    size_t keycnt;
    PBTree *child;
    BTree *parent;
    int *element;
};

BTree *new_bnode(size_t m);

void delete_bnode(BTree *t);

BTree *b_insert(int value, BTree *t);

void print_bnode(BTree *bn);

bool check_btree(BTree *t, int m);

#endif // !BAYER_H_20190103
