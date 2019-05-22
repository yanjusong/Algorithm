#include "priority_queue.hpp"

#include <iostream>
#include <vector>
#include <ctime>

template <typename T>
void printIsHeap(std::vector<T> &items)
{
    std::cout << "isHeap: " << (PQ::isHeap(items) ? "true" : "false") << "\n";
}

template <typename T>
void printVec(const std::vector<T> &items)
{
    int len = items.size();
    std::cout << "[";
    for (int i = 0; i < len - 1; ++i)
    {
        std::cout << items[i] << ", ";
    }
    if (len > 0)
    {
        std::cout << items[len - 1];
    }
    std::cout << "]\n";
}

// g++ -std=c++11 test__all.cpp -o a && ./a
int main()
{
    std::vector<int> nums = {2, 5, 4, 10, 7, 8, 6, 1, 0};
    printVec<int>(nums);
    printIsHeap(nums);

    PQ::makeHeap(nums);
    printVec<int>(nums);
    printIsHeap(nums);

    PQ::popHeap(nums);
    printVec<int>(nums);
    printIsHeap(nums);

    nums.pop_back();
    printVec<int>(nums);
    printIsHeap(nums);

    srand((unsigned)time(NULL));

    for (int j = 0; j < 100; ++j)
    {
        for (int i = 0; i < 1000; ++i)
        {
            int randNum = rand();
            if (randNum % 2 == 0)
            {
                int x = rand() % 1000;
                printVec<int>(nums);
                std::cout << "\nx=" << x << "\n";
                std::cout << "before pushHeap: ";
                PQ::pushHeap<int>(nums, x);
                std::cout << "after pushHeap: ";
                printVec<int>(nums);

                printIsHeap(nums);
                assert(PQ::isHeap<int>(nums));
            }
            else
            {
                std::cout << "\nbefore popHeap:\n";
                PQ::popHeap<int>(nums);
                std::cout << "\nafter popHeap:\n";
                printVec<int>(nums);

                if (nums.size() > 0)
                {
                    nums.pop_back();
                }

                std::cout << "\nafter popBack:\n";
                printVec<int>(nums);
                assert(PQ::isHeap<int>(nums));
            }
        }
    }

    return 0;
}
