#ifndef GENERATOR_H_20190513
#define GENERATOR_H_20190513

#include <string>

class Generator
{
public:
    enum Error 
    {
        CannotOpenFile = 1,
        WriteError = 2,
    };

public:
    int genIntegers(const std::string &outputFileName, int total);
};

#endif // !GENERATOR_H_20190513
