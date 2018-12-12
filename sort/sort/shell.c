#include <stdio.h>

int shellsort(int *nums, size_t n)
{
    int gap, i, j, tmp;

    if (!nums)
        return -1;

    for (gap = n >> 1; gap > 0; gap >>= 1) {
        for (i = gap; i < n; ++i) {
            tmp = nums[i];
            for (j = i - gap; j >= 0 && nums[j] > tmp; j -= gap)
                nums[j + gap] = nums[j];
            nums[j + gap] = tmp;
        }
    }
}
