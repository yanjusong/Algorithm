#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void getNext(const char *p, int *next)
{
    next[0] = -1;
    int len = strlen(p);
    int i, j;

    for (j = 1; j < len; ++j) {
        for (i = next[j - 1];; i = next[i]) {
            if (p[j] == p[i + 1]) {
                next[j] = i + 1;
                break;
            }
            if (i == -1) {
                next[j] = -1;
                break;
            }
        }
    }
}

static void printArray(int *p, int len)
{
    int i;
    for (i = 0; p && i < len; ++i) {
        printf("%d ", p[i]);
    }

    printf("\n");
}

int kmpMatch(const char *str, const char *p)
{
    int lens = strlen(str);
    int lenp = strlen(p);
    int *next = (int *)malloc(sizeof(int) * lenp);
    int i, j;

    getNext(p, next);
    printArray(next, lenp);

    for (i = 0, j = 0; i < lens && j < lenp;) {
        if (str[i] == p[j]) {
            ++i;
            ++j;
        } else if (j == 0) {
            ++i;
        } else {
            // `p[0]...p[next[j - 1]]`和`str[i - 1 - (next[j-1] + 1)]...str[i-1]`重合
            j = next[j - 1] + 1;
        }
    }

    free(next);
    return j == lenp ? i - lenp : -1;
}