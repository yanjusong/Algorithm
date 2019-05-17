#ifndef GRAPH_H_20190513
#define GRAPH_H_20190513

#include <iostream>
#include <vector>
#include <set>

class GNode;
typedef std::pair<GNode *, int> NodeDisPair;

typedef void(*UserFunc)(GNode *root, void *udata);

class GNode
{
public:
    int val_;
    std::vector<NodeDisPair> neighbors_;

    GNode() {}
    GNode(int val) : val_(val) {}

    void initNeighbors(const std::vector<GNode *> &neighbors)
    {
        for (const auto &x : neighbors)
        {
            neighbors_.push_back(NodeDisPair(x, 0));
        }
    }

    void initNeighbors(std::vector<NodeDisPair> neighbors)
    {
        neighbors_ = neighbors;
    }

    void print()
    {
        std::set<GNode *> visitedSet;
        printGraph(this, visitedSet);
    }

    void destroy()
    {
        std::set<GNode *> visitedSet;
        destroy(this, visitedSet);
        for (auto &x : visitedSet)
        {
            delete x;
        }
    }

    int getVal()
    {
        return val_;
    }

    // TODO:
    bool checkDis()
    {
        return true;
    }

    void dijkstra(std::vector<NodeDisPair> &result);

    void bfs(UserFunc func, void *udata);

    void dfs(UserFunc func, void *udata);

private:
    void destroy(GNode *root, std::set<GNode *> &visitedSet)
    {
        if (!root)
        {
            return;
        }
        visitedSet.insert(root);

        for (auto &x : root->neighbors_)
        {
            if (visitedSet.find(x.first) != visitedSet.end())
            {
                continue;
            }

            destroy(x.first, visitedSet);
        }
    }

    void printGraph(GNode *root, std::set<GNode *> &visitedSet)
    {
        if (!root)
        {
            return;
        }
        visitedSet.insert(root);

        printf("[val:%d] [%p]\n", root->val_, root);
        for (auto &x : root->neighbors_)
        {
            printf("\t |-  [val:%d] [dis:%d] [%p]\n", x.first->val_, x.second, x.first);
        }

        for (auto &x : root->neighbors_)
        {
            if (visitedSet.find(x.first) != visitedSet.end())
            {
                continue;
            }

            printGraph(x.first, visitedSet);
        }
    }
};

#endif // !GRAPH_H_20190513
