#include <stdio.h>

static void msort(int *nums, int start, int end)
{
    int mid, i;
    int *lbuf = NULL, *rbuf = NULL, *pl, *pr;
    int llen, rlen;

    if (start >= end)
        return;

    mid = (start + end) >> 1;
    msort(nums, start, mid);
    msort(nums, mid + 1, end);

    llen = mid - start + 1;
    rlen = end - mid;

    if (llen) {
        lbuf = (int *)malloc(sizeof(int) * llen);
        memcpy((void *)lbuf, (void *)(nums + start), sizeof(int) * llen);
    }

    if (rlen) {
        rbuf = (int *)malloc(sizeof(int) * rlen);
        memcpy((void *)rbuf, (void *)(nums + mid + 1), sizeof(int) * rlen);
    }

    i = start;
    pl = lbuf;
    pr = rbuf;
    while (llen > 0 && rlen > 0) {
        if (pl[0] > pr[0]) {
            nums[i++] = pr[0];
            ++pr;
            --rlen;
        } else {
            nums[i++] = pl[0];
            ++pl;
            --llen;
        }
    }

    while (llen) {
        nums[i++] = pl[0];
        ++pl;
        --llen;
    }

    while (rlen) {
        nums[i++] = pr[0];
        ++pr;
        --rlen;
    }

    if (lbuf)
        free(lbuf);
    if (rbuf)
        free(rbuf);
}

int mergesort(int *nums, size_t n)
{
    if (!nums)
        return -1;

    msort(nums, 0, n - 1);
    return 0;
}
