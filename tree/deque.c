#include "deque.h"

Item *new_item(size_t len)
{
    Item *new_one;
    new_one = (Item *)malloc(sizeof(Item));
    if (new_one) {
        new_one->prev = new_one->next = NULL;
        new_one->dlen = len;
        new_one->data = malloc(len);
        if (!new_one->data) {
            free(new_one);
            new_one = NULL;
        }
    }

    return new_one;
}

Deque *new_deque()
{
    Deque *new_one;
    new_one = (Deque *)malloc(sizeof(Deque));
    if (new_one) {
        new_one->head = new_one->rear = NULL;
        new_one->cnt = 0;
    }

    return new_one;
}
