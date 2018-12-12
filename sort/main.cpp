#include <QCoreApplication>
#include <QTime>
#include <QElapsedTimer>
#include <QDebug>

#include "easysort.h"

#define MAX_NUM 100000
int nums[MAX_NUM];

struct InitSD
{
    InitSD()
    {
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    }
};

void genRandomNums(int *nums, size_t n)
{
    static InitSD sisd;
    for (int i = 0; i < n; ++i)
        nums[i] = qrand();
}

int isOrderArray(int *nums, size_t n)
{
    if (!nums)
        return -1;

    for (int i = 0; i < n - 1; ++i) {
        if (nums[i] > nums[i + 1])
            return 0;
    }
    return 1;
}

void printNums(int *nums, size_t n)
{
    if (!nums) {
        printf("nums is NULL\n");
        return;
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

typedef int (*SortFunc)(int *, size_t);

int performanceTest(int *randomNums, int len, SortFunc func)
{
    if (!randomNums)
        return -1;

    int *nums = new int[len];
    memcpy((void *)nums, (void *)randomNums, sizeof(int) * len);

    QElapsedTimer et;
    et.start();

    func(nums, len);
    int isSorted = isOrderArray(nums, len);
    int cost = et.elapsed();

    //printNums(randomNums, len);
    //printNums(nums, len);

    delete nums;
    return isSorted ? cost : -1;
}

void test(SortFunc func, const char *desc)
{
    int cost = performanceTest(nums, MAX_NUM, func);
    printf("算法:%s, 数据:%d, 耗时:%dms\n", desc, MAX_NUM, cost);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    genRandomNums(nums, MAX_NUM);

    test(bubblesort, "冒泡排序");
    test(selectsort, "选择排序");
    test(insertsort, "插入排序");
    test(shellsort,  "希尔排序");
    test(mergesort,  "归并排序");
    test(quicksort,  "快速排序");
    test(heapsort,   "堆排序");

    return a.exec();
}
