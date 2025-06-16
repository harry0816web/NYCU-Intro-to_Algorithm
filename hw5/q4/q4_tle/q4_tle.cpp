// 修正：使用二维数组替换map，并修正数据类型和逻辑错误

#include <iostream>
#include <algorithm>
using namespace std;

// 定义最大 n 为 200
const int MAX_N = 200;

// 使用 long long 以防止整数溢出
long long m_arr[202][202];
int split_point_arr[202][202];
int p_arr[202];

// 计算最小乘法次数的函数，返回 long long 类型
long long calMin(int l, int r)
{
    if (m_arr[l][r] != -1)
        return m_arr[l][r];

    if (l == r)
    {
        m_arr[l][r] = 0;
        return 0;
    }

    long long minN = 1e18;
    int point = l;

    for (int k = l; k < r; k++)
    {
        long long lk = (m_arr[l][k] != -1) ? m_arr[l][k] : calMin(l, k);
        long long rk = (m_arr[k + 1][r] != -1) ? m_arr[k + 1][r] : calMin(k + 1, r);
        long long cost = lk + rk + (long long)p_arr[l] * p_arr[k + 1] * p_arr[r + 1];
        if (cost < minN)
        {
            minN = cost;
            point = k;
        }
    }

    m_arr[l][r] = minN;
    split_point_arr[l][r] = point;
    return m_arr[l][r];
}

// 打印最优括号化的函数
void findInterval(int l, int r)
{
    if (l == r)
    {
        cout << "(A" << l << ")";
        return;
    }

    cout << "(";
    findInterval(l, split_point_arr[l][r]);
    findInterval(split_point_arr[l][r] + 1, r);
    cout << ")";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n + 1; i++)
    {
        cin >> p_arr[i];
    }

    // 初始化 m_arr 为 -1 表示未计算
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            m_arr[i][j] = -1;
            split_point_arr[i][j] = -1;
        }
    }

    // 计算最小乘法次数
    long long result = calMin(1, n);
    cout << result << "\n";

    // 打印最优括号化
    findInterval(1, n);
    cout << "\n";

    return 0;
}