#include <stdio.h>
#include <stdlib.h> //malloc

int mergeSort(int *, int );
void mergeSort(int *, int , int );
void merge(int *, int , int , int );

void merge(int *nums, int low, int mid, int high)
{
	//复制到临时数组
	int *tmp = (int *)malloc( sizeof(int)*(high - low + 1) );
	for(int i = 0, j = low; i < (high - low + 1); ) {
		tmp[i++] = nums[j++];
	}
	
	int i = 0;
	int j = mid - low + 1;
	int cur = low;
	while(i <= mid - low && j <= high - low) {
		if(tmp[i] < tmp[j]) {
			nums[cur++] = tmp[i++];
		} else {
			nums[cur++] = tmp[j++];
		}
	}

	while(i <= mid - low) {
		nums[cur++] = tmp[i++];
	}
	
	while(j <= high - low) {
		nums[cur++] = tmp[j++];
	}
	
	free(tmp);
}

int mergeSort(int *nums, int length)
{
	if(!nums || length <= 0) {
		return -1;
	}
	
	mergeSort(nums, 0, length - 1);
	return 1;
}

void mergeSort(int *nums, int low, int high)
{
	if(low < high) {
		int mid = (low + high)/2;
		mergeSort(nums, low, mid);
		mergeSort(nums, mid + 1, high);
		merge(nums, low, mid, high);
	}
}

int main(int argc, char *argv[])
{
	int nums[] = {2, -10, 5, 10, -10, 23, 12};
	if( mergeSort(nums, sizeof(nums)/sizeof(int)) ) {
		for(int i = 0; i < sizeof(nums)/sizeof(int); ++i) {
			printf("%d ", nums[i]);
		}
		printf("\n");
	}
	return 0;
}