#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int>::iterator vi;
typedef pair<vi, vi> pvv;

/*
 * 属性
 * 1. m_head: 数组当前指针初始化为数组头指针
 * 2. m_cnt:  数组从当前指针之后的元素个数
 */
struct ArrayAttrs
{
    int *m_head;
    unsigned int m_cnt;
    ArrayAttrs(int *head, unsigned int cnt):m_head(head), m_cnt(cnt) {}

    ~ArrayAttrs()
    {
        delete [] m_head;
    }

    ArrayAttrs& operator=(const ArrayAttrs& rhs)
    {
        if(&rhs != this) {
            m_head = rhs.m_head;
            m_cnt = rhs.m_cnt;
        }
        return *this;
    }

    friend ostream& operator<<(ostream &os, const ArrayAttrs &rhs);
};

ostream& operator<<(ostream &os, const ArrayAttrs &rhs)
{
    os << "元素个数：" << rhs.m_cnt << endl;

    for(int i = 0; i < rhs.m_cnt; ++i) {
        cout << *(rhs.m_head + i) << " ";
    }
    cout << endl;
}

struct cmp
{
    bool operator() (const ArrayAttrs &lhs, const ArrayAttrs &rhs) const
    {
        return *(lhs.m_head) > *(rhs.m_head);
    }
};

ArrayAttrs *mergeKSortArray(vector<ArrayAttrs> arrays)
{
    if(arrays.size() == 0)
        return NULL;

    priority_queue<ArrayAttrs, vector<ArrayAttrs>, cmp> heap;
    unsigned int totalElements = 0;

    for(auto &array : arrays) {
        heap.push(array);
        totalElements += array.m_cnt;
    }

    int *res = new int[totalElements];
    int *p = res;
    ArrayAttrs minArrayAttrs(NULL, 0);

    while(!heap.empty()) {
        minArrayAttrs = heap.top();
        heap.pop();

        *p++ = *(minArrayAttrs.m_head);
        --minArrayAttrs.m_cnt;
        ++minArrayAttrs.m_head;

        // 当m_cnt为0时表示这个数组的元素都已经被选中了
        if(minArrayAttrs.m_cnt)
            heap.push(minArrayAttrs);
    }

    return new ArrayAttrs(res, totalElements);
}

struct cmpPvv
{
    bool operator()(const pvv &lhs, const pvv &rhs)
    {
        return *(lhs.first) > *(rhs.first);
    }
};

vector<int> mergeKSortArray(vector<vector<int> > arrays)
{
    priority_queue<pvv, vector<pvv>, cmpPvv> heap;

    for(auto &array : arrays) {
        if(array.size()) {
            heap.push( pvv(array.begin(), array.end()) );
        }
    }

    if(heap.empty())
        return vector<int> ();

    vector<int> res;
    pvv minPvv(res.begin(), res.end());
    while(!heap.empty()) {
        minPvv.first = heap.top().first;
        minPvv.second = heap.top().second;
        heap.pop();

        res.push_back(*(minPvv.first));

        ++(minPvv.first);
        if(minPvv.first != minPvv.second)
            heap.push(minPvv);
    }

    return res;
}

int main(int argc, char const *argv[])
{
    /* 
     * 1. 排序数组（普通）的多路归并排序
     * 构造ArrayAttrs对象以判断数组是否遍历完毕
     */
    int nums1[] = {1, 4, 7};
    int nums2[] = {2, 5, 8};
    int nums3[] = {2, 11, 13};

    ArrayAttrs aa1(nums1, sizeof(nums1)/sizeof(nums1[0]));
    ArrayAttrs aa2(nums2, sizeof(nums2)/sizeof(nums2[0]));
    ArrayAttrs aa3(nums3, sizeof(nums3)/sizeof(nums3[0]));

    vector<ArrayAttrs> arrays;
    arrays.push_back(aa1);
    arrays.push_back(aa2);
    arrays.push_back(aa3);

    ArrayAttrs *res = mergeKSortArray(arrays);
    cout << *res << endl;
    delete res;
    res = NULL;

    /*
     * 2. vector数组的多路归并排序
     * 以迭代器判断数组遍历完毕标志
     */
    vector<int> vec1 = {1, 4, 7};
    vector<int> vec2 = {2, 5, 8};
    vector<int> vec3 = {2, 11, 13};
    vector<vector<int> > vecs;
    vecs.push_back(vec1);
    vecs.push_back(vec2);
    vecs.push_back(vec3);

    vector<int> vec = mergeKSortArray(vecs);
    for(auto &i : vec)
        cout << i << " ";
    cout << endl;

    return 0;
}