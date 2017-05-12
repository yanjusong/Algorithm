#include "yjs-OperateTree.h"
#include <stack>
using namespace std;

void preOrderTraversal(Node *root)
{
    if(root == NULL)
        return ;

    cout << root->m_data << " ";
    if(root->m_left)
        preOrderTraversal(root->m_left);
    if(root->m_right)
        preOrderTraversal(root->m_right);
    cout << endl;
}

void preOrderTraversalNotRcs(Node *root)
{
    if(root == NULL)
        return ;

    stack<Node *> s;
    s.push(root);

    while(!s.empty()) {
        Node *tmpNode = s.top();
        s.pop();
        cout << tmpNode->m_data << " ";

        if(tmpNode->m_right)
            s.push(tmpNode->m_right);

        if(tmpNode->m_left)
            s.push(tmpNode->m_left);
    }
    cout << endl;
}