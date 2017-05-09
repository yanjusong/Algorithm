#include <stdio.h>

int selectSort(int *, int );
int swap(int *, int *);

int selectSort(int *nums, int length)
{
    if(!nums || length <= 0) {
        return -1;
    }

    for(int i = 0; i < length - 1; ++i) {
        int smallIndex = i;
        for(int j = i + 1; j < length; ++j) {
            if(nums[j] < nums[smallIndex]) {
                smallIndex = j;
            }
        }
        if(smallIndex != i) {
            swap(&nums[i], &nums[smallIndex]);
        }
    }

    return 1;
}

int swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int main(int argc, char const *argv[])
{
    int nums[] = {21, -2, 34, 0, 34, 90, 12};

    if( selectSort(nums, sizeof(nums)/sizeof(int)) ) {
        for(int i = 0; i < sizeof(nums)/sizeof(int); ++i) {
            printf("%d ", nums[i]);
        }
        printf("\n");
    }
    return 0;
}
