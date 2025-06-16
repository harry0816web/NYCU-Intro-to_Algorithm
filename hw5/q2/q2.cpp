#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
#define maxN 1000000
using namespace std;
vector<int> lazy(2 * maxN + 1, 0);
vector<int> value(maxN * 4 + 1, 0);
vector<int> initialArray(maxN + 1, 0);
void build(int left, int right, int node)
{
    if (left == right)
    {
        value[node] = initialArray[left]; // 假設有一個初始數組 initialArray
        return;
    }
    int mid = (left + right) / 2;
    build(left, mid, node * 2);
    build(mid + 1, right, node * 2 + 1);
    value[node] = value[node * 2] + value[node * 2 + 1];
}
void update(int left, int right, int node, int l, int r, int k)
{
    // 處理懶標記
    if (lazy[node] != 0)
    {
        value[node] += (right - left + 1) * lazy[node];
        if (left != right)
        {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }

    // 區間不相交
    if (l > right || r < left)
        return;

    // 完全包含的情況
    if (l <= left && r >= right)
    {
        value[node] += (right - left + 1) * k;
        if (left != right)
        {
            lazy[node * 2] += k;
            lazy[node * 2 + 1] += k;
        }
        return;
    }

    // 部分重疊，遞迴處理左右子節點
    int mid = (left + right) / 2;
    update(left, mid, node * 2, l, r, k);
    update(mid + 1, right, node * 2 + 1, l, r, k);
    value[node] = value[node * 2] + value[node * 2 + 1];
}
int query(int left, int right, int node, int l, int r)
{
    // 區間不相交
    if (l > right || r < left)
        return 0;

    // 處理lazy propagation
    if (lazy[node] != 0)
    {
        // 更新當前節點的 value，根據區間長度
        value[node] += (right - left + 1) * lazy[node];

        if (left != right)
        {
            // 向下傳遞 lazy 標記
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        // 清除當前節點的 lazy 標記
        lazy[node] = 0;
    }

    // 完全包含的情況
    if (l <= left && r >= right)
    {
        return value[node];
    }

    // 部分重疊，需要遞迴處理
    int mid = (left + right) / 2;
    return query(left, mid, node * 2, l, r) +
           query(mid + 1, right, node * 2 + 1, l, r);
}
signed main()
{
    int n, q;
    cin >> n; // 數組大小
    cin >> q; // 查詢數量
    for (int i = 1; i <= n; ++i)
        cin >> initialArray[i]; // 讀入初始數組
    build(1, n, 1);             // 建立線段樹

    while (q--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r, k;
            cin >> l >> r >> k;
            update(1, n, 1, l, r, k); // 區間更新
        }
        else if (type == 2)
        {
            int l, r;
            cin >> l >> r;
            cout << query(1, n, 1, l, r) << "\n"; // 區間查詢
        }
    }
    return 0;
}