#include "Generator.h"

#include <iostream>
using namespace std;

// g++ -std=c++11 test__Generator.cpp Generator.cpp -o a && ./a
int main()
{
    Generator gen;
    gen.genIntegers("./output.txt", 20);
    cout << "----------------------\n\n";
    FILE *fp = fopen("./output.txt", "r");
    int num = 0;
    while (fscanf(fp, "%d", &num) != EOF)
    {
        cout << num << endl;
    }

    return 0;
}