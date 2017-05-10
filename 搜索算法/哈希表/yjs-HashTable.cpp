#include "yjs-HashTable.h"

HashTable::HashTable(int initCapacity, float loadFactor):
    m_initCapacity(initCapacity), 
    m_loadFactor(loadFactor),
    m_totalItems(0)
{
    m_node = new Node*[m_initCapacity];
    for(int i = 0; i < m_initCapacity; ++i)
    {
        m_node[i] = NULL;
    }
}

HashTable::~HashTable()
{
    freeNodes(m_initCapacity);
}

void HashTable::freeNodes(int capacity)
{
    for(int i = 0; i < capacity; ++i) {
        while(m_node[i]) {
            Node *curNode = m_node[i];
            m_node[i] = m_node[i]->m_next;
            delete curNode;
        }
    }
    delete [] m_node;
    m_node = NULL;
}

bool HashTable::insert(int key, int value)
{
    Node *insertNode = new Node(key, value);
    return insert(insertNode);
}

bool HashTable::insert(Node *insertNode, Node **insertTo)
{
    if(!insertTo) {
        insertTo = m_node;

        if((m_totalItems + 1) * 1.0 / m_initCapacity - m_loadFactor > ZERO) {
            reHash();
            return insert(insertNode);
        }
    }

    int index = insertNode->hash() % m_initCapacity;

    if(insertTo[index] == NULL) {
        insertTo[index] = insertNode;
    } else {
        Node *tmpNode = insertTo[index];
        Node *preNode = NULL;
        bool isExist = false;
        while(tmpNode) {
            if(*tmpNode == *insertNode) {
                isExist = true;
                break;
            } else if(tmpNode->m_key == insertNode->m_key) {
                *tmpNode = *insertNode;
                isExist = true;
                break;
            }
            preNode = tmpNode;
            tmpNode = tmpNode->m_next;
        }

        if(!isExist) {
            preNode->m_next = insertNode;
        }
    }

    if(insertTo == m_node) {
        ++m_totalItems;
    }
    return true;
}

bool HashTable::reHash()
{
    int oldInitCapacity = m_initCapacity;
    m_initCapacity *= 2;

    Node **newNode = new Node*[m_initCapacity];
    for(int i = 0; i < m_initCapacity; ++i) {
        newNode[i] = NULL;
    }

    for(int i = 0; i < oldInitCapacity; ++i) {
        Node *tmpNode = m_node[i];
        while(tmpNode) {
            insert(tmpNode, newNode);
            tmpNode = tmpNode->m_next;
        }
    }

    freeNodes(oldInitCapacity);
    m_node = newNode;
    return true;
}

void HashTable::erase(Node *node)
{
    int index = node->hash() % m_initCapacity;
    Node *curNode = new Node();
    Node *headNode = new Node();
    curNode->m_next = m_node[index];
    headNode = curNode;

    while(curNode->m_next) {
        if(curNode->m_next == node) {
            curNode->m_next = node->m_next;
            delete node;
            break;
        } else {
            curNode = curNode->m_next;
        }
    } 
    m_node[index] = headNode->m_next;

    delete curNode;
    delete headNode;
}

void HashTable::erase(int key)
{
    Node *findNode = find(key);
    if(findNode) {
        erase(findNode);
    }
}

void HashTable::clean()
{
    freeNodes(m_initCapacity);
    
    m_initCapacity = 16;
    m_totalItems = 0;

    m_node = new Node*[m_initCapacity];
    for(int i = 0; i < m_initCapacity; ++i)
    {
        m_node[i] = NULL;
    }
}

int HashTable::size()
{
    return m_initCapacity;
}

Node* HashTable::find(int key)
{
    Node *findNode = m_node[key % m_initCapacity];
    if(findNode != NULL) {
        while(findNode) {
            if(findNode->m_key == key) {
                return findNode;
            }
            findNode = findNode->m_next;
        }
    }
    return NULL;
}

Node& HashTable::operator[](int index)
{
    Node *findNode = find(index);
    if(findNode) {
        return *findNode;
    } else {
        insert(new Node(index));
        findNode = find(index % m_initCapacity);
        return *findNode;
    }
}

void HashTable::show()
{
    for(int i = 0; i < m_initCapacity; ++i)
    {
        cout << i << ":" ;
        Node *tmpNode = m_node[i];
        while(tmpNode != NULL) {
            cout << "[" << tmpNode->m_key << "," << tmpNode->m_value << "]";
            tmpNode = tmpNode->m_next;
        }
        cout << "\n";
    }
}
