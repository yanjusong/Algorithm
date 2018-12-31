#include "rb.h"
#include "bst.h"

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

static void adjust_color2(BTree *p)
{
    BTree *parent;
    BTree *sibling;
    BTree *tmp_cell;
    BTree *lsib, *rsib;

    parent = p;
    if (!parent) {
        return;
    }

    sibling = p->right;
    if (!sibling)
        adjust_color2(parent->parent);

    // 兄弟结点红色
    if (sibling->color == Red) {
        parent->color = Red;
        tmp_cell = rb_rr_rotate(parent);
        adjust_color2(tmp_cell->left);
        return;
    }

    lsib = sibling->left;
    rsib = sibling->right;
    // 兄弟结点为黑色，且两个孩子都是黑色
    if ((!lsib || lsib->color == Black) && (!rsib || rsib->color == Black)) {
        sibling->color = Black;
        adjust_color2(parent->parent);
        return;
    }

    // 兄弟结点为黑色，兄弟结点两个孩子左红右黑
    if ((lsib && lsib->color == Red) && (!rsib || rsib->color == Black)) {
        lsib->color = Black;
        sibling->color = Red;
        tmp_cell = rb_ll_rotate(sibling);
        adjust_color2(parent);
        return;
    }

    // 兄弟结点为黑色，兄弟结点两个孩子右红
    sibling->color = parent->color;
    parent->color = Black;
    if (sibling->right)
        sibling->right->color = Black;

    tmp_cell = rb_rr_rotate(parent);

    if (tmp_cell->parent)
        adjust_color2(tmp_cell->parent->parent);
}

BTree *find_delete_node(int value, BTree *t, BTree **dnode)
{
    BTree *tmp_cell;

    if (t == NULL) return NULL;

    if (value < t->element) {
        tmp_cell = find_delete_node(value, t->left, dnode);
        if (tmp_cell)
            tmp_cell->parent = t->left;
        t->left = tmp_cell;
    } else if (value > t->element) {
        tmp_cell = find_delete_node(value, t->right, dnode);
        if (tmp_cell)
            tmp_cell->parent = t->right;
        t->right = tmp_cell;
    } else if (t->left && t->right) {
        tmp_cell = find_min(t->right);
        t->element = tmp_cell->element;
        tmp_cell = find_delete_node(t->element, t->right, dnode);
        if (tmp_cell)
            tmp_cell->parent = t->right;
        t->right = tmp_cell;
    } else {
        *dnode = t;
//        tmp_cell = t;
//        if (t->left == NULL)
//            t = t->right;
//        else if (t->right == NULL)
//            t = t->left;
//        free(tmp_cell);
    }

    return t;
}

BTree *rb_delete(int value, BTree *t)
{
    return NULL;
    BTree *tmp_cell;
    BTree *sibling;
    BTree *p;
    BTree *deleted_node = NULL;

    find_delete_node(value, t, &deleted_node);

    // 没找到欲删除的结点
    if (!deleted_node)
        return t;

    // 父节点
    p = deleted_node->parent;

    // 如果父节点为空,find_delete_node没有找到右子树最小的结点
    // 那么就删他自己,有红黑树的性质可知此时左子树只有一个结点且为红色
    if (!p) {
        t = deleted_node->left;
        t->color = Black;
        t->parent = NULL;
        free(deleted_node);
        return t;
    }

    // 被删除结点只有一个非空结点
    if (deleted_node->left || deleted_node->right) {
        tmp_cell = (deleted_node->left ? deleted_node->left : deleted_node->right);
        tmp_cell->color = Black;
        tmp_cell->parent = t->parent;

        if (deleted_node == p->left)
            p->left = tmp_cell;
        else
            p->right = tmp_cell;

        free(deleted_node);
        return t;
    }

    // 被删除的是红色结点且有两个NULL结点
    if (deleted_node->color == Red) {
        if (p->left == deleted_node)
            p->left = NULL;
        else
            p->right = NULL;

        free(deleted_node);
        return t;
    }

    // 被删除结点为黑色且有两个NULL结点
    sibling = (p->left == deleted_node ? p->right : p->left);
    if (p->left == deleted_node)
        p->left = NULL;
    else
        p->right = NULL;
    adjust_color2(p);
    free(deleted_node);
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
