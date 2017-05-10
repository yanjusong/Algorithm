#include <iostream>
#include <functional>
using namespace std;

#include "yjs-HashTable.h"

int main(int argc, char const *argv[])
{
    HashTable h;

    cout << "******************** test insert() *************************" << "\n";

    h.insert(0, 12);
    h.insert(1, 12);
    h.insert(2, 12);
    h.insert(3, 12);
    h.insert(4, 12);
    h.insert(5, 12);
    h.insert(6, 12);
    h.insert(7, 12);
    h.insert(8, 12);
    h.insert(9, 12);
    h.insert(10, 12);
    h.insert(11, 12);
    h.show();

    cout << "******************** test reHash **************************" << "\n";
    h.insert(12, 12);
    h.insert(13, 12);
    h.insert(14, 12);
    h.insert(15, 12);
    h.show();

    cout << "******************** test insert **************************" << "\n";
    h.insert(16, 12);
    h.insert(17, 17);

    h.show();

    cout << "******************** test overwrite insert*****************" << "\n";
    h.insert(0, 12);
    h.insert(0, 12);
    h.insert(0, 13);
    h.insert(32, 32);
    h.show();

    cout << "************************ test find *************************" << "\n";
    Node *findNode = h.find(17);
    if(findNode) {
        cout << "find 1:" << findNode->m_value << "\n";
    }

    findNode = h.find(32);
    if(findNode) {
        cout << "find 2:" << findNode->m_value << "\n";
    }

    findNode = h.find(18);
    if(findNode) {
        cout << "find 3:" << findNode->m_value << "\n";
    }
    
    Node findNode2 = h[32];
    cout << "find 4:" << findNode2.m_value << "\n";

    cout << "********************* test [] *****************************" << "\n";
    h[32] = 12;
    h.show();

    cout << "*********************** test erase() **********************" << "\n";
    Node *findNode3 = h.find(0);
    h.erase(findNode3);
    h.show();

    cout << "*********************** test clean() **********************" << "\n";
    h.clean();
    h.show();

    return 0;

}