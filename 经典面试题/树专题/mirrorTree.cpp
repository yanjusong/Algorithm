#include "yjs-OperateTree.h"
#include <queue>
using namespace std;

void mirrorTree(Node *root)
{
    if(root == NULL) {
        return ;
    }

    if(root->m_left == NULL && root->m_right == NULL) {
        return ;
    }

    Node *tmpNode = root->m_left;
    root->m_left = root->m_right;
    root->m_right = tmpNode;

    mirrorTree(root->m_left);
    mirrorTree(root->m_right);
}

void mirrorTreeNotRcs(Node *root)
{
    if(root == NULL) {
        return ;
    }

    if(root->m_left == NULL && root->m_right == NULL) {
        return ;
    }

    queue<Node *> q;
    q.push(root);

    while(!q.empty()) {
        Node *tmpNode = q.front();
        Node *leftNode = tmpNode->m_left;
        Node *rightNode = tmpNode->m_right;
        tmpNode->m_left = rightNode;
        tmpNode->m_right = leftNode;
        q.pop();

        if(leftNode) {
            q.push(leftNode);
        }
        if(rightNode) {
            q.push(rightNode);
        }
    }
}
