#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &nums, int start, int end)
{
    int left = start;
    int right = end;
    int mid = nums[end];

    while (left < right) {
        while (left < right && nums[left] < mid) ++left;
        nums[right] = nums[left];

        while (left < right && nums[right] >= mid) --right;
        nums[left] = nums[right];
    }

    nums[left] = mid;

    return left;
}


int getKth(vector<int> &nums, int start, int end, int k)
{
    int len = nums.size();
    int partitionIndex = partition(nums, start, end);
    if (partitionIndex == k) 
        return nums[partitionIndex];
    
    if (partitionIndex - 1 >= start && k <= partitionIndex - 1) 
        return getKth(nums, start, partitionIndex - 1, k);
    if (partitionIndex + 1 <= end && k >= partitionIndex + 1) 
        return getKth(nums, partitionIndex + 1, end, k);

    return -1;
}

bool getKth(vector<int> &nums, int k, int &value)
{
    int len = nums.size();
    if (len == 0 || k <= 0 || k > len) 
        return false;

    value = getKth(nums, 0, len - 1, k - 1);
    return true;
}

void printVec(const vector<int> &vec)
{
    for (auto x : vec) {
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    for (int i = -1; i < 8; ++i) {
        vector<int> nums{3,4,5,1,2,6};
        int value = -1;
        cout << "find " << i << "th: " << getKth(nums, i, value) 
             << ", value:" << value << endl;
    }

    return 0;
}
