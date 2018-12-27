#include "bst.h"

#include <stdlib.h>

Tree *find_min(Tree *t)
{
    if (t == NULL) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return find_min(t->left);
    }
}

Tree *find_max(Tree *t)
{
    if (t == NULL) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return find_max(t->right);
    }
}

Tree *find(int value, Tree *t)
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

Tree *insert(int value, Tree *t)
{
    Tree *new_node;

    if (t == NULL) {
        new_node = (Tree *)malloc(sizeof(Tree));
        if (new_node == NULL) {
            return t;
        }

        new_node->element = value;

        new_node->left = new_node->right = NULL;
        return new_node;
    }

    if (value < t->element) {
        t->left = insert(value, t->left);
    } else if (value > t->element) {
        t->right = insert(value, t->right);
    } else {
        //duplicate, ignore it
        return t;
    }
    return t;
}

Tree *del(int value, Tree *t)
{
    //Deletes node from the tree
    // Return a pointer to the resulting tree
    Tree *x;
    Tree *tmp_cell;

    if (t == NULL) return NULL;

    if (value < t->element) {
        t->left = del(value, t->left);
    } else if (value > t->element) {
        t->right = del(value, t->right);
    } else if (t->left && t->right) {
        tmp_cell = find_min(t->right);
        t->element = tmp_cell->element;
        t->right = del(t->element, t->right);
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
