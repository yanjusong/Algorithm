#ifndef DEQUE_H_20190101
#define DEQUE_H_20190101

#include <stdlib.h>

typedef struct Deque Deque;
typedef struct Item Item;

#define get_node(type) \
    (type *)malloc(sizeof(type))

// TODO:

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

Item *new_item(size_t len);

#endif // !DEQUE_H_20190101
