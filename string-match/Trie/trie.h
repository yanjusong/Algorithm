#ifndef TIRE_TREE_H_20190228
#define TIRE_TREE_H_20190228

#include <map>
#include <vector>

struct TrieNode;
typedef unsigned char Key;
typedef std::map<Key, TrieNode*> ChildList;
typedef std::map<Key, TrieNode*>::iterator ChildListIt;
typedef std::vector<TrieNode *> TrieVec;
typedef std::string String;

struct TrieNode
{
    Key key_;
    ChildList childList_;
    int cnt_;

    TrieNode(const Key &k) : key_(k), cnt_(0) {}
};

struct TrieTree
{
  public:
    TrieTree() : root_(new TrieNode(0)) 
    {
        root_->cnt_ = -1;
    }

    ~TrieTree()
    {
        clear(root_);
    }

    void addString(const String& str)
    {
        size_t len = str.size();
        TrieNode *root = root_;

        for (size_t i = 0; i < len; ++i) {
            root = insert(root, str[i]);
        }

        if (len > 0)
            ++root->cnt_;
    }

    bool findString(const String& str)
    {
        size_t len = str.size();
        TrieNode *root = root_;

        for (size_t i = 0; i < len; ++i) {
            root = find(root, str[i]);
            if (!root)
                return false;
        }

        return (len > 0 && root && root->cnt_ > 0);
    }

    bool delString(const String& str)
    {
        TrieVec trieVec;
        size_t len = str.size();
        TrieNode *root = root_;
        trieVec.push_back(root);

        for (size_t i = 0; i < len; ++i) {
            root = find(root, str[i]);
            trieVec.push_back(root);

            if (!root)
                return false;
        }

        bool bRet = (len > 0 && root && root->cnt_ > 0);
        if (bRet) {
            --root->cnt_;
        }

        for (size_t i = trieVec.size() - 1; i > 0; --i) {
            /* 当前结点是另外一个字符串的终点，不能继续删除 */
            if (trieVec[i]->cnt_ > 0 && trieVec[i]->childList_.size() > 0) { 
                break;
            } else {
                trieVec[i - 1]->childList_.erase(trieVec[i]->key_);
                delete trieVec[i];
                trieVec[i] = NULL;

                /* 当前结点是父结点的其中一个孩子结点，不能继续删除父结点 */
                if (trieVec[i - 1]->childList_.size() > 0)
                    break;
            }
        }

        return bRet;
    }

  private:
    TrieNode* insert(TrieNode *root, const Key &k)
    {
        TrieNode *node = NULL;
        ChildListIt it = root->childList_.find(k);

        if (it == root->childList_.end()) {
            node = new TrieNode(k);
            (root->childList_)[k] = node;
        } else {
            node = it->second;
        }

        return node;
    }

    TrieNode* find(TrieNode *root, const Key &k)
    {
        TrieNode *node = NULL;
        ChildListIt it = root->childList_.find(k);

        if (it != root->childList_.end()) {
            node = it->second;
        }

        return node;
    }

    void clear(TrieNode *node)
    {
        if (!node)
            return;

        for (ChildListIt it = node->childList_.begin(); it != node->childList_.end(); ++it) {
            clear(it->second);
        }
        delete node;
    }

    TrieNode *root_;
};

#endif // !TIRE_TREE_H_20190228
