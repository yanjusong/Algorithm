#include "yjs-OperateTree.h"
#include <stack>
using namespace std;

void postOrderTraversal(Node *root)
{
    if(root == NULL)
        return ;

    if(root->m_left)
        postOrderTraversal(root->m_left);
    if(root->m_right)
        postOrderTraversal(root->m_right);

    cout << root->m_data << " ";
}

void postOrderTraversalNotRcs1(Node *root)
{
    if(root == NULL)
        return ;

    stack<Node *> s;
    s.push(root);
    Node *curNode = root->m_left;
    Node *preNode = NULL;

    while(!s.empty()) {
        while(curNode) {
            s.push(curNode);
            curNode = curNode->m_left;
        }

        curNode = s.top();
        if(preNode == NULL || preNode == curNode->m_right) {
            cout << curNode->m_data << " ";
            s.pop();
            preNode = curNode;
            curNode = NULL;
        } else {
            preNode = NULL;
            curNode = curNode->m_right;
        }

        
    }
    cout << endl;
}

void postOrderTraversalNotRcs2(Node *root)
{
    if(root == NULL)
        return ;

    stack<Node *> s1, s2;
    s1.push(root);
    while(!s1.empty()) {
        Node *tmpNode = s1.top();
        s1.pop();
        s2.push(tmpNode);

        if(tmpNode->m_left)
            s1.push(tmpNode->m_left);
        if(tmpNode->m_right)
            s1.push(tmpNode->m_right);
    }

    while(!s2.empty()) {
        Node *tmpNode = s2.top();
        s2.pop();
        cout << tmpNode->m_data << " ";
    }
    cout << endl;
}
