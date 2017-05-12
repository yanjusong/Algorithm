#include "yjs-OperateTree.h"

#include <stack>
using namespace std;

void inOrderTraversal(Node *root)
{
    if(root == NULL)
        return ;

    if(root->m_left)
        inOrderTraversal(root->m_left);

    cout << root->m_data << " ";

    if(root->m_right)
        inOrderTraversal(root->m_right);

    // cout << endl;
}

void inOrderTraversalNotRcs(Node *root)
{
    if(root == NULL)
        return ;

    stack<Node *> s;
    s.push(root);
    Node *curNode = root->m_left;

    while(!s.empty() || curNode) {
        while(curNode) {
            s.push(curNode);
            curNode = curNode->m_left;
        }

        curNode = s.top();
        cout << curNode->m_data << " ";
        s.pop();

        curNode = curNode->m_right;
    }

    cout << endl;
}