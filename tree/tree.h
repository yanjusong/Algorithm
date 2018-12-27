#ifndef TREE_H_20181227
#define TREE_H_20181227

typedef struct Tree Tree;

struct Tree
{
    Tree *left, *right;
    int element;
};

Tree *make_empty(Tree *t);

void print_ascii_tree(Tree *t);

#endif // !TREE_H_20181227
