#ifndef PRIORITY_QUEUE_H_20190522
#define PRIORITY_QUEUE_H_20190522

#include <vector>

// priority queue
class PQ
{
public:
    template<typename T>
    static void makeHeap(std::vector<T> &items)
    {
        int len = items.size();
        for (int i = (len >> 1) - 1; i >= 0; --i)
        {
            siftDown(items, i, len - 1);
        }
    }

    template<typename T>
    static void popHeap(std::vector<T> &items)
    {
        int len = items.size();
        if (len <= 1)
        {
            return;
        }

        std::swap(items[0], items[len - 1]);
        siftDown(items, 0, len - 2);
    }

    template<typename T>
    static void pushHeap(std::vector<T> &items, const T &x)
    {
        items.push_back(x);
        siftUp(items, items.size() - 1);
    }

    template<typename T>
    static bool isHeap(std::vector<T> &items)
    {
        int len = items.size();
        int left, right;
        for (int i = 0; i <= (len >> 1) - 1; ++i)
        {
            left = (i << 1) + 1;
            right = (i << 1) + 2;

            if (left < len && items[left] < items[i])
            {
                return false;
            }

            if (right < len && items[right] < items[i])
            {
                return false;
            }
        }

        return true;
    }

private:
    template<typename T>
    static void siftDown(std::vector<T> &items, int start, int end)
    {
        int dad = start;
        int son = (dad << 1) + 1;

        while (son <= end)
        {
            if (son + 1 <= end && items[son + 1] < items[son])
            {
                ++son;
            }

            if (items[dad] <= items[son])
            {
                break;
            }

            std::swap(items[dad], items[son]);
            dad = son;
            son = (dad << 1) + 1;
        }
    }

    template<typename T>
    static void siftUp(std::vector<T> &items, int idx)
    {
        int son = idx;
        int dad = (son - 1) >> 1;

        while (dad >= 0 && son != 0)
        {
            if (items[dad] < items[son])
            {
                break;
            }

            std::swap(items[dad], items[son]);
            son = dad;
            dad = (son - 1) >> 1;
        }
    }
};

#endif // !PRIORITY_QUEUE_H_20190522
