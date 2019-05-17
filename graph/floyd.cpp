#include "graph.hpp"

#include <map>
#include <algorithm>

static void getNodes(GNode *root, std::map<int, GNode *> &nodes, std::map<GNode *, int> &nodeIds)
{
    std::set<GNode *> nodeSet = root->getAllNodes();
    int i = 0;

    for (auto &x : nodeSet)
    {
        nodes[i] = x;
        nodeIds[x] = i;

        ++i;
    }
}

void GNode::floyd(std::vector<NodeDisPair> &result)
{
    std::map<int, GNode *> nodes;
    std::map<GNode *, int> nodeIds;
    getNodes(this, nodes, nodeIds);
    int len = nodes.size();

    std::vector<std::vector<int64_t>> path(len, std::vector<int64_t>(len, 0x7fffffff));
    for (int i = 0; i < len; ++i)
    {
        for (auto &x : nodes[i]->neighbors_)
        {
            int j = nodeIds[x.node_];
            path[i][j] = x.dis_;
        }
        path[i][i] = 0;
    }

    for (int k = 0; k < len; ++k)
    {
        for (int i = 0; i < len; ++i)
        {
            for (int j = 0; j < len; ++j)
            {
                path[i][j] = std::min(path[i][j], path[i][k] + path[k][j]);
            }
        }
    }

    // for log
    // for (int i = 0; i < len; ++i)
    // {
    //     for (int j = 0; j < len; ++j)
    //     {
    //         printf("%lld ", path[i][j]);
    //     }
    //     printf("\n");
    // }

    int rootId = nodeIds[this];
    for (int j = 0; j < len; ++j)
    {
        result.push_back(NodeDisPair(nodes[j], (int)path[rootId][j]));
    }
}
