#include <iostream>
using namespace std;

struct Node
{
    int value_;
    Node* next_;

    Node(int value) : value_(value), next_(NULL) {} 
};

/**
 * O(1)空间复杂度逆向打印链表 
 */
void printReverseLinkedList(const Node *head)
{
    if (head == NULL)
        return ;
    
    printReverseLinkedList(head->next_);
    cout << head->value_ << " ";
}

void freeLinkedList(Node *head)
{
    Node *curNode = head;
    Node *badNode = NULL;
    while (curNode) {
        badNode = curNode;
        curNode = curNode->next_;
        delete badNode;
    }
}

int main()
{
    // case 1:
    {
        Node *head = new Node(0);
        Node *railNode = head;
        for (int i = 1; i < 10; ++i) {
            Node *node = new Node(i);
            railNode->next_ = node;
            railNode = node;
        }

        printReverseLinkedList(head);
        cout << endl;

        freeLinkedList(head);
    }

    // case 2:
    {
        printReverseLinkedList(NULL);
    }

    return 0;
}