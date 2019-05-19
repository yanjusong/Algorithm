#ifndef SKIPTABLE_H_20190518
#define SKIPTABLE_H_20190518

#include <iostream>
#include <vector>
#include <ctime>

template <class K, class T>
class SkipTable
{
private:
    struct STNode;
    struct Node
    {
        Node *next_;
        Node(STNode *stnode) : stnode_(stnode), next_(NULL) {}
        STNode *stnode_;
    };
    struct STNode
    {
        STNode(K key, T val, int level) : key_(key), val_(val)
        {
            for (int i = 0; i < level; ++i)
            {
                downNodes_.push_back(new Node(this));
            }
        }

        ~STNode()
        {
            for (int i = 0; i < downNodes_.size(); ++i)
            {
                delete downNodes_[i];
            }
        }

        int getLevel()
        {
            return downNodes_.size();
        }

        std::vector<Node *> downNodes_;
        K key_;
        T val_;
    };

public:
    SkipTable(int level = 4)
        : level_(level),
          head_(new STNode(K(), T(), level_)),
          rear_(new STNode(K(), T(), level_))
    {
        for (int i = 0; i < level_; ++i)
        {
            head_->downNodes_[i]->next_ = rear_->downNodes_[i];
        }
        srand((unsigned)time(NULL));
    }

    ~SkipTable()
    {
        Node *p = head_->downNodes_[0];
        while (p)
        {
            STNode *outNode = p->stnode_;
            p = p->next_;
            delete outNode;
        }
    }

    int getRandomLevel()
    {
        int level = 0;
        while (rand() % 2 && level < level_ - 1)
        {
            ++level;
        }

        return level + 1;
    }

    void insert(const K &k, const T &v)
    {
        int nodeLevel = getRandomLevel();
        STNode *node = new STNode(k, v, nodeLevel);
        int depth = level_ - nodeLevel;
        std::vector<Node **> vdownNodes;
        for (int i = 0; i < nodeLevel; ++i)
        {
            vdownNodes.push_back(&(node->downNodes_[i]));
        }
        for (int i = 0; i < depth; ++i)
        {
            vdownNodes.push_back(NULL);
        }

        Node **left = &(head_->downNodes_[level_ - 1]);
        Node **right = &(rear_->downNodes_[level_ - 1]);
        for (int i = level_ - 1; i >= 0; --i)
        {
            while (true)
            {
                if ((*left)->next_->stnode_ == rear_)
                {
                    break;
                }

                if (k > (*left)->next_->stnode_->key_)
                {
                    left = &((*left)->next_->stnode_->downNodes_[i]);
                }
                else
                {
                    right = &((*left)->next_->stnode_->downNodes_[i]);
                    break;
                }
            }

            if (vdownNodes[i] != NULL)
            {
                Node *nextLeftNode = (*left)->next_;
                (*left)->next_ = node->downNodes_[i];
                node->downNodes_[i]->next_ = nextLeftNode;
            }

            if (i != 0)
            {
                // 下移一步
                left = &((*left)->stnode_->downNodes_[i - 1]);
                right = &((*right)->stnode_->downNodes_[i - 1]);
            }
        }
    }

    void remove(const K &k)
    {
        Node **left = &(head_->downNodes_[level_ - 1]);
        Node **right = &(rear_->downNodes_[level_ - 1]);
        STNode *outNode = NULL;

        for (int i = level_ - 1; i >= 0; --i)
        {
            while (true)
            {
                if ((*left)->next_->stnode_ == rear_)
                {
                    break;
                }

                if (k > (*left)->next_->stnode_->key_)
                {
                    left = &((*left)->next_->stnode_->downNodes_[i]);
                }
                else
                {
                    right = &((*left)->next_->stnode_->downNodes_[i]);

                    if ((*right)->stnode_ != rear_ && (*right)->stnode_->key_ == k)
                    {
                        if (!outNode)
                        {
                            outNode = (*left)->next_->stnode_;
                        }
                        
                        (*left)->next_ = (*left)->next_->next_;
                    }
                    break;
                }
            }

            if (i != 0)
            {
                // 下移一步
                left = &((*left)->stnode_->downNodes_[i - 1]);
                right = &((*right)->stnode_->downNodes_[i - 1]);
            }
        }

        if (outNode)
        {
            delete outNode;
        }
    }

    bool find(const K &k, T &v)
    {
        Node **left = &(head_->downNodes_[level_ - 1]);
        Node **right = &(rear_->downNodes_[level_ - 1]);
        for (int i = level_ - 1; i >= 0; --i)
        {
            while (true)
            {
                if ((*left)->next_->stnode_ == rear_)
                {
                    break;
                }

                if (k > (*left)->next_->stnode_->key_)
                {
                    left = &((*left)->next_->stnode_->downNodes_[i]);
                }
                else
                {
                    right = &((*left)->next_->stnode_->downNodes_[i]);

                    if ((*right)->stnode_ != rear_ && (*right)->stnode_->key_ == k)
                    {
                        v = (*right)->stnode_->val_;
                        return true;
                    }
                    break;
                }
            }

            if (i != 0)
            {
                // 下移一步
                left = &((*left)->stnode_->downNodes_[i - 1]);
                right = &((*right)->stnode_->downNodes_[i - 1]);
            }
        }

        return false;
    }

    void print()
    {
        for (int i = head_->downNodes_.size() - 1; i >= 0; --i)
        {
            Node *head = head_->downNodes_[i];
            while (head)
            {
                std::cout << head->stnode_->key_ << " ";
                head = head->next_;
            }
            std::cout << "\n";
        }
    }

private:
    int level_;
    STNode *head_;
    STNode *rear_;
};

#endif // !SKIPTABLE_H_20190518
