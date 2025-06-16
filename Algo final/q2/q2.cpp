#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    long long result = 0;

    // DP 表計算
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = n - 1; j >= 0; --j)
        {
            if (s[i] == s[j])
            {
                dp[i][j] = dp[i + 1][j + 1] + 1;
            }
            else
            {
                dp[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result += dp[i][j];
        }
    }
    cout << result << endl;
    return 0;
}
