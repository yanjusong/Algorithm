#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
using namespace std;

struct Node
{
    int value;
    vector<Node *> connectionNodes;

    Node(int v):value(v) {}
};

void dfsSearch(Node *n)
{
    if(n == NULL)
        return ;

    set<Node *> set;
    stack<Node *> s;
    s.push(n);

    while(!s.empty()) {
        Node *tmp = s.top();

        // 访问节点，并将访问标志置位
        if(set.find(tmp) == set.end()) {
            cout << tmp->value << " ";
            set.insert(tmp);
        }

        // flag为1表示节点的所有连接节点都被访问过
        int flag = 1;
        for(auto &connNode : tmp->connectionNodes) {
            if(set.find(connNode) == set.end()) {
                s.push(connNode);
                flag = 0;
                break;
            }
        }

        // 当节点所有的链接节点都被访问则出栈
        if(flag)
            s.pop();
    }
    
    cout << endl;
}

void bfsSearch(Node *n)
{
    if(n == NULL)
        return ;

    set<Node *> set;
    queue<Node *> q;

    q.push(n);

    while(!q.empty()) {
        Node *tmp = q.front();
        q.pop();

        if(set.find(tmp) == set.end()) {
            cout << tmp->value << " ";
            set.insert(tmp);
        }

        for(auto &connNode : tmp->connectionNodes) {
            if(set.find(connNode) == set.end())
                q.push(connNode);
        }
    }

    cout << endl;
}

int main(int argc, char const *argv[])
{
    Node n1(1);
    Node n2(2);
    Node n3(3);
    Node n4(4);
    Node n5(5);
    Node n6(6);

    // 构造的图如dfs-bfs.png所示
    n1.connectionNodes.push_back(&n2);
    n1.connectionNodes.push_back(&n6);
    n1.connectionNodes.push_back(&n3);

    n2.connectionNodes.push_back(&n1);
    n2.connectionNodes.push_back(&n4);

    n3.connectionNodes.push_back(&n1);

    n4.connectionNodes.push_back(&n2);
    n4.connectionNodes.push_back(&n6);

    n5.connectionNodes.push_back(&n6);

    n6.connectionNodes.push_back(&n1);
    n6.connectionNodes.push_back(&n4);
    n6.connectionNodes.push_back(&n5);

    dfsSearch(&n1);
    bfsSearch(&n1);

    return 0;
}