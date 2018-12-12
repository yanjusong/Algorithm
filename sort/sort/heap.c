#include <stdio.h>

static void swap(int *a, int *b)
{
    *a ^= *b ^= *a ^= *b;
}

void mkheap(int *nums, int start, int end)
{
    int dad = start;
    int son = start * 2 + 1;

    while (son <= end) {
        if (son + 1 <= end && nums[son + 1] > nums[son])
            ++son;

        if (nums[dad] > nums[son]) {
            return;
        } else {
            swap(&nums[dad], &nums[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

int heapsort(int *nums, size_t n)
{
    int i;
    if (!nums)
        return -1;

    // 构建最大堆
    for (i = n / 2 -1; i >= 0; --i)
        mkheap(nums, i, n - 1);

    for (i = n - 1; i > 0; --i) {
        swap(&nums[0], &nums[i]);
        // 堆重调整
        mkheap(nums, 0, i - 1);
    }

    return 0;
}
