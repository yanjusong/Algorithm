#include "Generator.h"

#include <iostream>
#include <ctime>
using namespace std;

int Generator::genIntegers(const std::string &outputFileName, int total)
{
    srand((unsigned)time(NULL));

    FILE *fp = fopen(outputFileName.c_str(), "w+");
    if (!fp)
    {
        return CannotOpenFile;
    }

    for (int i = 0; i < total; i++)
    {
        int randomNum = rand();
        if (fprintf(fp, "%d\n", randomNum) < 0)
        {
            fclose(fp);
            return WriteError;
        }
    }
        
    fclose(fp);
    return 0;
}
