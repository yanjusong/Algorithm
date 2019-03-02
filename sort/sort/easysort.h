#ifndef EASY_SORT_H_20181210
#define EASY_SORT_H_20181210

#ifdef __cplusplus
extern "C" {
#endif

int bubblesort(int *nums, size_t n);
int quicksort(int *nums, size_t n);
int insertsort(int *nums, size_t n);
int mergesort(int *nums, size_t n);
int heapsort(int *nums, size_t n);
int selectsort(int *nums, size_t n);
int shellsort(int *nums, size_t n);
int radixsort(int *nums, size_t n)

#ifdef __cplusplus
}
#endif

#endif // !EASY_SORT_H_20181210
