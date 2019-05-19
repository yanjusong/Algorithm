#include "skiptable.hpp"

#include <cassert>

void testInsert(SkipTable<int, int> &st, int x)
{
    printf("\nafter insert %d\n", x);
    st.insert(x, x);
    st.print();
}

void testRemove(SkipTable<int, int> &st, int x)
{
    printf("\nafter remove %d\n", x);
    st.remove(x);
    st.print();
}

void testFind(SkipTable<int, int> &st, int x, bool expected)
{
    int val = -1;
    bool ok = st.find(x, val);
    assert(ok == expected);
    printf("\nafter find %d\n", x);
    if (ok)
    {
        printf("key:%d, value:%d\n", x, val);
    }
    else
    {
        printf("key:%d, value:not found\n", x);
    }
}

#define TEST_INSERT(x) testInsert(st, x)
#define TEST_REMOVE(x) testRemove(st, x)
#define TEST_FIND(x, e) testFind(st, x, e)

// g++ -std=c++11 test__all.cpp -o a && ./a
int main()
{
    SkipTable<int, int> st(4);
    st.print();

    TEST_FIND(0, false);
    TEST_FIND(1, false);

    TEST_INSERT(0);
    TEST_INSERT(2);
    TEST_INSERT(3);
    TEST_INSERT(5);
    TEST_INSERT(4);
    TEST_INSERT(0);
    TEST_INSERT(0);

    TEST_FIND(0, true);
    TEST_FIND(1, false);

    TEST_REMOVE(0);
    TEST_REMOVE(4);
    TEST_REMOVE(3);
    TEST_REMOVE(6);
    TEST_REMOVE(2);
    TEST_REMOVE(5);
    TEST_REMOVE(0);
    TEST_REMOVE(0);

    TEST_FIND(0, false);
    TEST_FIND(1, false);

    return 0;
}
