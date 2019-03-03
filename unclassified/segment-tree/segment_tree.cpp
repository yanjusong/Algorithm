#include <iostream>
#include <vector>

using namespace std;

class SegmentTree
{
    class Node
    {
      public:
        int start, end, sum;
        Node *left, *right;
        Node(int start, int end, int sum)
        {
            this->start = start;
            this->end = end;
            this->sum = sum;
            this->left = this->right = NULL;
        }
    };

  public:
    /**
	 * @param A: An integer array
	 */
    SegmentTree(const vector<int> &A)
    {
        // do nothing
        if (A.empty())
            return;
        root_ = build(0, A.size() - 1, A);
    }

    ~SegmentTree()
    {
        clear(root_);
    }

    /**
	 * @param start: An integer
	 * @param end: An integer
	 * @return: The sum from start to end
	 */
    long long query(int start, int end)
    {
        if (start > end)
            return 0;
        return doQuery(root_, start, end);
    }

    /**
	 * @param index: An integer
	 * @param value: An integer
	 * @return: nothing
	 */
    void modify(int index, int value)
    {
        // write your code here
        doModify(root_, index, value);
    }

  private:
    Node *root_;

    Node *build(int start, int end, const vector<int> &v)
    {
        if (start == end)
            return new Node(start, end, v[start]);
        int mid = (start + end) / 2;
        Node *node = new Node(start, end, 0);
        node->left = build(start, mid, v);
        node->right = build(mid + 1, end, v);
        node->sum = node->left->sum + node->right->sum;
        return node;
    }

    int doQuery(Node *root, int start, int end)
    {
        if (!root)
            return 0;

        if (start > root->end || end < root->start)
            return 0;

        if (start <= root->start && end >= root->end)
            return root->sum;

        return doQuery(root->left, start, end) + doQuery(root->right, start, end);
    }

    void doModify(Node *root, int index, int value)
    {
        if (root->start == root->end && root->start == index)
        {
            root->sum = value;
            return;
        }
        int mid = (root->start + root->end) / 2;
        if (index <= mid)
        {
            doModify(root->left, index, value);
            root->sum = root->left->sum + root->right->sum;
        }
        else
        {
            doModify(root->right, index, value);
            root->sum = root->left->sum + root->right->sum;
        }
    }

    void clear(Node *node)
    {
        if (!node)
            return;
        clear(node->left);
        clear(node->right);
        delete node;
        node = NULL;
    }
};

int main()
{
    vector<int> nums = {1, 7, 3, 4, 2, 5};
    SegmentTree st(nums);

    cout << "vector: ";
    for (auto x : nums)
        cout << x << " ";
    cout << endl;

    cout << "sum[0,5]:" << st.query(0, 5) << endl;
    cout << "sum[0,1]:" << st.query(0, 1) << endl;
    cout << "sum[4,5]:" << st.query(4, 5) << endl;
    cout << "sum[0,0]:" << st.query(0, 0) << endl;
    cout << "sum[5,5]:" << st.query(5, 5) << endl;
    cout << "sum[-1,5]:" << st.query(-1, 5) << endl;
    cout << "sum[-1,6]:" << st.query(-1, 6) << endl;
    cout << "sum[-6,-1]:" << st.query(-6, -1) << endl;

    return 0;
}