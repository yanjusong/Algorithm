#include <stdio.h>

#define ERROR -1
#define FAIL -2

int binarySearch(int *nums, int length, int key)
{
	if(!nums || length <= 0) {
		return ERROR;
	}
	
	int low = 0;
	int high = length - 1;
	int mid;
	while(low <= high) {
		mid = (low + high)/2;
		if(nums[mid] == key) {
			return mid;
		} else if(nums[mid] > key) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	
	return FAIL;
}

int main(int argc, char *argv[])
{
	int nums[] = {1,2,3,4,5,6,7,8,9,10};
	
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 1) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 2) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 3) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 4) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 5) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 6) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 7) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 8) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 9) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 10) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 11) );
	printf( "%d \n", binarySearch(nums, sizeof(nums)/sizeof(int), 0) );
	printf( "%d \n", binarySearch(nums, -3, 0) );
	return 0;
}