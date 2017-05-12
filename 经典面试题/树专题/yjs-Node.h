#ifndef _YJS_NODE_H_
#define _YJS_NODE_H_

#include <iostream>
using namespace std;

struct Node
{
    int m_data;
    Node *m_left;
    Node *m_right;

    Node(int data = 0, Node *left = NULL, Node *right = NULL);
    ~Node();
};

#endif // _YJS_NODE_H_