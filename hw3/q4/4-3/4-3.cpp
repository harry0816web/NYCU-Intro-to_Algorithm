#include <iostream>
#include <vector>
#include <string>
#define int long long
using namespace std;

const int MAXN = 100005;
vector<int> length(4 * MAXN, 0);
vector<int> count(4 * MAXN, 0); // 用於追蹤每個區間的重疊次數
vector<int> points(MAXN);

vector<int> lazy(4 * MAXN, 0);

void propagate(int node, int start, int end)
{
    if (lazy[node] != 0)
    {
        count[node] += lazy[node];
        if (count[node] > 0)
        {
            length[node] = points[end + 1] - points[start];
        }
        else
        {
            if (start != end)
            {
                length[node] = length[2 * node] + length[2 * node + 1];
            }
            else
            {
                length[node] = 0;
            }
        }
        if (start != end)
        {
            lazy[2 * node] += lazy[node];
            lazy[2 * node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r, int value)
{
    propagate(node, start, end);
    if (start > end || start > r || end < l)
    {
        return;
    }
    if (start >= l && end <= r)
    {
        lazy[node] += value;
        propagate(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, value);
    update(2 * node + 1, mid + 1, end, l, r, value);
    length[node] = (count[node] > 0) ? (points[end + 1] - points[start]) : (length[2 * node] + length[2 * node + 1]);
}

int query(int node, int start, int end, int l, int r)
{
    propagate(node, start, end);
    if (start > end || start > r || end < l)
    {
        return 0;
    }
    if (start >= l && end <= r)
    {
        return length[node];
    }
    int mid = (start + end) / 2;
    int left_query = query(2 * node, start, mid, l, r);
    int right_query = query(2 * node + 1, mid + 1, end, l, r);
    return left_query + right_query;
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
            int l, r;
            cin >> l >> r;
            // 暫時更新整個 [l, r] 區間
            update(1, 1, n - 1, l, r - 1, 1);
            cout << query() << endl;
            // 恢復原狀
            update(1, 1, n - 1, l, r - 1, -1);
        }
    }

    return 0;
}

// 這題是在report的時候還要將這些聯集與輸入的區間交集最後在輸出長度 我覺得可以用先把其他區間的長度設為0 加上懶人標記 計算完長度之後再將長度復原
