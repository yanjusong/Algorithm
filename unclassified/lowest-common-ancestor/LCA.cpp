#include <iostream>

struct Node
{
    Node *left_;
    Node *right_;
    int value_;
};

#define IS_SORTED 1
#if IS_SORTED
Node *getLCA(Node *root, Node *n1, Node *n2)
{
    if (!root)
        return NULL;

    int minNum = (n1->value_ < n2->value_) ? n1->value_ : n2->value_;
    int maxNum = (n1->value_ > n2->value_) ? n1->value_ : n2->value_;

    while (root){
        int tmp = root->value_;
        if (tmp >= minNum && tmp <= maxNum) {
            return root;
        } else if (tmp > maxNum) {
            root = root->left_;
        } else {
            root = root->right_;
        }
    }
    
    return NULL;
}
#else
Node *getLCA(Node *root, Node *n1, Node *n2)
{
    if (!root)
        return NULL;
    if (root == n1 || root == n2)
        return root;

    Node *left = getLCA(root->left_, n1, n2);
    Node *right = getLCA(root->right_, n1, n2);

    if (left && right)
        return root;
    else if (left)
        return left;
    else /* 如果right为NULL也返回NULL */
        return right;
}
#endif
