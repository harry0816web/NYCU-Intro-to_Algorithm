#include <bits/stdc++.h>
#define int long long
using namespace std;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    cin >> n >> x;
    vector<long long> w(n);
    vector<int> p(n);
    for (int i = 0; i < n; i++)
        cin >> w[i];
    for (int i = 0; i < n; i++)
        cin >> p[i];

    // 最大總成本
    int max_cost = 100 * n;
    // dp[c] = 在總成本恰好為 c 時的最大長度, -1表示不可行
    vector<long long> dp(max_cost + 1, -1);
    dp[0] = 0;

    // 動態規劃轉移
    for (int i = 0; i < n; i++)
    {
        vector<long long> new_dp = dp;
        for (int c = 0; c <= max_cost; c++)
        {
            if (dp[c] == -1)
                continue; // 不可行狀態跳過
            int next_c = c + p[i];
            if (next_c <= max_cost)
            {
                new_dp[next_c] = max(new_dp[next_c], dp[c] + w[i]);
            }
        }
        dp = move(new_dp);
    }

    // 找出最小成本使 dp[c] >= x
    int ans = -1;
    for (int c = 0; c <= max_cost; c++)
    {
        if (dp[c] >= x)
        {
            ans = c;
            break;
        }
    }

    cout << ans << "\n";
    return 0;
}
