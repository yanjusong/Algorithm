#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <iostream>
using namespace std;

#include "yjs-Node.h"

const float ZERO = 10e-6;

class HashTable
{
private:
    int m_initCapacity;
    float m_loadFactor;
    unsigned int m_totalItems;
    Node **m_node;

private:
	void freeNodes(int capacity);
public:
    HashTable(int initCapacity = 16, float loadFactor = 0.75);
    ~HashTable();
    int size();
    Node& operator[](int index);
    bool insert(int key, int value);
    bool insert(Node *insertNode, Node **insertTo = NULL);
    void erase(Node *node);
    void erase(int key);
    Node* find(int key);
    void clean();
    bool reHash();
    void show();
};

#endif // _HASHTABLE_H_