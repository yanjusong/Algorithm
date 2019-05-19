#include "bloomfilter.hpp"

unsigned int getIntHash(const int &x)
{
    return x;
}

struct Student
{
    Student(std::string name, int id) : name_(name), id_(id) {}
    std::string name_;
    int id_;
};

unsigned int getStuHash(const Student &x)
{
    std::hash<std::string> h;
    return h(x.name_) + x.id_;
}

// g++ -std=c++11 test__all.cpp -o a && ./a
int main()
{
    {
        BloomFilter<int> ft(128, 4, getIntHash);
        ft.insert(1);
        ft.insert(2);
        ft.insert(3);

        printf("not exist %d: %s\n", 1, ft.exist(1) ? "unknown" : "true");
        printf("not exist %d: %s\n", 2, ft.exist(2) ? "unknown" : "true");
        printf("not exist %d: %s\n", 3, ft.exist(3) ? "unknown" : "true");
        printf("not exist %d: %s\n", 4, ft.exist(4) ? "unknown" : "true");
    }

    printf("---------------------------------------\n");
    
    {
        BloomFilter<Student> ft(128, 4, getStuHash);
        Student Jason("jason", 1);
        Student Jeff("Jeff", 2);
        Student Jerry("Jerry", 3);
        Student Tom("Tom", 4);

        ft.insert(Jason);
        ft.insert(Jeff);
        ft.insert(Jerry);

        printf("not exist %s: %s\n", Jason.name_.c_str(), ft.exist(Jason) ? "unknown" : "true");
        printf("not exist %s: %s\n", Jeff.name_.c_str(), ft.exist(Jeff) ? "unknown" : "true");
        printf("not exist %s: %s\n", Jerry.name_.c_str(), ft.exist(Jerry) ? "unknown" : "true");
        printf("not exist %s: %s\n", Tom.name_.c_str(), ft.exist(Tom) ? "unknown" : "true");
    }

    return 0;
}
