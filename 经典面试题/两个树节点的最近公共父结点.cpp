#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *m_left;
    Node *m_right;
    Node(int d = 0, Node *left = NULL, Node *right = NULL):
        data(d), 
        m_left(left), 
        m_right(right) {}
};

/*
 * lowest common ancestor
 * 找出二叉树上任意两个结点的最近公共父结点
 * @author yanjusong
 */
Node* lca(Node *root, Node *n1, Node *n2)
{
    if(!root || !n1 || !n2) 
        return NULL;

    if(root == n1 || root == n2)
        return root;

    Node *tl = lca(root->m_left, n1, n2);
    Node *tr = lca(root->m_right, n1, n2);

    if(tl && tr)
        return root;

    if(tl)
        return tl;
    if(tr)
        return tr;

    return NULL;
}

int main(int argc, char const *argv[])
{
    Node n1(1), n2(2), n3(3), n4(4), n5(5), n6(6), n7(7);

    n1.m_left = &n2;
    n1.m_right = &n3;
    n2.m_left = &n4;
    n2.m_right = &n5;
    n3.m_left = &n6;
    n3.m_right = &n7;

    /****************************************
     *                1
     *               / \
     *              2   3
     *             / \ / \
     *            4  5 6  7 
      ****************************************/

    cout << lca(&n1, &n4, &n7)->data << endl;
    cout << lca(&n1, &n1, &n7)->data << endl;
    cout << lca(&n1, &n4, &n5)->data << endl;

    return 0;
}
