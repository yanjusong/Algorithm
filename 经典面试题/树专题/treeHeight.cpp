#include "yjs-OperateTree.h"

int treeHeight(Node *root)
{
    if(root == NULL)
        return 0;

    int len_left = treeHeight(root->m_left);
    int len_right = treeHeight(root->m_right);

    return 1 + (len_left > len_right ? len_left : len_right);
}