#include <stdio.h>

int heapSort(int *, int );
int heapAdjust(int *, int , int );
void swap(int *, int * );
void print(int *, int);

int main(int argc, char *argv[]) 
{
    int nums[] = {16, 7, 3, 20, 17, 8};
    if( heapSort(nums, sizeof(nums)/sizeof(int)) ) {
        print(nums, 6);
    }
    return 0;
}

int heapSort(int *nums, int length) 
{
    if(nums == NULL || length <= 0) {
        return -1;
    }
    
    if(length == 1) {
        return 1;
    }
    
    // 建堆
    for(int i = length/2 - 1; i >= 0; --i) {
        heapAdjust(nums, i, length);
    }
    
    // 堆头堆尾交换 + 调整堆
    for(int i = 0; i < length - 1; ++i) {
        // 交换
        swap(&nums[0], &nums[length - i - 1]);
        // 调整
        heapAdjust(nums, 0, length - i - 1);
    }
    
    return 1;
}

int heapAdjust(int *nums, int index, int length)
{
    int tmp = nums[index];
    
    int i = index;
    int j = i;
    
    while(i < length) {
        int bigOne = i;
        if(i*2 + 1 < length && tmp < nums[i*2 + 1]) {
            bigOne = i*2 + 1;
        }
        if(i*2 + 2 < length && tmp < nums[i*2 + 2]) {
            if(bigOne == i) {
                bigOne = i*2 + 2;
            } else if(nums[i*2 + 2] > nums[i*2 + 1]) {
                bigOne = i*2 + 2;
            }
        }
        
        if(bigOne == i) {
            break;
        }
        
        nums[i] = nums[bigOne];
        j = i;
        i = bigOne;
    }
    nums[i] = tmp;
    
    return 1;
}

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void print(int *nums, int length) 
{
    for(int i = 0; i < length; ++i)
        printf("%d ", nums[i]);
    printf("\n");
}
