#include "graph.hpp"

#include <iostream>
using namespace std;

void bfsHandle(GNode *root, void *udata)
{
    int *id = (int *)udata;
    if (id)
    {
        (*id)++;
    }

    printf("dfs [val:%d][%p][udata:%d]\n", root->getVal(), root, (id ? *id : -1));
}

void test(GNode *root)
{
    static int caseIndex = 1;
    cout << "\ncase " << caseIndex++ << ":\n";
    cout << "Input:\n";
    root->print();

    cout << "Output:\n";
    int id = 0;
    root->dfs(bfsHandle, (void *)&id);
}

// g++ -std=c++11 dfs.cpp test__dfs.cpp -o a && ./a
int main()
{
    // case 1:
    // 有向图
    {
        GNode n1(1);
        GNode n2(2);
        GNode n3(3);
        GNode n4(4);
        GNode n5(5);
        GNode n6(6);

        n1.initNeighbors(vector<std::pair<GNode *, int>>{{&n2, 1}, {&n3, 12}});
        n2.initNeighbors(vector<std::pair<GNode *, int>>{{&n3, 9}, {&n4, 3}});
        n3.initNeighbors(vector<std::pair<GNode *, int>>{{&n5, 5}});
        n4.initNeighbors(vector<std::pair<GNode *, int>>{{&n3, 4}, {&n5, 13}, {&n6, 15}});
        n5.initNeighbors(vector<std::pair<GNode *, int>>{{&n6, 4}});

        test(&n1);
    }

    // case 2:
    // 无向图
    {
        GNode n1(1);
        GNode n2(2);
        GNode n3(3);
        GNode n4(4);
        GNode n5(5);
        GNode n6(6);

        n1.initNeighbors(vector<std::pair<GNode *, int>>{{&n2, 7}, {&n3, 9}, {&n4, 11}});
        n2.initNeighbors(vector<std::pair<GNode *, int>>{{&n1, 7}, {&n3, 8}, {&n6, 20}});
        n3.initNeighbors(vector<std::pair<GNode *, int>>{{&n1, 9}, {&n2, 8}, {&n5, 6}});
        n4.initNeighbors(vector<std::pair<GNode *, int>>{{&n1, 11}, {&n5, 3}});
        n5.initNeighbors(vector<std::pair<GNode *, int>>{{&n3, 6}, {&n4, 3}, {&n6, 1}});
        n6.initNeighbors(vector<std::pair<GNode *, int>>{{&n2, 20}, {&n5, 1}});

        test(&n1);
    }

    return 0;
}
