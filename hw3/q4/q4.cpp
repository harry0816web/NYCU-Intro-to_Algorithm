#include <iostream>
#include <vector>
#include <string>
#define int long long
using namespace std;

const int MAXN = 100005;
vector<int> length(4 * MAXN, 0);
vector<int> count(4 * MAXN, 0); // 用於追蹤每個區間的重疊次數
vector<int> points(MAXN);

void update(int node, int start, int end, int l, int r, int value)
{
    // 如果當前區間不在範圍內，直接返回
    if (start > end || start > r || end < l)
    {
        return;
    }

    // 如果當前區間完全包含在[l, r]內，更新該區間
    if (start >= l && end <= r)
    {
        count[node] += value;
        length[node] = (count[node] > 0) ? (points[end + 1] - points[start]) : 0;
        if (count[node] == 0 && start != end)
            length[node] = length[2 * node] + length[2 * node + 1];
        return;
    }

    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, value);       // 更新左子區間
    update(2 * node + 1, mid + 1, end, l, r, value); // 更新右子區間

    // 更新當前節點的區間長度
    if (count[node] == 0)
        length[node] = length[2 * node] + length[2 * node + 1];
}

int query()
{
    return length[1];
}

signed main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> points[i];
    }

    int q;
    cin >> q;
    while (q--)
    {
        string op;
        cin >> op;
        if (op == "insert")
        {
            int l, r;
            cin >> l >> r;
            // 更新整個 [l, r] 區間
            update(1, 1, n - 1, l, r - 1, 1);
        }
        else if (op == "delete")
        {
            int l, r;
            cin >> l >> r;
            // 刪除整個 [l, r] 區間
            update(1, 1, n - 1, l, r - 1, -1);
        }
        else if (op == "report")
        {
            cout << query() << endl;
        }
    }

    return 0;
}
