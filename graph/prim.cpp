#include "graph.hpp"

#include <map>
#include <algorithm>

static GNode *getNode(std::map<GNode *, GNode *> &hash, GNode *key)
{
    if (hash.find(key) == hash.end())
    {
        hash[key] = new GNode(key->getVal());
    }

    return hash[key];
}

static GNode *makeMinGraph(GNode *root, std::map<GNode *, std::vector<GNode *>> &paths)
{
    if (!root)
    {
        return NULL;
    }

    std::map<GNode *, GNode *> hash;
    hash[root] = new GNode(root->getVal());

    for (auto &x : paths)
    {
        int len = x.second.size();
        for (int i = 1; i < len; ++i)
        {
            GNode *preNode = getNode(hash, x.second[i - 1]);
            GNode *curNode = getNode(hash, x.second[i]);

            std::set<NodeDisPair>::iterator toRightIt = x.second[i - 1]->neighbors_.find(x.second[i]);
            if (toRightIt != x.second[i - 1]->neighbors_.end())
            {
                preNode->neighbors_.insert({curNode, toRightIt->dis_});
            }

            std::set<NodeDisPair>::iterator toLeftIt = x.second[i]->neighbors_.find(x.second[i - 1]);
            if (toLeftIt != x.second[i]->neighbors_.end())
            {
                curNode->neighbors_.insert({preNode, toLeftIt->dis_});
            }
        }
    }

    return hash[root];
}

GNode *GNode::prim()
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
    std::map<GNode *, std::vector<GNode *>> paths;
    paths[this] = std::vector<GNode *>{this};

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
            bool isRepath = false;
            if (dis.find(vecIt->node_) == dis.end())
            {
                dis[vecIt->node_] = dis[minIt->first] + vecIt->dis_;
                isRepath = true;
            }
            else
            {
                // 在visitedSet中存在，说明已经被计算过了，无序重复计算，主要适用于无向图。
                if (visitedSet.find(vecIt->node_) != visitedSet.end())
                {
                    continue;
                }
                isRepath = ((dis[minIt->first] + vecIt->dis_) < dis[vecIt->node_]);
                dis[vecIt->node_] = std::min(dis[vecIt->node_], dis[minIt->first] + vecIt->dis_);
            }

            if (isRepath)
            {
                std::vector<GNode *> path(paths[minIt->first]);
                path.push_back(vecIt->node_);
                paths[vecIt->node_] = path;
            }
        }

        visitedSet.insert(minIt->first);
    }

    // for log
    // for (auto &x : paths)
    // {
    //     printf("key:%d\t", x.first->getVal());
    //     for (auto &node : x.second)
    //     {
    //         printf("%d->", node->getVal());
    //     }
    //     printf("NULL\n");
    // }

    return makeMinGraph(this, paths);
}
