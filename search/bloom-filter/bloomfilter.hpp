#ifndef BLOOM_FILTER_H_20190519
#define BLOOM_FILTER_H_20190519

#include <iostream>
#include <vector>

template <typename T>
using HashFunc = unsigned int (*)(const T &x);

template <class T>
class BloomFilter
{
public:
    BloomFilter(int tableSize, int mapTimes, HashFunc<T> hashFunc)
        : mapTimes_(mapTimes), hashFunc_(hashFunc)
    {
        table_.resize(tableSize);
        for (int i = 0; i < tableSize; ++i)
        {
            table_[i] = false;
        }
    }

    void insert(const T &x)
    {
        unsigned int hashRes = hashFunc_(x);
        for (int i = 0; i < mapTimes_; ++i)
        {
            table_[(hashRes + getSeed(i)) % table_.size()] = true;
        }
    }

    bool exist(const T &x)
    {
        unsigned int hashRes = hashFunc_(x);
        for (int i = 0; i < mapTimes_; ++i)
        {
            if (table_[(hashRes + getSeed(i)) % table_.size()] == false)
            {
                return false;
            }
        }
        return true;
    }

private:
    unsigned int getSeed(unsigned int hashIndex)
    {
        std::string seed = "13";
        for (int i = 0; i < hashIndex; ++i)
        {
            seed += (i % 2 == 0) ? "1" : "3";
        }

        return atoi(seed.c_str());
    }

private:
    HashFunc<T> hashFunc_;
    std::vector<bool> table_;
    int mapTimes_;
};

#endif // !BLOOM_FILTER_H_20190519
