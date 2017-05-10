#ifndef _NODE_H_
#define _NODE_H_

#include <iostream> // NULL
#include <functional>
using namespace std;

struct Node
{
    int m_key;
    int m_value;
    Node *m_next;

    int hash();
    Node(int key, int value = 0, Node *next = NULL);
    Node();
    ~Node();
    bool operator==(const Node &node);
    Node& operator=(const Node &node);
    Node& operator=(int value);
};

#endif // _NODE_H_