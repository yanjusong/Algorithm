#include <iostream>
#include <vector>
using namespace std;

typedef std::vector<int> Vec;
typedef std::vector<Vec> Result;

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void getAllPermutation(int start, int end, Vec &nums, Result &result)
{
    if (start == end) 
    {
        result.push_back(nums);
        return;
    }

    // 假设start为0，可以理解为
    // 1. 以此把第i个元素换到第一个位置来(第一个swap)
    // 2. 对第一个元素后面的元素做全排列
    // 3. 恢复第i个元素的原始位置
    for (int i = start; i < end; ++i) 
    {
        // swap 
        swap(&nums[i], &nums[start]);

        getAllPermutation(start + 1, end, nums, result);

        // swap again
        swap(&nums[i], &nums[start]);
    }
}

Result getAllPermutation(Vec &nums)
{
    Result result;
    int len = nums.size();

    getAllPermutation(0, len, nums, result);

    return result;
}

void printResult(const Result &result)
{
    cout << "[" << endl;
    for (auto &nums : result) 
    {
        cout << "   ( ";
        for (auto x : nums)
        {
            cout << x << " ";
        }
        cout << ")\n";
    }
    cout << "]" << endl;
}

int main()
{
    // case 1:
    {
        cout << "case 1:" << endl;
        Vec nums;
        Result result = getAllPermutation(nums);
        printResult(result);
        cout << endl;
    }

    // case 2:
    {
        cout << "case 2:" << endl;
        Vec nums = {1,2,3};
        Result result = getAllPermutation(nums);
        printResult(result);
        cout << endl;
    }

    // case 3:
    {
        cout << "case 3:" << endl;
        Vec nums = {1,2,3,4};
        Result result = getAllPermutation(nums);
        printResult(result);
        cout << endl;
    }

    return 0;
}
