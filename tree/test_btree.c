#include "b.h"

#include <stdio.h>

int main()
{
    char buf[64];
    int x = 0;
    //sscanf("123456", "%8s", buf);
    //sprintf(buf, "%8d", -45);
    sprintf(buf, "0x%.8x", &x);
    //sprintf(buf, "%.6s", "he");
    strcat(buf, "  ");
    printf("%s, %d\n", buf, strlen(buf));

    getchar();
    return 0;
}