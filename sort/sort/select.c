#include <stdio.h>

static void swap(int *a, int *b)
{
    *a ^= *b ^= *a ^= *b;
}

int selectsort(int *nums, size_t n)
{
    int i, j, minidx;

    if (!nums)
        return -1;

    for (i = 0; i < n - 1; ++i) {
        minidx = i;
        for (j = i + 1; j < n; ++j) {
            if (nums[j] < nums[minidx])
                minidx = j;
        }

        if (i != minidx)
            swap(&nums[i], &nums[minidx]);
    }

    return 0;
}
