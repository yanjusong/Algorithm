#include <stdio.h>

static void swap(int *a, int *b)
{
    *a ^= *b ^= *a ^= *b;
}

int bubblesort(int *nums, size_t n)
{
    int i, j;

    if (!nums)
        return -1;

    for (i = n - 1; i > 0; --i) {
        for (j = 0; j < i; ++j) {
            if (nums[j] > nums[j + 1]) {
                swap(&nums[j], &nums[j + 1])
            }
        }
    }

    return 0;
}
