#ifndef BAYER_H_20190103
#define BAYER_H_20190103

#include <stdlib.h>

typedef struct BNode BNode;
typedef struct BNode* PBNode;

struct BNode
{
    size_t m;
    PBNode *child;
    BNode *parent;
    int *element;
};

BNode *new_bnode(size_t m);

void delete_bnode(BNode *bn);

void print_bnode(BNode *bn);

#endif // !BAYER_H_20190103
