#include "deque.h"

#include <stdio.h>

int main()
{
    int i, v, x;
    int *p, *px;
    Deque *dq = new_deque();

    printf("Testing front and pop_front:\n");
    for (i = 0; i < 5; ++i) {
        push_back(dq, i + 1, int);
    }
    printf("after push_back 5 items, deque size=%d\n", size(dq));
    for (i = 0; i < 5; ++i) {
        v = front(dq, int);
        pop_front(dq);
        printf("%d ", v);
    }
    printf("\n");
    printf("after pop_front 5 items, deque size=%d\n", size(dq));

    printf("\nTesting back and pop_back:\n");
    for (i = 0; i < 5; ++i) {
        push_front(dq, i + 1, int);
    }
    printf("after push_front 5 items, deque size=%d\n", size(dq));
    for (i = 0; i < 5; ++i) {
        v = back(dq, int);
        pop_back(dq);
        printf("%d ", v);
    }
    printf("\n");
    printf("after pop_back 5 items, deque size=%d\n", size(dq));

    printf("\nTesting clear:\n");
    x = 67890;
    p = &x;
    push_back(dq, p, int *);
    px = back(dq, int *);
    printf("*px=%d\n", *px);

    printf("after pop_back 1 item, deque size=%d\n", size(dq));
    clear(dq);
    printf("after clear, deque size=%d\n", size(dq));

    delete_deque(dq);

    getchar();
    return 0;
}