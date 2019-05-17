#ifndef GRAPH_H_20190513
#define GRAPH_H_20190513

#include <iostream>
#include <vector>
#include <set>

class GNode;

struct NodeDisPair
{
    GNode *node_;
    int dis_;
    NodeDisPair(GNode *node, int dis = 0) : node_(node), dis_(dis) {}

    bool operator<(const NodeDisPair &rhs) const
    {
        return node_ < rhs.node_;
    }
};

typedef void(*UserFunc)(GNode *root, void *udata);

class GNode
{
public:
    int val_;
    std::set<NodeDisPair> neighbors_;

    GNode() {}
    GNode(int val) : val_(val) {}

    void initNeighbors(const std::vector<GNode *> &neighbors)
    {
        for (const auto &x : neighbors)
        {
            neighbors_.insert(NodeDisPair(x, 0));
        }
    }

    void initNeighbors(std::vector<std::pair<GNode *, int>> neighbors)
    {
        for (const auto &x : neighbors)
        {
            neighbors_.insert(NodeDisPair(x.first, x.second));
        }
    }

    void print()
    {
        std::set<GNode *> visitedSet;
        printGraph(this, visitedSet);
    }

    static void destroy(GNode *root)
    {
        std::set<GNode *> visitedSet;
        destroy(root, visitedSet);
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

    std::set<GNode *> getAllNodes()
    {
        std::set<GNode *> result;
        getAllNodes(this, result);

        return result;
    }

    void createOrChangeNeighbor(GNode *root, int dis)
    {
        std::set<NodeDisPair>::iterator it = neighbors_.find(NodeDisPair(root));
        if (it != neighbors_.end())
        {
            neighbors_.erase(it);
        }
        neighbors_.insert(NodeDisPair(root, dis));
    }

    bool hasNeighbor(GNode *root)
    {
        return neighbors_.find(NodeDisPair(root)) != neighbors_.end();
    }

    void dijkstra(std::vector<NodeDisPair> &result);

    void bfs(UserFunc func, void *udata);

    void dfs(UserFunc func, void *udata);

    GNode *prim();

    GNode *kruskal();

private:
    static void destroy(GNode *root, std::set<GNode *> &visitedSet)
    {
        if (!root)
        {
            return;
        }
        visitedSet.insert(root);

        for (auto &x : root->neighbors_)
        {
            if (visitedSet.find(x.node_) != visitedSet.end())
            {
                continue;
            }

            destroy(x.node_, visitedSet);
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
            printf("\t |-  [val:%d] [dis:%d] [%p]\n", x.node_->val_, x.dis_, x.node_);
        }

        for (auto &x : root->neighbors_)
        {
            if (visitedSet.find(x.node_) != visitedSet.end())
            {
                continue;
            }

            printGraph(x.node_, visitedSet);
        }
    }

    void getAllNodes(GNode *root, std::set<GNode *> &visitedSet)
    {
        if (!root)
        {
            return;
        }
        visitedSet.insert(root);

        for (auto &x : root->neighbors_)
        {
            if (visitedSet.find(x.node_) != visitedSet.end())
            {
                continue;
            }

            getAllNodes(x.node_, visitedSet);
        }
    }
};

#endif // !GRAPH_H_20190513
