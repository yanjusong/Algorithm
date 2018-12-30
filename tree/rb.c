#include "rb.h"

#include <stdlib.h>

static void adjust_color(BTree *t, BTree **p)
{
    BTree *puncle;
    BTree *pgparent;
    t->color = Red;
    if (!t->parent) {
        t->color = Black;
        *p = t;
        return;
    }

    // 父亲结点是黑色，自己结点是红色，无需左任何操作
    if (t->parent->color == Black) {
        return;
    }

    // 叔父结点存在并且红色，父结点也为红色
    puncle = uncle(t);
    pgparent = grandparent(t);
    if (puncle && puncle->color == Red && t->parent->color == Red) {
        puncle->color = Black;
        t->parent->color = Black;
        pgparent->color = Red;
        adjust_color(pgparent, p);
        return;
    }

    // 父亲为红色，叔父结点不存在或叔父结点为黑色
    if (t == t->parent->right && t->parent == pgparent->left) {
        // 该节点和父节点交换(父结点右转)，此时：该节点和父结点和祖父结点在一条线上，父节点位于最底端
        t = rb_rr_rotate(t->parent);
        t = t->left;
    } else if (t == t->parent->left && t->parent == pgparent->right) {
        // 同if里面操作，只不过方向不同
        t = rb_ll_rotate(t->parent);
        t = t->right;
    }

    // 整体操作将红色往祖父结点物理位置的右(左)移动，祖父结点也会变化，注意如果祖父结点是根结点，那么根节点也应变化
    puncle = uncle(t);
    pgparent = grandparent(t);
    t->parent->color = Black;
    pgparent->color = Red;
    if (pgparent == *p)
        *p = t->parent;
    if (t == t->parent->left && t->parent == pgparent->left) {
        t = rb_ll_rotate(pgparent);
    } else {
        t = rb_rr_rotate(pgparent);
    }
    adjust_color(pgparent, p);
 }

BTree *rb_insert(int value, BTree *t)
{
    BTree *tmp_cell = NULL;
    BTree *p = NULL;
    bool isleft = false;

    if (!t) {
        tmp_cell = getNode(value);
        tmp_cell->color = Black;
        return tmp_cell;
    }

    tmp_cell = t;
    while (tmp_cell) {
        p = tmp_cell;
        if (value < tmp_cell->element) {
            tmp_cell = tmp_cell->left;
            isleft = true;
        } else if (value > tmp_cell->element) {
            tmp_cell = tmp_cell->right;
            isleft = false;
        } else {
            //duplicate, ignore it
            return t;
        }
    }
    tmp_cell = getNode(value);
    tmp_cell->color = Red;
    tmp_cell->parent = p;
    if (isleft)
        p->left = tmp_cell;
    else
        p->right = tmp_cell;

    adjust_color(tmp_cell, &t);

    return t;
}

BTree *rb_delete(int value, BTree *t)
{
    return NULL;
}

BTree *rb_ll_rotate(BTree *t)
{
    BTree *ori_left = t->left;
    if (t->parent) {
        if (t == t->parent->left)
            t->parent->left = ori_left;
        else
            t->parent->right = ori_left;
    }
    t->left = ori_left->right;
    if (ori_left->right)
        ori_left->right->parent = t;
    ori_left->parent = t->parent;
    ori_left->right = t;
    t->parent = ori_left;

    return ori_left;
}

BTree *rb_rr_rotate(BTree *t)
{
    BTree *ori_right = t->right;
    if (t->parent) {
        if (t == t->parent->left)
            t->parent->left = ori_right;
        else
            t->parent->right = ori_right;
    }
    t->right = ori_right->left;
    if (ori_right->left)
        ori_right->left->parent = t;
    ori_right->parent = t->parent;
    ori_right->left = t;
    t->parent = ori_right;

    return ori_right;
}

BTree *rb_lr_rotate(BTree *t)
{
    BTree *tmp_cell = rb_rr_rotate(t->left);
    t->left = tmp_cell;
    tmp_cell->parent = t;
    return rb_ll_rotate(t);
}

BTree *rb_rl_rotate(BTree *t)
{
    BTree *tmp_cell = rb_ll_rotate(t->right);
    t->right = tmp_cell;
    tmp_cell->parent = t;
    return rb_rr_rotate(t);
}
