#include <iostream>
#include <vector>
using namespace std;

#define MAX(x, y) (x > y ? x : y)

struct Knapsack
{
    int value_;
    int weight_;
    Knapsack(int weight, int value) : weight_(weight), value_(value)
    {
    }
};

typedef std::vector<Knapsack> Knapsacks;
typedef std::vector<int> Vec;
typedef std::vector<Vec> Array;

int getMaxWeight(int totalWeight, const Knapsacks &knapsacks)
{
    int len = knapsacks.size();
    Array dp(len + 1, Vec(totalWeight + 1, 0));

    for (int i = 1; i <= len; ++i)
    {
        for (int j = 1; j <= totalWeight; ++j)
        {
            const Knapsack &tmp = knapsacks[i-1];
            if (tmp.weight_ > j) 
                dp[i][j] = dp[i-1][j];
            else 
                dp[i][j] = MAX(dp[i-1][j], dp[i-1][j-tmp.weight_] + tmp.value_);
        }
    }

    for (auto &nums : dp) 
    {
        for (auto &x : nums) 
        {
            cout << x << " ";
        }
        cout << endl;
    }

    return dp[len][totalWeight];
}

int main()
{
    {
        Knapsack knapsack1(1, 1);
        Knapsack knapsack2(2, 6);
        Knapsack knapsack3(5, 18);
        Knapsack knapsack4(6, 22);
        Knapsack knapsack5(7, 28);
        Knapsacks knapsacks;
        knapsacks.push_back(knapsack1);
        knapsacks.push_back(knapsack2);
        knapsacks.push_back(knapsack3);
        knapsacks.push_back(knapsack4);
        knapsacks.push_back(knapsack5);

        int result = getMaxWeight(11, knapsacks);
        cout << "result=" << result << endl;
    }
    
    return 0;
}