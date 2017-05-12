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

	levelTravel(&n1);
	cout << endl;
	mirrorTree(&n1);
	levelTravel(&n1);
	cout << endl;
	mirrorTreeNotRct(&n1);
	levelTravel(&n1);

	return 0;
}