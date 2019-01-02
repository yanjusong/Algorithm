#include "b.h"

#include <stdio.h>

BNode *new_bnode(size_t m)
{
    BNode *new_one = NULL;
    size_t i;
    PBNode *pn = NULL;
    int *pe = NULL;

    new_one = (BNode *)malloc(sizeof(BNode));
    if (new_one) {
        new_one->parent = NULL;
        new_one->m = m;
        new_one->child = (PBNode *)malloc(sizeof(PBNode) * m);
        if (!new_one->child) {
            free(new_one);
        } else {
            pn = new_one->child;
            for (i = 0; i < m; ++i)
                pn[i] = NULL;
        }

        new_one->element = (int *)malloc(sizeof(int) * (m - 1));
        if (!new_one->child) {
            free(new_one->child);
            free(new_one);
        } else {
            pe = new_one->element;
            for (i = 0; i < m - 1; ++i)
                pe[i] = -1;
        }
    }

    return new_one;
}

void delete_bnode(BNode *bn)
{
    if (!bn)
        return;

    if (bn->child)
        free(bn->child);

    if (bn->element)
        free(bn->element);

    free(bn);
}

void print_bnode(BNode *bn)
{
    size_t i;
    int *pe = NULL;
    PBNode *pn = NULL;

    if (!bn)
        return;

    pe = bn->element;
    pn = bn->child;

    if (!pe || !pn)
        return;

    printf("addr: %u (m=%d)\n", (int)bn, (int)bn->m);
    for (i = 0; i < bn->m - 1; ++i) {
        printf("%d ", pe[i]);
    }
    printf("\n");

    for (i = 0; i < bn->m; ++i) {
        printf("%u ", (int)pn[i]);
    }
    printf("\n\n\n");

    for (i = 0; i < bn->m; ++i) {
        if (pn)
            print_bnode(pn[i]);
    }
}
