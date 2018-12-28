#include "avl.h"

#include <stdlib.h>

BTree *avl_insert(int value, BTree *t)
{
    if (!t) 
        return getNode(value);

    if (value < t->element) {
        t->left = avl_insert(value, t->left);
        int lh = height(t->left);
        int rh = height(t->right);

        if (lh - rh == 2) {
            if (value < t->left->element) {
                // left-left rotate
                t = ll_rotate(t);
            } else {
                // left-right rotate
                t = lr_rotate(t);
            }
        }

    } else if (value > t->element) {
        t->right = avl_insert(value, t->right);
        int lh = height(t->left);
        int rh = height(t->right);

        if (rh - lh == 2) {
            if (value > t->right->element) {
                // right-right rotate
                t = rr_rotate(t);
            } else {
                // right-left rotate
                t = rl_rotate(t);
            }
        }

    } else {
        //duplicate, ignore it
        return t;
    }
    return t;
}

BTree *ll_rotate(BTree *t)
{
    BTree *ori_left = t->left;
    t->left = ori_left->right;
    ori_left->right = t;
    return ori_left;
}

BTree *rr_rotate(BTree *t)
{
    BTree *ori_right = t->right;
    t->right = ori_right->left;
    ori_right->left = t;
    return ori_right;
}

BTree *lr_rotate(BTree *t)
{
    t->left = rr_rotate(t->left);
    return ll_rotate(t);
}

BTree *rl_rotate(BTree *t)
{
    t->right = ll_rotate(t->right);
    return rr_rotate(t);
}

BTree *avl_delete(int value, BTree *t)
{
    BTree *tmp_cell;

    if (t == NULL) return NULL;

    if (value < t->element) {
        t->left = avl_delete(value, t->left);
    } else if (value > t->element) {
        t->right = avl_delete(value, t->right);
    } else if (t->left && t->right) {
        // 如果左子树高于右子树
        if (height(t->left) > height(t->right)) {
            tmp_cell = find_max(t->left);
            t->element = tmp_cell->element;
            t->left = avl_delete(tmp_cell->element, t->left);
        } else {
            tmp_cell = find_min(t->right);
            t->element = tmp_cell->element;
            t->right = avl_delete(tmp_cell->element, t->right);
        }

    } else {
        tmp_cell = t;
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        free(tmp_cell);
    }

    return t;
}
