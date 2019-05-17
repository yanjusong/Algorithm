#include "graph.hpp"

#include <map>
#include <algorithm>

void GNode::dijkstra(std::vector<NodeDisPair> &result)
{
    // dis的每个元素表示this到这个结点的当前最短距离，
    // 如果可以在visitedSet找到这个结点指针说明是最终结果。
    std::map<GNode *, int> dis;

    // visitedSet记录已经确定最短距离的结点
    std::set<GNode *> visitedSet;

    dis[this] = 0;
    std::map<GNode *, int>::iterator minIt;
    int minDis = 0x7fffffff;
    std::map<GNode *, int>::iterator it;
    std::set<NodeDisPair>::iterator vecIt;

    while (true)
    {
        minIt = dis.end();
        minDis = 0x7fffffff;

        // 找到当前距离开始结点最小的点
        for (it = dis.begin(); it != dis.end(); ++it)
        {
            if (visitedSet.find(it->first) == visitedSet.end() && it->second < minDis)
            {
                minDis = it->second;
                minIt = it;
            }
        }

        // 所有结点已经计算出最终距离
        if (minIt == dis.end())
        {
            break;
        }

        for (vecIt = minIt->first->neighbors_.begin();
             vecIt != minIt->first->neighbors_.end();
             ++vecIt)
        {
            if (dis.find(vecIt->node_) == dis.end())
            {
                dis[vecIt->node_] = dis[minIt->first] + vecIt->dis_;
            }
            else
            {
                // 在visitedSet中存在，说明已经被计算过了，无序重复计算，主要适用于无向图。
                if (visitedSet.find(vecIt->node_) != visitedSet.end())
                {
                    continue;
                }
                dis[vecIt->node_] = std::min(dis[vecIt->node_], dis[minIt->first] + vecIt->dis_);
            }
        }

        visitedSet.insert(minIt->first);
    }

    for (auto &x : dis)
    {
        result.push_back({x.first, x.second});
    }
}
