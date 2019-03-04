#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int weight;
    int cur_weight;
    char name[3];
} server;

int getsum(int *set, int size)
{
    int i = 0;
    int res = 0;

    for (i = 0; i < size; i++)
        res += set[i];

    return res;
}

server *initServers(char **names, int *weights, int size)
{
    int i = 0;
    server *ss = (server *)malloc((size + 1) * sizeof(server));

    for (i = 0; i < size; i++) {
        ss[i].weight = weights[i];
        memcpy(ss[i].name, names[i], 3);
        ss[i].cur_weight = 0;
    }

    return ss;
}

/**
 * @brief:
 *      1.遍历服务器列表，每个服务器的当前权值都加上单位权值；
 *      2.total表示遍历过程中加上的单位权值的总和；
 *      3.选取最大当前权值的服务器，将它的当前权值减去total。
 */
int getNextServerIndex(server *ss, int size)
{
    int i;
    int index = -1;
    int total = 0;

    for (i = 0; i < size; i++) {
        ss[i].cur_weight += ss[i].weight;
        total += ss[i].weight;

        // 1.初始化是选择第一个服务器
        // 2.否则选择cur_weight最大的服务器
        if (index == -1 || ss[index].cur_weight < ss[i].cur_weight) {
            index = i;
        }
    }

    ss[index].cur_weight -= total;
    return index;
}

void wrr_nginx(server *ss, int *weights, int size)
{
    int i = 0;
    int index = -1;
    int sum = getsum(weights, size);

    for (i = 0; i < sum; i++) {
        index = getNextServerIndex(ss, size);
        printf("%s(%d) ", ss[index].name, ss[index].weight);
    }
    printf("\n");
}

int main()
{
    int i = 0;
    int weights[] = { 4, 2, 1 };
    char *names[] = { "a", "b", "c" };
    int size = sizeof(weights) / sizeof(int);

    server *ss = initServers(names, weights, size);

    printf("server is ");
    for (i = 0; i < size; i++) {
        printf("%s(%d) ", ss[i].name, ss[i].weight);
    }
    printf("\n");

    printf("\nwrr_nginx sequence is ");
    wrr_nginx(ss, weights, size);

    free(ss);

    return 0;
}