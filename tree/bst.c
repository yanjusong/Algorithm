#include "bst.h"

#include <stdlib.h>

BSTree *find_min(BSTree *t)
{
    if (t == NULL) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return find_min(t->left);
    }
}

BSTree *find_max(BSTree *t)
{
    if (t == NULL) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return find_max(t->right);
    }
}

BSTree *find(int value, BSTree *t)
{
    if (t == NULL) {
        return NULL;
    }

    if (value < t->element) {
        return find(value, t->left);
    } else if (value > t->element) {
        return find(value, t->right);
    } else {
        return t;
    }
}

BSTree *bst_insert(int value, BSTree *t)
{
    if (!t)
        return getNode(value);

    if (value < t->element) {
        t->left = bst_insert(value, t->left);
    } else if (value > t->element) {
        t->right = bst_insert(value, t->right);
    } else {
        //duplicate, ignore it
        return t;
    }
    return t;
}

BSTree *bst_delete(int value, BSTree *t)
{
    //Deletes node from the tree
    // Return a pointer to the resulting tree
    BSTree *tmp_cell;

    if (t == NULL) return NULL;

    if (value < t->element) {
        t->left = bst_delete(value, t->left);
    } else if (value > t->element) {
        t->right = bst_delete(value, t->right);
    } else if (t->left && t->right) {
        tmp_cell = find_min(t->right);
        t->element = tmp_cell->element;
        t->right = bst_delete(t->element, t->right);
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
