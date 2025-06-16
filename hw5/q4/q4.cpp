#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#define int long long
using namespace std;
struct interval
{
    int start;
    int mid;
    int end;
};

map<pair<int, int>, int> m;
// map<pair<int, int>, interval> minInterval;
map<pair<int, int>, int> split_point;
vector<int> p(200 + 2);
int calMin(int l, int r)
{
    // cout << "--------------------------------" << endl;
    // cout << "l: " << l << " r: " << r << endl;
    if (m.find({l, r}) != m.end())
        return m[{l, r}];

    int minN = 1e18;
    int point = 0;
    // interval thisInterval;
    for (int k = l; k < r; k++)
    {
        int lk = 0;
        if (m.find({l, k}) != m.end())
            lk = m[{l, k}];
        else
            lk = calMin(l, k);
        int rk = 0;
        if (m.find({k + 1, r}) != m.end())
            rk = m[{k + 1, r}];
        else
            rk = calMin(k + 1, r);
        // cout << "l: " << l << " k: " << k << " r: " << r << " lk: " << lk << " rk: " << rk << " multi: " << p[l] * p[k + 1] * p[r + 1] << endl;
        // // minN = min(minN, lk + rk + p[l] * p[k + 1] * p[r + 1]);
        if (lk + rk + p[l] * p[k + 1] * p[r + 1] < minN)
        {
            minN = lk + rk + p[l] * p[k + 1] * p[r + 1];
            point = k;
            // thisInterval.start = l;
            // thisInterval.mid = k;
            // thisInterval.end = r;
        }
    }
    // cout << "minN between " << l << " and " << r << " is " << minN << endl;
    // cout << "--------------------------------" << endl;
    m.insert({{l, r}, minN});
    split_point.insert({{l, r}, point});
    // minInterval.insert({{l, r}, thisInterval});
    // cout << "split_point between " << l << " and " << r << " is " << point << endl;
    // print all m
    // for (auto it = m.begin(); it != m.end(); it++)
    // {
    //     cout << "{" << it->first.first << ", " << it->first.second << "}: " << it->second << endl;
    // }
    return minN;
}
void findInterval(int l, int r)
{
    if (l == r)
    {
        cout << "(A" << l << ")";
        return;
    }
    else if (split_point.find({l, r}) != split_point.end())
    {
        int point = split_point[{l, r}];
        if (l == point)
        {
            cout << "(A" << l << ")";
        }
        else
        {
            cout << "(";
            findInterval(l, point);
            cout << ")";
        }

        if (r == point + 1)
        {
            cout << "(A" << r << ")";
        }
        else
        {
            cout << "(";
            findInterval(point + 1, r);
            cout << ")";
        }
        return;
    }
    else
    {
        cout << "(A" << l << ")(A" << r << ")";
        return;
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n + 1; i++)
    {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++)
    {
        m.insert({{i, i}, 0});
    }
    for (int i = 1; i <= n - 1; i++)
    {
        m.insert({{i, i + 1}, p[i] * p[i + 1] * p[i + 2]});
    }
    for (int l = 1; l <= n; l++)
    {
        for (int r = l + 1; r <= n; r++)
        {
            m.insert({{l, r}, calMin(l, r)});
        }
    }
    // cout << "ans: " << endl;
    cout << calMin(1, n) << endl;
    cout << "(";
    findInterval(1, n);
    cout << ")" << endl;
    // cout << "--------------------------------" << endl;
}
// 4
// 5 1 3 4 2
//