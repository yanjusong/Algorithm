#include <stdio.h>

int shellSort(int *, int );

int shellSort(int *nums, int length)
{
    if(!nums || length <= 0) {
        return -1;
    }

    int d = length/2;

    while(d > 0) {
        for(int i = 0; i < d; ++i) {
            for(int j = i + d; j < length; j += d) {
                int tmp = nums[j];
                int k = j;
                while(k >= 0 && nums[k] >= tmp) {
                    nums[k] = nums[k - d];
                    k -= d;
                }
                nums[k + d] = tmp; 
             }
            
        }
        d /= 2;
    }

    return 1;
}

int main(int argc, char const *argv[])
{
    int nums[] = {80, 93, 60, 12, 42, 30, 68, 85, 10};
    if( shellSort(nums, sizeof(nums)/sizeof(int)) ) {
        for(int i = 0; i < sizeof(nums)/sizeof(int); ++i) {
            printf("%d ", nums[i]);
        }
        printf("\n");
    }
    return 0;
}