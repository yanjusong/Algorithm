#include "graph.hpp"

#include <set>
#include <cassert>

void dfsInternal(GNode *root, UserFunc func, void *udata, std::set<GNode *> &visitedSet)
{
    assert(root);
    // 严重错误
    if (!root)
    {
        fprintf(stderr, "line:%d, fatal:get an null obj in queue\n", __LINE__);
        return;
    }

    if (visitedSet.find(root) == visitedSet.end())
    {
        // 调用用户注册的处理函数
        func(root, udata);
        visitedSet.insert(root);
    }

    for (auto &x : root->neighbors_)
    {
        if (visitedSet.find(x.node_) == visitedSet.end())
        {
            dfsInternal(x.node_, func, udata, visitedSet);
        }
    }
}

void GNode::dfs(UserFunc func, void *udata)
{
    std::set<GNode *> visitedSet;
    dfsInternal(this, func, udata, visitedSet);
}
