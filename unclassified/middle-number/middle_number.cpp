#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void printVec(const vector<int> &vec)
{
    for (auto x : vec) {
        cout << x << " ";
    }
    cout << endl;
}

double getMiddleNumber(const vector<int> nums)
{
    int len = nums.size();
    if (len == 0)
        return 0.0;
    
    int heapSize = len / 2 + 1;
    vector<int> heapVec;
    heapVec.assign(nums.begin(), nums.begin() + heapSize);
    // 构建最小堆
    make_heap(heapVec.begin(), heapVec.end(), greater<int>());

    for (int i = heapSize; i < len; ++i) {
        if (nums[i] > heapVec[0]) {
            // 把堆顶元素移到最后
            pop_heap(heapVec.begin(), heapVec.end(), greater<int>());
            // 删除最后一个元素
            heapVec.pop_back();
            // 加入新的元素
            heapVec.push_back(nums[i]);
            // 重调整堆
            push_heap(heapVec.begin(), heapVec.end(), greater<int>());
        }
    }

    double dRet = heapVec[0];
    if (len % 2 == 0) {
        // 把堆顶元素移到最后
        pop_heap(heapVec.begin(), heapVec.end(), greater<int>());
        // 删除最后一个元素
        heapVec.pop_back();
        // 重调整堆
        push_heap(heapVec.begin(), heapVec.end(), greater<int>());

        dRet += heapVec[0];
        dRet /= 2;
    }

    return dRet;
}

int main()
{
    {
        vector<int> vi{6, 1, 2, 5, 3, 4};
        cout << getMiddleNumber(vi) << endl;
    }

    {
        vector<int> vi{1, 2, 5, 3, 4};
        cout << getMiddleNumber(vi) << endl;
    }

    {
        vector<int> vi{6};
        cout << getMiddleNumber(vi) << endl;
    }

    {
        vector<int> vi{1,2};
        cout << getMiddleNumber(vi) << endl;
    }

    {
        vector<int> vi;
        cout << getMiddleNumber(vi) << endl;
    }

    return 0;
}