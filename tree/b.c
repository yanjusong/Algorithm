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
    new_one->keycnt = 0;

    if (m > 2) {
        new_one->child = (PBTree *)malloc(sizeof(PBTree) * (m + 1));
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
            for (i = 0; i < m + 1; ++i)
                pn[i] = NULL;

            pe = new_one->element;
            for (i = 0; i < m; ++i)
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

void print_bnode(BTree *t)
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

    if (!t)
        return;

    pe = t->element;
    pn = t->child;

    if (!pe || !pn)
        return;

    childstr = (char *)(malloc(MAX_STR_SIZE));
    valuestr = (char *)(malloc(MAX_STR_SIZE));
    addrstr  = (char *)(malloc(MAX_STR_SIZE));

    dq = new_deque();
    push_back(dq, t, BTree*);
    while (!is_empty(dq)) {
        memset(addrstr, 0, MAX_STR_SIZE);
        memset(valuestr, 0, MAX_STR_SIZE);
        memset(childstr, 0, MAX_STR_SIZE);
        
        dqlen = size(dq);
        for (i = 0; i < dqlen; ++i) {
            bnode = front(dq, BTree *);
            pe = bnode->element;
            pn = bnode->child;

            sprintf(tmpstr, "self:0x%.8x, parent:0x%.8x  ", bnode, bnode->parent);
            strcat(addrstr, tmpstr);
            for (j = 0; j < bnode->m - 2; ++j) {
                strcat(addrstr, "        ");
            }

            strcat(valuestr, "     ");
            for (j = 0; j < bnode->m; ++j) {
                sprintf(tmpstr, "%10d", pe[j]);
                strcat(valuestr, tmpstr);
                strcat(valuestr, " ");

                sprintf(tmpstr, "0x%.8x", pn[j]);
                strcat(childstr, tmpstr);
                strcat(childstr, " ");
                if (pn[j])
                    push_back(dq, pn[j], BTree*);
            }
            sprintf(tmpstr, "0x%.8x", pn[bnode->m]);
            strcat(childstr, tmpstr);
            strcat(childstr, " ");
            if (pn[bnode->m])
                push_back(dq, pn[bnode->m], BTree*);

            strcat(valuestr, "      ");

            strcat(addrstr,  "| ");
            strcat(valuestr, "| ");
            strcat(childstr, "| ");

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

void insert(int value, BTree *t, BTree *left, BTree *right, BTree **root)
{
    int *pe = NULL;
    PBTree *pn = NULL;
    BTree *right_node = NULL;
    int pos;
    int i, j, ori_keycnt;;

    if (!t)
        return NULL;

    pe = t->element;
    pn = t->child;
    ori_keycnt = t->keycnt;

    for (i = 0; i < ori_keycnt; ++i) {
        if (value == pe[i]) {
            return;
        } else if (value < pe[i]) {
            break;
        }
    }
    pos = i;

    for (i = ori_keycnt - 1; i >= pos; --i) {
        pe[i + 1] = pe[i];
    }
    for (i = ori_keycnt; i >= pos + 1; --i) {
        pn[i + 1] = pn[i];
    }

    pn[pos] = left;
    pn[pos + 1] = right;
    pe[pos] = value;
    ++t->keycnt;

    ori_keycnt = t->keycnt;
    // 分裂，t结点分裂成t和右结点
    if (ori_keycnt == t->m) {
        right_node = new_bnode(t->m);
        right_node->parent = t->parent;
        
        pos = t->m / 2;
        for (i = pos + 1, j = 0; i < ori_keycnt; ++i, ++j) {
            (right_node->element)[j] = pe[i];
            pe[i] = -1;
            ++right_node->keycnt;
            --t->keycnt;
        }
        for (i = pos + 1, j = 0; i < ori_keycnt + 1; ++i, ++j) {
            (right_node->child)[j] = pn[i];
            // 分裂后的右结点原来的父亲是t，现在改成right_node
            if ((right_node->child)[j]) {
                (right_node->child)[j]->parent = right_node;
            }
            pn[i] = NULL;
        }

        value = pe[pos];
        pe[pos] = -1;
        --t->keycnt;

        if (t->parent == NULL) {
            BTree *p = new_bnode(t->m);
            t->parent = p;
            right_node->parent = t->parent;
            *root = t->parent;
        }

        // 分裂后插入父结点
        insert(value, t->parent, t, right_node, root);
    }
}

void find_insert_node(int value, BTree *t, BTree **root)
{
    int *pe = NULL;
    PBTree *pn = NULL;
    size_t pos;
    int i;
    if (!t)
        return NULL;

    pe = t->element;
    pn = t->child;

    for (i = 0; i < t->keycnt; ++i) {
        if (value == pe[i]) {
            return;
        } else if (value < pe[i]) {
            break;
        }
    }
    pos = i;

    if (pn[pos])
        find_insert_node(value, pn[pos], root);
    else
        insert(value, t, NULL, NULL, root);
}

BTree *b_insert(int value, BTree *t)
{
    find_insert_node(value, t, &t);
    return t;
}

bool check_bnode(BTree *t, int m)
{
    bool ret = true;
    PBTree *ppn = NULL;
    int *pe = NULL;
    BTree *p;
    int i;

    if (!t)
        return false;

    if (t->keycnt >= m || t->keycnt <= 0)
        return false;

    pe = t->element;
    // 检查是否排序
    for (i = 0; i < t->keycnt - 1; ++i)
        if (pe[i] >= pe[i + 1])
            return false;
    

    // 检查父节点是否的孩子结点是否符合逻辑
    p = t->parent;
    if (p) {
        ppn = p->child;
        for (i = 0; i < p->keycnt + 1 && ret; ++i) {
            ret &= (ppn[i] != NULL);
        }

        for (i = p->keycnt + 1; i < p->m + 1 && ret; ++i) {
            ret &= (ppn[i] == NULL);
        }
    }

    return ret;
}

bool check_btree(BTree *t, int m)
{
    bool ret = true;
    PBTree *pn = NULL;
    int i;

    if (!t)
        return true;

    ret &= check_bnode(t, m);
    pn = t->child;
    for (i = 0; i < m + 1 && ret; ++i) {
        ret &= check_btree(pn[i], m);
    }

    return ret;
}
