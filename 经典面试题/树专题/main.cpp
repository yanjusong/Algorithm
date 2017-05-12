#include <iostream>
using namespace std;

#include "yjs-OperateTree.h"
#include "yjs-Node.h"

int main(int argc, char const *argv[])
{
    Node n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7);

    n1.m_left = &n2;
    n1.m_right = &n3;
    n2.m_left = &n4;
    n2.m_right = &n5;
    n3.m_left = &n6;
    n3.m_right = &n7;

    /*
     *          1
     *        /   \
     *       2     3
     *      / \   / \
     *     4   5 6   7
     */
    cout << "Level Traversal of The Binary Tree" << endl;
    levelTraversal(&n1);

    cout << "The Mirror Tree of The Binary Tree" << endl;
    mirrorTree(&n1);
    levelTraversal(&n1);
    cout << endl;
    mirrorTreeNotRcs(&n1);
    levelTraversal(&n1);
    
    cout << "The Height of Binary Tree " << endl;
    cout << treeHeight(&n1) << endl;

    cout << "Pre Order Traversal of The Binary Tree" << endl;
    preOrderTraversal(&n1);
    preOrderTraversalNotRcs(&n1);

    cout << "In Order Traversal of The Binary Tree" << endl;
    inOrderTraversal(&n1);
    cout << endl;
    inOrderTraversalNotRcs(&n1);

    cout << "Post Order Traversal of The Binary Tree" << endl;
    postOrderTraversal(&n1);
    cout << endl;
    postOrderTraversalNotRcs1(&n1);
    postOrderTraversalNotRcs2(&n1);

    return 0;
}