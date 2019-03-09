#include <iostream>
#include <vector>
#include <climits>
using namespace std;

typedef std::vector<int> Vec;

void printVector(const Vec &nums)
{
    for (const auto &x : nums)
        cout << x << " ";
    cout << endl;
}

Vec findThePivot(const Vec &nums)
{
    Vec result;
    int len = nums.size();
    if (len <= 2)
        return result;

    Vec minNums(len, 0); /* 从右到左的最小值 */
    minNums[len - 1] = nums[len - 1];
    for (int i = len - 2; i >= 0; --i) 
    {
        if (nums[i] < minNums[i + 1])
            minNums[i] = nums[i];
        else 
            minNums[i] = minNums[i + 1];
    }

    int leftMax = nums[0];
    for (int i = 1; i < len - 1; ++i)
    {
        // not `>=`
        if (nums[i] > leftMax)
        {
            leftMax = nums[i];
            // not `<=`
            if (nums[i] < minNums[i + 1])
            {
                result.push_back(nums[i]);
            }
        }
    }

    return result;
}

int main()
{
    // case 1:
    {
        cout << "\ncase 1:\n";
        Vec nums;
        Vec result = findThePivot(nums);
        printVector(result);
    }

    // case 2:
    {
        cout << "\ncase 2:\n";
        Vec nums = {1};
        Vec result = findThePivot(nums);
        printVector(result);
    }

    // case 3:
    {
        cout << "\ncase 3:\n";
        Vec nums = {1,4};
        Vec result = findThePivot(nums);
        printVector(result);
    }

    // case 4:
    {
        cout << "\ncase 4:\n";
        Vec nums = {1,4,5};
        Vec result = findThePivot(nums);
        printVector(result);
    }

    // case 5:
    {
        cout << "\ncase 5:\n";
        Vec nums = {5,4,5};
        Vec result = findThePivot(nums);
        printVector(result);
    }

    // case 6:
    {
        cout << "\ncase 6:\n";
        Vec nums = {1,2,2,3,4,5};
        Vec result = findThePivot(nums);
        printVector(result);
    }

    return 0;
}
