#include <stdio.h>

int kmpMatch(const char *str, const char *p);

void testKMPMatch(const char *str, const char *p)
{
    printf("str:%s, pattern:%s, match:%d\n", str, p, kmpMatch(str, p));
}

int main()
{
    testKMPMatch("123abababcdef45", "abababcdef");
  
    getchar();
    return 0;
}