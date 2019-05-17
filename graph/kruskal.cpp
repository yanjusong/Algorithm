#include "graph.hpp"

#include <algorithm>
#include <map>

struct NodePart
{
    std::set<GNode *> nodes_;
    bool contains(GNode *root)
    {
        return nodes_.find(root) != nodes_.end();
    }

    NodePart& operator+=(const NodePart &rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        for (auto &x : rhs.nodes_)
        {
            nodes_.insert(x);
        }

        return *this;
    }
};

struct NodePair
{
    GNode *begin_;
    GNode *end_;
    int dis_;
    NodePair(GNode *begin, GNode *end, int dis = 0) : begin_(begin), end_(end), dis_(dis) {}

    bool operator<(const NodePair &rhs) const
    {
        return dis_ > rhs.dis_;
    } 
};

static void printEdges(const std::vector<NodePair> &edges)
{
    for (const auto &x : edges)
    {
        printf("%d->%d [%d]\n", x.begin_->getVal(), x.end_->getVal(), x.dis_);
    }
    printf("\n\n");
}

static void printParts(const std::vector<NodePart> &parts)
{
    for (const auto &x : parts)
    {
        printf("[ ");
        for (const auto &i : x.nodes_)
        {
            printf("%d ", i->getVal());
        }
        printf("]\n");
    }
    printf("\n\n");
}

GNode* GNode::kruskal()
{
    std::set<GNode *> nodes = getAllNodes();
    std::vector<NodePart> parts;
    std::vector<NodePair> edges;
    std::map<GNode *, GNode *> hashTable;

    for (auto &x : nodes) 
    {
        NodePart part;
        part.nodes_.insert(x);
        parts.push_back(part);

        for (auto &i : x->neighbors_)
        {
            edges.push_back(NodePair(x, i.node_, i.dis_));
        }

        hashTable[x] = new GNode(x->val_);
    }

    std::make_heap(edges.begin(), edges.end());

    while (true)
    {
        // for log
        // printEdges(edges);
        // printParts(parts);

        if (edges.size() == 0 || parts.size() == 1)
        {
            break;
        }

        NodePair minNodePair = edges[0];
        int beginInPartsIndex = -1;
        int endInPartIndex = -1;

        for (int i = 0; i < parts.size(); ++i)
        {
            if (beginInPartsIndex != - 1 && endInPartIndex != -1)
            {
                break;
            }

            if (parts[i].contains(minNodePair.begin_))
            {
                beginInPartsIndex = i;
            }

            if (parts[i].contains(minNodePair.end_))
            {
                endInPartIndex = i;
            }
        }


        if (beginInPartsIndex != - 1 
            && endInPartIndex != -1 
            && beginInPartsIndex != endInPartIndex)
        {
            if (beginInPartsIndex > endInPartIndex)
            {
                std::swap(beginInPartsIndex, endInPartIndex);
            }

            parts[beginInPartsIndex] += parts[endInPartIndex];

            if (endInPartIndex != parts.size() - 1)
            {
                std::swap(parts[endInPartIndex], parts[parts.size() - 1]);
            }
            parts.pop_back();

            hashTable[minNodePair.begin_]->createOrChangeNeighbor(hashTable[minNodePair.end_], minNodePair.dis_);
            if (minNodePair.end_->hasNeighbor(minNodePair.begin_))
            {
                hashTable[minNodePair.end_]->createOrChangeNeighbor(hashTable[minNodePair.begin_], minNodePair.dis_);
            }
        }

        std::pop_heap(edges.begin(), edges.end());
        edges.pop_back();
    }

    return hashTable[this];
}
