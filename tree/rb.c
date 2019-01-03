#include "rb.h"
#include "bst.h"

#include <stdlib.h>

static BSTree *rb_ll_rotate(BSTree *t);
static BSTree *rb_rr_rotate(BSTree *t);
static BSTree *rb_lr_rotate(BSTree *t);
static BSTree *rb_rl_rotate(BSTree *t);

static void adjust_color_inserted(BSTree *t, BSTree **p)
{
    BSTree *puncle;
    BSTree *pgparent;
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
        adjust_color_inserted(pgparent, p);
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
    adjust_color_inserted(pgparent, p);
 }

static void adjust_color_deleted(BSTree *p, BSTree *sib, BSTree **root)
{
    BSTree *parent = NULL;
    BSTree *gparent = NULL;
    BSTree *sibling = NULL;
    BSTree *tmp_cell = NULL;
    BSTree *lsib, *rsib;

    if (!p) 
        return;

    parent = p;
    sibling = sib;

    // 兄弟结点是红色
    if (sibling->color == Red) {
        if (sibling == parent->left) {
            parent->color = Red;
            sibling->color = Black;
            tmp_cell = rb_ll_rotate(parent);
            if (!tmp_cell->parent)
                *root = tmp_cell;
            parent = tmp_cell->right;
            sibling = parent->left;
            adjust_color_deleted(parent, sibling, root);
        } else {
            parent->color = Red;
            sibling->color = Black;
            tmp_cell = rb_rr_rotate(parent);
            if (!tmp_cell->parent)
                *root = tmp_cell;
            parent = tmp_cell->left;
            sibling = parent->right;
            adjust_color_deleted(parent, sibling, root);
        }
        return;
    }

    lsib = sibling->left;
    rsib = sibling->right;
    // 兄弟结点为黑色，并且兄弟结点两个孩子结点都为黑色
    if ((!lsib || lsib->color == Black) && (!rsib || rsib->color == Black)) {
        sibling->color = Red;
        if (parent->color == Red) {
            parent->color = Black;
            return;
        }
        gparent = parent->parent;
        sibling = NULL;
        if (gparent)
            sibling = (gparent->left == parent ? gparent->right : gparent->left);
        adjust_color_deleted(gparent, sibling, root);
    }

    // 兄弟结点为黑色，并且兄弟结点两个孩子结点左红右黑
    if (sibling == parent->right && lsib && lsib->color == Red && (!rsib || rsib->color == Black)) {
        sibling->color = Red;
        lsib->color = Black;
        tmp_cell = rb_ll_rotate(sibling);
        if (!tmp_cell->parent)
            *root = tmp_cell;
        parent = tmp_cell->parent;
        sibling = parent->right;
        adjust_color_deleted(parent, sibling, root);
        return;
    }

    // 兄弟结点为黑色，并且兄弟结点两个孩子结点左黑右红
    if (sibling == parent->left && rsib && rsib->color == Red && (!lsib || lsib->color == Black)) {
        sibling->color = Red;
        rsib->color = Black;
        tmp_cell = rb_rr_rotate(sibling);
        if (!tmp_cell->parent)
            *root = tmp_cell;
        parent = tmp_cell->parent;
        sibling = parent->left;
        adjust_color_deleted(parent, sibling, root);
        return;
    }

    // 兄弟结点为黑色，并且兄弟结点右孩子结点为红色
    if (sibling == parent->right && rsib && rsib->color == Red) {
        sibling->color = parent->color;
        parent->color = Black;
        sibling->right->color = Black;
        tmp_cell = rb_rr_rotate(parent);
        if (!tmp_cell->parent)
            *root = tmp_cell;
    }

    // 兄弟结点为黑色，并且兄弟结点左孩子结点为红色
    if (sibling == parent->left && lsib && lsib->color == Red) {
        sibling->color = parent->color;
        parent->color = Black;
        sibling->left->color = Black;
        tmp_cell = rb_ll_rotate(parent);
        if (!tmp_cell->parent)
            *root = tmp_cell;
    }
}

static BSTree *find_delete_node(int value, BSTree *t, BSTree **dnode)
{
    BSTree *tmp_cell;

    if (t == NULL) 
        return NULL;

    if (value < t->element) {
        tmp_cell = find_delete_node(value, t->left, dnode);
        if (tmp_cell)
            tmp_cell->parent = t;
        t->left = tmp_cell;
    } else if (value > t->element) {
        tmp_cell = find_delete_node(value, t->right, dnode);
        if (tmp_cell)
            tmp_cell->parent = t;
        t->right = tmp_cell;
    } else if (t->left && t->right) {
        tmp_cell = find_min(t->right);
        t->element = tmp_cell->element;
        tmp_cell = find_delete_node(t->element, t->right, dnode);
        if (tmp_cell)
            tmp_cell->parent = t;
        t->right = tmp_cell;
    } else {
        *dnode = t;
    }

    return t;
}

BSTree *rb_insert(int value, BSTree *t)
{
    BSTree *tmp_cell = NULL;
    BSTree *p = NULL;
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

    adjust_color_inserted(tmp_cell, &t);

    return t;
}

BSTree *rb_delete(int value, BSTree *t)
{
    BSTree *tmp_cell;
    BSTree *sibling;
    BSTree *parent;
    BSTree *deleted_node = NULL;
    BSTree *root;

    if (!t)
        return NULL;

    find_delete_node(value, t, &deleted_node);

    // 没找到欲删除的结点
    if (!deleted_node)
        return t;

    // 父节点
    parent = deleted_node->parent;

    // 如果父节点为空，要删除的节点就是根节点
    if (!parent) {
        t = (deleted_node->left ? deleted_node->left : deleted_node->right);
        if (t) {
            t->color = Black;
            t->parent = NULL;
        }
        free(deleted_node);
        return t;
    }

    // 被删除结点只有一个非空结点
    if (deleted_node->left || deleted_node->right) {
        tmp_cell = (deleted_node->left ? deleted_node->left : deleted_node->right);
        tmp_cell->color = Black;
        tmp_cell->parent = t->parent;

        if (deleted_node == parent->left)
            parent->left = tmp_cell;
        else
            parent->right = tmp_cell;

        free(deleted_node);
        return t;
    }

    // 被删除的是红色结点且有两个NULL结点
    if (deleted_node->color == Red) {
        if (parent->left == deleted_node)
            parent->left = NULL;
        else
            parent->right = NULL;

        free(deleted_node);
        return t;
    }

    // 被删除结点为黑色且有两个NULL结点
    sibling = (parent->left == deleted_node ? parent->right : parent->left);
    if (parent->left == deleted_node)
        parent->left = NULL;
    else
        parent->right = NULL;
    root = t;
    adjust_color_deleted(parent, sibling, &root);
    free(deleted_node);
    root->color = Black;
    return root;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

BSTree *rb_ll_rotate(BSTree *t)
{
    BSTree *ori_left = t->left;
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

BSTree *rb_rr_rotate(BSTree *t)
{
    BSTree *ori_right = t->right;
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

BSTree *rb_lr_rotate(BSTree *t)
{
    BSTree *tmp_cell = rb_rr_rotate(t->left);
    t->left = tmp_cell;
    tmp_cell->parent = t;
    return rb_ll_rotate(t);
}

BSTree *rb_rl_rotate(BSTree *t)
{
    BSTree *tmp_cell = rb_ll_rotate(t->right);
    t->right = tmp_cell;
    tmp_cell->parent = t;
    return rb_rr_rotate(t);
}
