#include <stdio.h>

int insertsort(int *nums, size_t n)
{
    int i, j, tmp;

    if (!nums)
        return -1;

    for (i = 1; i < n; ++i) {
        tmp = nums[i];
        for (j = i - 1; j >= 0 && nums[j] > tmp; --j)
            nums[j + 1] = nums[j];
        nums[j + 1] = tmp;
    }

    return 0;
}
