#include "yjs-OperateTree.h"

#include <queue>
using namespace std;

void levelTravel(Node *root)
{
    if(!root) {
        return ;
    }

    queue<Node *> q;
    q.push(root);
    while(!q.empty()) {
        Node *tmpNode = q.front();
        cout << tmpNode->m_data << endl;
        q.pop();        

        if(tmpNode->m_left) {
            q.push(tmpNode->m_left);
        }

        if(tmpNode->m_right) {
            q.push(tmpNode->m_right);
        }
    }
}