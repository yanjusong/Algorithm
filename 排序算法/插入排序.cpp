/*
 * @author yanjusong
 */
#include <stdio.h>

int insertSort(int *, int );

int insertSort(int *nums, int length)
{
    if(!nums || length <= 0) {
        return -1;
    }
    
    int tmp,j;
    for(int i = 1; i < length; ++i) {
        tmp = nums[i];
        j = i;
        // while一定循环一次以上
        while(j >= 0 && tmp <= nums[j]) {
            nums[j] = nums[--j];
        }
        nums[++j] = tmp;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int nums[] = {12, 13, 4, 56, 4, 23, 4,  -12, 9};
    if( insertSort(nums, sizeof(nums)/sizeof(int)) ) {
        for(int i = 0; i < sizeof(nums)/sizeof(int); ++i) {
            printf("%d ", nums[i]);
        }
        printf("\n");
    }
    return 0;
}
