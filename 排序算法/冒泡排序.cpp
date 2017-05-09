#include <stdio.h>

int bubbleSort(int *, int );
void swap(int *, int *);

void swap(int *x, int *y)
{
    int tmp = *x;    
    *x = *y;
    *y = tmp;
}

int bubbleSort(int *nums, int length)
{
    if(!nums || length <= 0) {
        return -1;
    }
    
    for(int i = 0; i < length - 1; ++i) {
        for(int j = 0; j < length - i - 1; ++j) {
            // 前数比后数大则交换，每一次遍历确定一个元素的位置
            if(nums[j] > nums[j + 1]) {
                swap(&nums[j], &nums[j + 1]);
            }
        }
    }
    
    return 1;
}

int main(int argc, char *argv[])
{
    int nums[] = {12, 4, 0, 4, 18, 90, 32};
    if( bubbleSort(nums, sizeof(nums)/sizeof(int)) ) {
        for(int i = 0; i < sizeof(nums)/sizeof(int); ++i) {
            printf("%d ", nums[i]);
        }
        printf("\n");
    }
    return 0;
}






