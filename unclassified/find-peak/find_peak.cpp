#include <iostream>
#include <vector>
using namespace std;

struct LogData
{
    int loginSec_;
    int logoutSec_;
    int uid_;

    LogData(int uid, int loginSec, int logoutSec) 
        : uid_(uid), loginSec_(loginSec), logoutSec_(logoutSec)
    {
    }
};

struct PeakData
{
    int startSec_;
    int endSec_;
    PeakData(int startSec, int endSec) : startSec_(startSec), endSec_(endSec)
    {
    }
};

typedef std::vector<PeakData> PeakList;
typedef std::vector<LogData> LogList;

PeakList getPeakList(const LogList &logList)
{
    PeakList result;
    int *count = NULL;
    int maxSec = 24*60*60;
    int maxValue = 0;

    if (logList.size() == 0)
        return result;

    count = new int[maxSec];
    memset(count, 0, maxSec * sizeof(int));

    for (const auto &x : logList)
    {
        // 数据合法性校验，忽略不合法
        if (x.loginSec_ < 0 || x.loginSec_ >= maxSec 
            || x.logoutSec_ <= 0 || x.logoutSec_ > maxSec
            || x.loginSec_ > x.logoutSec_)
        {
            continue;
        }

        for (int i = x.loginSec_; i <= x.logoutSec_; ++i)
            ++count[i];
    }

    for (int i = 0; i < maxSec;)
    {
        if (count[i] != 0 && count[i] >= maxValue)
        {
            int j = i;
            for (; j < maxSec && count[j] == count[i]; ++j);

            if (count[i] > maxValue)
                result.clear();
            PeakData pd(i, j - 1);
            result.push_back(pd);
            maxValue = count[i];

            i = j;
        } else {
            ++i;
        }
    }

    // free
    delete [] count;

    return result;
}

void printPeakList(const PeakList &plist)
{
    for (const auto &x : plist) 
    {
        cout << "(" << x.startSec_ << ", " << x.endSec_ << ")" << endl;
    }
}

int main()
{
    // case 1:
    {
        cout << "\ncase 1:\n";
        LogList logList;
        LogData d1(1, 3, 5);
        LogData d2(2, 4, 6);
        LogData d3(3, 0, 10);

        logList.push_back(d1);
        logList.push_back(d2);
        logList.push_back(d3);

        PeakList peakList = getPeakList(logList);
        printPeakList(peakList);
    }

    // case 2:
    {
        cout << "\ncase 2:\n";
        LogList logList;
        LogData d1(1, 3, 5);
        LogData d2(2, 4, 6);
        LogData d3(3, 8, 10);

        logList.push_back(d1);
        logList.push_back(d2);
        logList.push_back(d3);

        PeakList peakList = getPeakList(logList);
        printPeakList(peakList);
    }

    // case 3:
    {
        cout << "\ncase 3:\n";
        LogList logList;
        LogData d1(1, 3, 5);
        LogData d2(2, 5, 8);
        LogData d3(3, 8, 10);

        logList.push_back(d1);
        logList.push_back(d2);
        logList.push_back(d3);

        PeakList peakList = getPeakList(logList);
        printPeakList(peakList);
    }

    // case 4:
    {
        cout << "\ncase 4:\n";
        LogList logList;
        LogData d1(1, 3, 5);
        LogData d2(2, 4, 8);
        LogData d3(3, 8, 10);

        logList.push_back(d1);
        logList.push_back(d2);
        logList.push_back(d3);

        PeakList peakList = getPeakList(logList);
        printPeakList(peakList);
    }

    // case 5:
    {
        cout << "\ncase 5:\n";
        LogList logList;

        PeakList peakList = getPeakList(logList);
        printPeakList(peakList);
    }

    // case 6:
    {
        cout << "\ncase 6:\n";
        LogList logList;
        LogData d1(1, 3, 5);

        logList.push_back(d1);

        PeakList peakList = getPeakList(logList);
        printPeakList(peakList);
    }

    // case 7:
    {
        cout << "\ncase 7:\n";
        LogList logList;
        LogData d1(1, 3, 3);

        logList.push_back(d1);

        PeakList peakList = getPeakList(logList);
        printPeakList(peakList);
    }

    // case 8:
    {
        cout << "\ncase 8:\n";
        LogList logList;
        LogData d1(1, 3, 5);
        LogData d2(2, 4, 6);
        LogData d3(3, 8, 10);
        LogData d4(4, 8, 10);
        LogData d5(5, 8, 10);

        logList.push_back(d1);
        logList.push_back(d2);
        logList.push_back(d3);
        logList.push_back(d4);
        logList.push_back(d5);

        PeakList peakList = getPeakList(logList);
        printPeakList(peakList);
    }

    return 0;
}