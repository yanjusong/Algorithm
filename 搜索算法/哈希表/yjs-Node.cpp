#include "yjs-Node.h"

Node::Node(int key, int value, Node *next):
    m_key(key),
    m_value(value),
    m_next(next)
{

}

Node::Node():
    m_key(0),
    m_value(0),
    m_next(NULL)
{

}

Node::~Node() 
{

}

int Node::hash()
{
    // 这里的std不值为何无法去掉
    return std::hash<int>()(m_key);
}

bool Node::operator==(const Node &node)
{
    if(this->m_key == node.m_key && this->m_value == node.m_value) {
        return true;
    }
    return false;
}

Node& Node::operator=(const Node &node)
{
    if(this != &node && this->m_key == node.m_key) {
        this->m_value = node.m_value;
    }
    return *this;
}

Node& Node::operator=(int value)
{
    this->m_value = value;
    return *this;
}