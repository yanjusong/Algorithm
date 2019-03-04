#include <iostream>
#include <cassert>
using namespace std;

struct Node
{
    int value_;
    Node* next_;

    Node(int value) : value_(value), next_(NULL) {}
};

void printLinkedList(Node *head)
{
    Node *curNode = head;
    while (curNode) {
        cout << curNode->value_ << " ";
        curNode = curNode->next_;
    }
    cout << endl;
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

Node* reverseRecur(Node *head)
{
    // 输入为空或到达最后一个结点
    if (!head || !head->next_)
        return head;

    Node *nextNode = head->next_;
    head->next_ = NULL;
    Node *reverseNode = reverseRecur(nextNode);
    nextNode->next_ = head;
    return reverseNode;
}

Node* reverse(Node *head)
{
    Node *preHead = new Node(-1);
    Node *curNode = head;
    Node *nextHeadNode = NULL;
    Node *reverseNode = NULL;

    while (curNode) {
        Node *tmpNode = curNode->next_;
        nextHeadNode = preHead->next_;
        preHead->next_ = curNode;
        curNode->next_ = nextHeadNode;
        curNode = tmpNode;
    }

    reverseNode = preHead->next_;
    delete preHead;
    return reverseNode;
}

int main()
{
    assert(reverse(NULL) == NULL);
    assert(reverseRecur(NULL) == NULL);

    {
        cout << "递归模式反转" << endl;
        Node *head = new Node(0);
        Node *railNode = head;
        for (int i = 1; i < 10; ++i) {
            Node *node = new Node(i);
            railNode->next_ = node;
            railNode = node;
        }

        printLinkedList(head);
        head = reverseRecur(head);
        printLinkedList(head);

        freeLinkedList(head);
    }

    cout << endl << endl;

    {
        cout << "非递归模式反转" << endl;
        Node *head = new Node(0);
        Node *railNode = head;
        for (int i = 1; i < 10; ++i) {
            Node *node = new Node(i);
            railNode->next_ = node;
            railNode = node;
        }

        printLinkedList(head);
        head = reverse(head);
        printLinkedList(head);

        freeLinkedList(head);
    }

    return 0;
}
