#include "b.h"
#include "deque.h"

#include <stdio.h>
#include <string.h>

BTree *new_bnode(size_t m)
{
    BTree *new_one = NULL;
    size_t i;
    PBTree *pn = NULL;
    int *pe = NULL;

    new_one = (BTree *)malloc(sizeof(BTree));
    if (!new_one)
        return NULL;

    new_one->parent = NULL;
    new_one->child = NULL;
    new_one->element = NULL;
    new_one->m = m;
    new_one->childcnt = 0;

    if (m > 2) {
        new_one->child = (PBTree *)malloc(sizeof(PBTree) * m);
        new_one->element = (int *)malloc(sizeof(int) * m);

        if (!new_one->child || !new_one->element) {
            free(new_one);
            new_one = NULL;
            if (new_one->child)
                free(new_one->child);
            if (new_one->element)
                free(new_one->element);
        } else {
            pn = new_one->child;
            for (i = 0; i < m; ++i)
                pn[i] = NULL;

            pe = new_one->element;
            for (i = 0; i < m - 1; ++i)
                pe[i] = -1;
        }
    }

    return new_one;
}

void delete_bnode(BTree *bn)
{
    if (!bn)
        return;

    if (bn->child)
        free(bn->child);

    if (bn->element)
        free(bn->element);

    free(bn);
}

void print_bnode(BTree *bn)
{
    size_t i, j;
    int *pe = NULL;
    PBTree *pn = NULL;
    Deque *dq = NULL;
    BTree *bnode = NULL;
    size_t dqlen;
    char *childstr = NULL;
    char *valuestr = NULL;
    char *addrstr = NULL;
    char tmpstr[64];

    if (!bn)
        return;

    pe = bn->element;
    pn = bn->child;

    if (!pe || !pn)
        return;

    childstr = (char *)(malloc(MAX_STR_SIZE));
    valuestr = (char *)(malloc(MAX_STR_SIZE));
    addrstr  = (char *)(malloc(MAX_STR_SIZE));

    dq = new_deque();
    push_back(dq, bn, BTree*);
    while (!is_empty(dq)) {
        memset(addrstr, 0, MAX_STR_SIZE);
        memset(valuestr, 0, MAX_STR_SIZE);
        memset(childstr, 0, MAX_STR_SIZE);
        
        dqlen = size(dq);
        for (i = 0; i < dqlen; ++i) {
            bnode = back(dq, BTree *);
            pe = bnode->element;
            pn = bnode->child;

            sprintf(tmpstr, "self:0x%8x, parent:0x%8x  ", bnode, bnode->parent);
            strcat(addrstr, tmpstr);
            for (j = 0; j < bnode->m - 2; ++j) {
                strcat(addrstr, "          ");
            }

            strcat(valuestr, "     ");
            for (j = 0; j < bnode->m - 1; ++j) {
                sprintf(tmpstr, "%10d", pe[j]);
                strcat(valuestr, tmpstr);
                strcat(valuestr, " ");

                sprintf(tmpstr, "0x%8x", pn[j]);
                strcat(childstr, tmpstr);
                strcat(childstr, " ");
                push_back(dq, pn[j], BTree*);
            }
            sprintf(tmpstr, "0x%8x", pn[bnode->m - 1]);
            strcat(childstr, tmpstr);
            strcat(childstr, " ");
            strcat(valuestr, "     ");

            strcat(addrstr,  "| ");
            strcat(valuestr, "| ");
            strcat(childstr, "| ");

            push_back(dq, pn[bnode->m - 1], BTree*);
            pop_front(dq);
        }
        printf("%s\n", addrstr);
        printf("%s\n", valuestr);
        printf("%s\n", childstr);
        printf("\n\n");
    }

    free(addrstr);
    free(valuestr);
    free(childstr);
    delete_deque(dq);
}

void _b_insert(int value, BTree *t, BTree **root)
{
    size_t left, right, mid;
    int *pe = NULL;
    PBTree *pn = NULL;
    BTree *ct;
    size_t ict;
    int i;
    if (!t)
        return NULL;

    pe = t->element;
    pn = t->child;

    if (t->childcnt > 0) {
        for (i = 0; i < t->childcnt; ++i) {
            if (value = pe[i]) {
                return;
            } else if (value < pe[i]) {
                ict = i;
                break;
            }
        }
        ict = i;

        _b_insert(value, pn[ict], root);
    } else {

    }

    // TODO: 二分法
    //if (t->childcnt > 0) {
    //    left = 0;
    //    right = t->childcnt - 1;
    //    while (left <= right) {
    //        mid = (left + right) >> 1;
    //        if (value < pe[mid]) {
    //            right = mid - 1;
    //        } else if (value > pe[mid]) {
    //            left = mid + 1;
    //        } else {
    //            return t;
    //        }
    //    }

    //    // mid
    //    ict = mid;
    //    if (value > pe[mid]) {
    //        ++ict;
    //    }

    //    // TODO:
    //}
}

BTree *b_insert(int value, BTree *t)
{
    _b_insert(value, t, &t);
    return t;
}