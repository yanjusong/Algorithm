#include <iostream>
#include <stack>
#include <unordered_set>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int d = 0, Node *n = NULL):data(d), next(n) {}
};

// 判断两个链表是否存在交点
bool isExistSameNode1(Node *n1, Node *n2);
bool isExistSameNode2(Node *n1, Node *n2); 

// 寻找两个链表的相交结点没有返回NULL
Node* findSameNode1(Node *n1, Node *n2); 
Node* findSameNode2(Node *n1, Node *n2);
Node* findSameNode3(Node *n1, Node *n2); 
Node* findSameNode4(Node *n1, Node *n2);

/*
 * 拿不到offer的暴力法：O(n^2)
 */
bool isExistSameNode1(Node *n1, Node *n2) 
{
    if(n1 != NULL || n2 != NULL) {
        return false;
    } else if(n1 == n2) {
        return true;
    }

    return isExistSameNode1(n1->next, n2) || isExistSameNode1(n1, n2->next);
}

/*
 * 优质解法：O(m + n)
 * 利用单向链表的特性，若两个单向链表相交那么相交之后的结点序列都一致
 */
bool isExistSameNode2(Node *n1, Node *n2) {
    if(!n1 || !n2) {
        return false;
    }
    // 寻找n1和n2的尾结点
    while(n1->next) n1 = n1->next;
    while(n2->next) n2 = n2->next;

    return n1 == n2;
}

/*
 * 暴力美学：O(n^2)
 */
Node* findSameNode1(Node *n1, Node *n2) {
    if(!n1 || !n2) {
        return NULL;
    }

    Node *head1 = n1, *head2 = n2;

    while(head1) {
        head2 = n2;
        while(head2) {
            if(head1 == head2) {
                return head1;
            }
            head2 = head2->next;
        }
        head1 = head1->next;
    }
    return NULL;
}

/*
 * 长度判断法 Q(n^2)
 */
Node* findSameNode2(Node *n1, Node *n2) 
{
    if(!n1 || !n2) {
        return NULL;
    }

    int len1 = 0, len2 = 0;
    Node *head1 = n1, *head2 = n2;

    // 分别统计两个链表长度
    while(head1) {
        ++len1;
        head1 = head1->next;
    }

    while(head2) {
        ++len2;
        head2 = head2->next;
    }

    int diff = len1 - len2;
    Node *tmp = diff > 0 ? n1 : n2;
    head2 = diff > 0 ? n2 : n1;
    while(diff > 0) {
        tmp = tmp->next;
        --diff;
    }
    head1 = tmp;

    while(head1 !=NULL && head2 != NULL) {
        if(head1 == head2) {
            return head1;
        }
        head1 = head1->next;
        head2 = head2->next;
    }    

    return NULL;
}

/*
 * 辅助栈解法
 */
Node* findSameNode3(Node *n1, Node *n2) 
{
    if(!n1 || !n2) {
        return NULL;
    }

    stack<Node *> s1;
    stack<Node *> s2;

    while(n1) {
        s1.push(n1);
        n1 = n1->next; 
    }

    while(n2) {
        s2.push(n2);
        n2 = n2->next; 
    }

    Node *res = NULL;
    while( (!s1.empty()) && (!s2.empty()) ) {
        if(s1.top() != s2.top()) {
            return res;
        }
        res = s1.top();
        s1.pop();
        s2.pop();
    }

    return NULL;
}

/*
 * 哈希表辅助法，在C++中使用unordered_set<Node *>
 */
Node* findSameNode4(Node *n1, Node *n2)
{
    if(!n1 || !n2) {
        return NULL;
    }

    unordered_set<Node *> hashTable;
    while(n1) {
        hashTable.insert(n1);
        n1 = n1->next;
    }

    unordered_set<Node *>::iterator end = hashTable.end();
    while(n2) {
        if(hashTable.find(n2) != end) {
            return n2;
        }
        n2 = n2->next;
    }

    return NULL;
}


int main(int argc, char const *argv[])
{
    Node N1(1), N2(2), N3(3), N4(4), N5(5);
    Node M1(10), M2(11), /* M3 = N4 */ M4(12);
    Node K1(100), K2(101);
    N1.next = &N2;
    N2.next = &N3;
    N3.next = &N4;
    N4.next = &N5;
    /*
     * N1->N2->N3->N4->N5
     */

    M1.next = &M2;
    M2.next = &N4;
    N4.next = &M4;
    /*
     *               M4
     *               |               
     *   N1->N2->N3->N4  (由于是单向链表这里断开) ->N5
     *              /
     *        M1->M2
     */

    K1.next = &K2;
    /*
     * K1->K2
     */

    cout << isExistSameNode2(&N1, &M1) << endl;
    cout << isExistSameNode2(&N1, &K1) << endl;

    Node *res = NULL;
    if(res = findSameNode4(&N1, &M1)) {
        cout << res->data << endl;
    }
    if(res = findSameNode4(&N1, &K1)) {
        cout << res->data << endl;
    }

    return 0;
}