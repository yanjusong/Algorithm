#ifndef HASH_TABLE_H_20190521
#define HASH_TABLE_H_20190521

#include <iostream>
#include <vector>

template <typename K>
using HashFunc = unsigned int (*)(const K &x);

template <class K, class T>
class HashTable
{
    friend class TestHashTable;

private:
    struct HNode
    {
        HNode(const K &key, const T &val) : key_(key), val_(val), next_(NULL) {}
        K key_;
        T val_;
        HNode *next_;
    };

public:
    HashTable(HashFunc<K> hashFunc, float factor = 0.75)
        : hashFunc_(hashFunc), factor_(factor), itemNum_(0)
    {
        items_ = std::vector<HNode *>(128, NULL);
    }

    ~HashTable()
    {
        destroy(items_);
    }

    void insert(const K &key, const T &val)
    {
        if ((itemNum_ + 1) > static_cast<int>(items_.size() * factor_))
        {
            rehash();
        }

        if (insert(key, val, items_))
        {
            ++itemNum_;
        }
    }

    bool get(const K &key, T &val)
    {
        int keyIndex = hashFunc_(key) % items_.size();
        HNode *keyNode = items_[keyIndex];

        while (keyNode)
        {
            if (keyNode->key_ == key)
            {
                val = keyNode->val_;
                return true;
            }

            keyNode = keyNode->next_;
        }

        return false;
    }

    void remove(const K &key)
    {
        int keyIndex = hashFunc_(key) % items_.size();
        HNode preNode((K()), (T()));
        preNode.next_ = items_[keyIndex];
        HNode *p = &preNode;

        while (p->next_)
        {
            if (p->next_->key_ == key)
            {
                HNode *deletedNode = p->next_;
                p->next_ = p->next_->next_;
                --itemNum_;
                delete deletedNode;
                break;
            }

            p = p->next_;
        }

        items_[keyIndex] = preNode.next_;
    }

    T &operator[](const K &key)
    {
        int keyIndex = hashFunc_(key) % items_.size();
        HNode *keyNode = items_[keyIndex];

        while (keyNode)
        {
            if (keyNode->key_ == key)
            {
                return (keyNode->val_);
            }

            keyNode = keyNode->next_;
        }

        insert(key, T());
        return operator[](key);
    }

private:
    void rehash()
    {
        int oldLen = items_.size();
        std::vector<HNode *> items = std::vector<HNode *>(static_cast<int>(oldLen * 1.5));
        for (int i = 0; i < oldLen; ++i)
        {
            HNode *keyNode = items_[i];
            while (keyNode)
            {
                insert(keyNode->key_, keyNode->val_, items);
                keyNode = keyNode->next_;
            }
        }

        destroy(items_);
        items_ = items;
    }

    bool insert(const K &key, const T &val, std::vector<HNode *> &items)
    {
        int keyIndex = hashFunc_(key) % items.size();
        HNode *keyNode = items[keyIndex];
        if (!keyNode)
        {
            items[keyIndex] = new HNode(key, val);
        }
        else
        {
            while (true)
            {
                if (keyNode->key_ == key)
                {
                    keyNode->val_ = val;
                    return false;
                }

                if (keyNode->next_)
                {
                    keyNode = keyNode->next_;
                }
                else
                {
                    break;
                }
            }
            keyNode->next_ = new HNode(key, val);
        }

        return true;
    }

    void destroy(std::vector<HNode *> &items)
    {
        int len = items.size();
        for (int i = 0; i < len; ++i)
        {
            HNode *keyNode = items[i];
            while (keyNode)
            {
                HNode *deletedNode = keyNode;
                keyNode = keyNode->next_;
                delete deletedNode;
            }
        }
    }

private:
    HashFunc<K> hashFunc_;
    float factor_;
    std::vector<HNode *> items_;
    int itemNum_;
};

#endif // !HASH_TABLE_H_20190521
