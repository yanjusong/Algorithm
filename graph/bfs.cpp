#include "graph.hpp"

#include <set>
#include <queue>
#include <cassert>

void GNode::bfs(UserFunc func, void *udata)
{
    std::set<GNode *> visitedSet;
    std::queue<GNode *> curQueue;
    curQueue.push(this);
    visitedSet.insert(this);

    while (!curQueue.empty())
    {
        GNode *lastNode = curQueue.front();
        curQueue.pop();

        assert(lastNode);
        // 严重错误
        if (!lastNode)
        {
            fprintf(stderr, "line:%d, fatal:get an null obj in queue\n", __LINE__);
            break;
        }

        for (auto &x : lastNode->neighbors_)
        {
            if (visitedSet.find(x.first) == visitedSet.end())
            {
                curQueue.push(x.first);
                visitedSet.insert(x.first);
            }
        }

        // 调用用户注册的处理函数
        func(lastNode, udata);
    }
}
