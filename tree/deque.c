#include "deque.h"

#include <string.h>

Item *new_item(void *data, size_t len)
{
    Item *new_one;
    new_one = (Item *)malloc(sizeof(Item));
    if (new_one) {
        new_one->prev = new_one->next = NULL;
        new_one->dlen = len;
        new_one->data = NULL;
        if (len > 0) {
            new_one->data = malloc(len);
            if (!new_one->data) {
                free(new_one);
                new_one = NULL;
            } else {
                memcpy(new_one->data, data, len);
            }
        }
    }

    return new_one;
}

void delete_item(Item *item)
{
    if (!item)
        return;
    if (item->data)
        free(item->data);
    free(item);
}

Deque *new_deque()
{
    Deque *new_one;
    new_one = (Deque *)malloc(sizeof(Deque));

    if (new_one) {
        new_one->head = new_item(NULL, 0);
        new_one->rear = new_item(NULL, 0);
         new_one->cnt = 0;

        if (!new_one->head || !new_one->rear) {
            if (new_one->head) {
                free(new_one->head);
            }
            if (new_one->rear) {
                free(new_one->rear);
            }
            free(new_one);
            new_one = NULL;
        } else {
            new_one->head->next = new_one->rear;
            new_one->rear->prev = new_one->head;
        }
    }

    return new_one;
}

void delete_deque(Deque *dq)
{
    Item *i, *tmp;

    if (!dq)
        return;

    i = dq->head;
    while (i) {
        tmp = i->next;
        delete_item(i);
        i = tmp;
    }
}

void pop_back(Deque *dq)
{
    Item *back_item = NULL;
    Item *pre_back_item = NULL;

    if (!dq || dq->cnt == 0)
        return;

    back_item = dq->rear->prev;
    pre_back_item = back_item->prev;
    pre_back_item->next = dq->rear;
    dq->rear->prev = pre_back_item;
    --dq->cnt;

    delete_item(back_item);
}

void pop_front(Deque *dq)
{
    Item *front_item = NULL;
    Item *next_front_item = NULL;

    if (!dq || dq->cnt == 0)
        return;

    front_item = dq->head->next;
    next_front_item = front_item->next;
    dq->head->next = next_front_item;
    next_front_item->prev = dq->head;
    --dq->cnt;

    delete_item(front_item);
}

int size(Deque *dq)
{
    if (!dq)
        return 0;
    else
        return dq->cnt;
}

int is_empty(Deque *dq)
{
    return (size(dq) == 0 ? 0 : 1);
}

void clear(Deque *dq)
{
    Item *i, *tmp;
    if (!dq)
        return;

    i = dq->head->next;
    while (i != dq->rear) {
        tmp = i->next;
        delete_item(i);
        i = tmp;
    }

    dq->head->next = dq->rear;
    dq->rear->prev = dq->head;
    dq->cnt = 0;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Item *BACK(Deque *dq)
{
    if (!dq || dq->cnt == 0)
        return NULL;

    return dq->rear->prev;
}

Item *FRONT(Deque *dq)
{
    if (!dq || dq->cnt == 0)
        return NULL;

    return dq->head->next;
}

void PUSH_BACK(Deque *dq, void *data, size_t len)
{
    Item *i = NULL;
    Item *pre_rear = NULL;

    if (!dq)
        return;

    i = new_item(data, len);
    if (!i)
        return;

    int x = *((int *)data);
    int xxx = *((int *)i->data);
    pre_rear = dq->rear->prev;
    pre_rear->next = i;
    i->prev = pre_rear;
    i->next = dq->rear;
    dq->rear->prev = i;
    ++dq->cnt;
}

void PUSH_FRONT(Deque *dq, void *data, size_t len)
{
    Item *i = NULL;
    Item *next_head = NULL;

    if (!dq)
        return;

    i = new_item(data, len);
    if (!i)
        return;

    next_head = dq->head->next;
    dq->head->next = i;
    i->prev = dq->head;
    i->next = next_head;
    next_head->prev = i;
    ++dq->cnt;
}
