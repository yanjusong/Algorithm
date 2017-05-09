#include <stdio.h>

int quickSort(int *, int );
void quickSort(int *, int, int );
int partition(int *, int, int );

int quickSort(int *nums, int length) 
{
    if(!nums && length <= 0) {
        return -1;
    }
    else if(length == 1) {
        return 1;
    }
    
    quickSort(nums, 0, length - 1);
    return 1;
}

void quickSort(int *nums, int low, int high) 
{
    if(low < high) {
        int pivot = partition(nums, low, high);
        quickSort(nums, low, pivot);
        quickSort(nums, pivot + 1, high);
    }
}

int partition(int *nums, int low, int high)
{
    int tmp = nums[low];
    while(low < high) {
        while(low < high && nums[high] >= tmp) --high;
        nums[low] = nums[high];
        
        while(low < high && nums[low] <= tmp) ++low;
        nums[high] = nums[low];
    }
    nums[low] = tmp;
    return low;
}

int main(int argc, char *argv[])
{
    int nums[] = {23, 5, 10, 2, 30, 21, 23, 23};
    if( quickSort(nums, sizeof(nums)/sizeof(int)) ) {
        for(int i = 0; i < sizeof(nums)/sizeof(int); ++i) {
            printf("%d ", nums[i]);
        }
        printf("\n");
    }
    return 0;
}
