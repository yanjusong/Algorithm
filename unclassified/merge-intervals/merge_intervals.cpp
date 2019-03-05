#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Interval
{
    int start_;
    int end_;

    Interval(int start, int end) : start_(start), end_(end) 
    {
    }

    bool operator<(const Interval &rhs) const
    {
        return start_ < rhs.start_;
    }
};

typedef std::vector<Interval> Intervals;

void printIntervals(const Intervals &intervals)
{
    cout << "[";
    for (auto x : intervals) 
    {
        cout << "(" << x.start_ << ", " << x.end_ << ") ";
    }
    cout << "]" << endl;
}

Intervals mergeIntervals(Intervals &intervals)
{
    Intervals result;
    int len = intervals.size();

    if (len == 0)
        return result;

    sort(intervals.begin(), intervals.end());

    Interval item(-1, -1);
    for (int i = 0; i < len - 1; ++i) 
    {
        item = intervals[i];
        Interval &nextItem = intervals[i + 1];
        if (nextItem.start_ <= item.end_) {
            nextItem.start_ = item.start_;
            nextItem.end_ = (item.end_ > nextItem.end_ ? item.end_ : nextItem.end_);
        } else {
            result.push_back(item);
        }
    }

    result.push_back(intervals.back());

    return result;
}

int main()
{
    // case 1
    {
        Intervals intervals;

        cout << "case 1:" << endl;
        printIntervals(intervals);
        Intervals result = mergeIntervals(intervals);
        printIntervals(result);
        cout << endl;
    }

    // case 2
    {
        Intervals intervals;
        Interval item1(1, 2);
        intervals.push_back(item1);

        cout << "case 2:" << endl;
        printIntervals(intervals);
        Intervals result = mergeIntervals(intervals);
        printIntervals(result);
        cout << endl;
    }

    // case 3
    {
        Intervals intervals;
        Interval item1(1, 2);
        Interval item2(2, 3);

        intervals.push_back(item1);
        intervals.push_back(item2);
        
        cout << "case 3:" << endl;
        printIntervals(intervals);
        Intervals result = mergeIntervals(intervals);
        printIntervals(result);
        cout << endl;
    }

    // case 4
    {
        Intervals intervals;
        Interval item1(1, 10);
        Interval item2(2, 3);

        intervals.push_back(item1);
        intervals.push_back(item2);
        
        cout << "case 4:" << endl;
        printIntervals(intervals);
        Intervals result = mergeIntervals(intervals);
        printIntervals(result);
        cout << endl;
    }

    // case 5
    {
        Intervals intervals;
        Interval item1(1, 2);
        Interval item2(3, 4);

        intervals.push_back(item1);
        intervals.push_back(item2);
        
        cout << "case 5:" << endl;
        printIntervals(intervals);
        Intervals result = mergeIntervals(intervals);
        printIntervals(result);
        cout << endl;
    }

    // case 6
    {
        Intervals intervals;
        Interval item1(1, 2);
        Interval item2(2, 3);
        Interval item3(1, 1);
        Interval item4(1, 1);
        Interval item5(5, 7);
        Interval item6(6, 8);

        intervals.push_back(item1);
        intervals.push_back(item2);
        intervals.push_back(item3);
        intervals.push_back(item4);
        intervals.push_back(item5);
        intervals.push_back(item6);

        cout << "case 6:" << endl;
        printIntervals(intervals);
        Intervals result = mergeIntervals(intervals);
        printIntervals(result);
        cout << endl;
    }

    return 0;
}
