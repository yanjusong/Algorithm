#include "avl.h"
#include "bst.h"

#include <stdlib.h>

BTree *avl_insert(int value, BTree *t)
{
    int lh, rh;

    if (!t) 
        return getNode(value);

    if (value < t->element) {
        t->left = avl_insert(value, t->left);
        lh = height(t->left);
        rh = height(t->right);

        if (lh - rh == 2) {
            if (value < t->left->element) {
                // left-left rotate
                t = avl_ll_rotate(t);
            } else {
                // left-right rotate
                t = avl_lr_rotate(t);
            }
        }

    } else if (value > t->element) {
        t->right = avl_insert(value, t->right);
        lh = height(t->left);
        rh = height(t->right);

        if (rh - lh == 2) {
            if (value > t->right->element) {
                // right-right rotate
                t = avl_rr_rotate(t);
            } else {
                // right-left rotate
                t = avl_rl_rotate(t);
            }
        }

    } else {
        //duplicate, ignore it
    }
    return t;
}

BTree *avl_ll_rotate(BTree *t)
{
    BTree *ori_left = t->left;
    t->left = ori_left->right;
    ori_left->right = t;
    return ori_left;
}

BTree *avl_rr_rotate(BTree *t)
{
    BTree *ori_right = t->right;
    t->right = ori_right->left;
    ori_right->left = t;
    return ori_right;
}

BTree *avl_lr_rotate(BTree *t)
{
    t->left = avl_rr_rotate(t->left);
    return avl_ll_rotate(t);
}

BTree *avl_rl_rotate(BTree *t)
{
    t->right = avl_ll_rotate(t->right);
    return avl_rr_rotate(t);
}

BTree *avl_delete(int value, BTree *t)
{
    int lh, rh;
    BTree *tmp_cell;

    if (t == NULL) return NULL;

    if (value < t->element) {
        t->left = avl_delete(value, t->left);
        lh = height(t->left);
        rh = height(t->right);

        // 删除左子树的结点，左子树高度可能降低
        if (rh - lh == 2) {
            tmp_cell = t->right;
            lh = height(tmp_cell->left);
            rh = height(tmp_cell->right);

            if (lh > rh)
                t = avl_rl_rotate(t);
            else
                t = avl_rr_rotate(t);
        }
    } else if (value > t->element) {
        t->right = avl_delete(value, t->right);

        lh = height(t->left);
        rh = height(t->right);

        // 删除右子树的结点，右子树高度可能降低
        if (lh - rh == 2) {
            tmp_cell = t->left;
            lh = height(tmp_cell->left);
            rh = height(tmp_cell->right);

            if (rh > lh)
                t = avl_lr_rotate(t);
            else
                t = avl_ll_rotate(t);
        }
    } else if (t->left && t->right) {
        // 如果左子树高于右子树，则取左子树的最大值作为新的根结点
        if (height(t->left) > height(t->right)) {
            tmp_cell = find_max(t->left);
            t->element = tmp_cell->element;
            t->left = avl_delete(tmp_cell->element, t->left);
        } else { // 取右子树的最小值作为新的根结点
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
