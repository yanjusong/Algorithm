#include <stdio.h>

void qksort(int *nums, int start, int end)
{
    int soldier, left, right;

    if (start >= end)
        return;

    soldier = nums[end];
    left = start;
    right = end;

    while (left < right) {
        while (left < right && nums[left] < soldier) ++left;
        nums[right] = nums[left];

        while (left < right && nums[right] >= soldier) --right;
        nums[left] = nums[right];
    }

    nums[left] = soldier;

    qksort(nums, start, left - 1);
    qksort(nums, left + 1, end);
}

int quicksort(int *nums, size_t n)
{
    if (!nums)
        return -1;

    qksort(nums, 0, n - 1);
    return 0;
}
