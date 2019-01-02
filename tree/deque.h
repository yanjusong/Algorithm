#ifndef DEQUE_H_20190101
#define DEQUE_H_20190101

#include <stdlib.h>

typedef struct Deque Deque;
typedef struct Item Item;

struct Deque
{
    Item *head;
    Item *rear;
    size_t cnt;
};

struct Item
{
    Item *prev;
    Item *next;
    void *data;
    size_t dlen;
};

Deque *new_deque();
void delete_deque(Deque *dq);

Item *new_item(void *data, size_t len);
void delete_item(Item *item);

#define push_back(dq, obj, type) \
    do { \
        type obj_micro = obj; \
        PUSH_BACK(dq, &obj_micro, sizeof(obj)); \
    } while (0) 

#define push_front(dq, obj, type) \
    do { \
        type obj_micro = obj; \
        PUSH_FRONT(dq, &obj_micro, sizeof(obj)); \
    } while (0) 

#define back(dq, type) \
    *((type *)(BACK(dq)->data))

#define front(dq, type) \
    *((type *)(FRONT(dq)->data))

void pop_back(Deque *dq);
void pop_front(Deque *dq);

int size(Deque *dq);
int is_empty(Deque *dq);
void clear(Deque *dq);

Item *BACK(Deque *dq);
Item *FRONT(Deque *dq);
void PUSH_BACK(Deque *dq, void *data, size_t len);
void PUSH_FRONT(Deque *dq, void *data, size_t len);

#endif // !DEQUE_H_20190101
