#include <stdio.h>
#include <stdlib.h>

/*
 * @brief: 求数据的最大位数
 */
static int maxbit(int *data, size_t n)
{
    int maxData = data[0];
    for (int i = 1; i < n; ++i)
    {
        if (maxData < data[i])
            maxData = data[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        maxData /= 10;
        ++d;
    }
    return d;
}

int radixsort(int *nums, size_t n)
{
    if (!nums)
        return -1;

    int d = maxbit(nums, n);
    int i, j, k;
    int radix = 1;

    int *tmp = (int *)malloc(sizeof (int) * n);
    int *count = (int *)malloc(sizeof (int) * 10); /* 计数器 */

    for (i = 1; i <= d; i++) /* 进行d次排序 */
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; /* 每次分配前清空计数器 */
        for (j = 0; j < n; j++)
        {
            k = (nums[j] / radix) % 10; /* 统计每个桶中的记录数 */
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; /* 将tmp中的位置依次分配给每个桶 */
        for (j = n - 1; j >= 0; j--) /* 将所有桶中记录依次收集到tmp中 */
        {
            k = (nums[j] / radix) % 10;
            tmp[count[k] - 1] = nums[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) /* 将临时数组的内容复制到data中 */
            nums[j] = tmp[j];
        radix = radix * 10;
    }

    free(tmp);
    free(count);

    return 0;
}
