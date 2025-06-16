#include <iostream>
#include <vector>
#include <queue>
#include <numeric> // for accumulate
using namespace std;

signed main()
{
    int x, n;
    cin >> x >> n;
    vector<int> lengths(n);
    for (int i = 0; i < n; i++)
    {
        cin >> lengths[i];
    }

    if (accumulate(lengths.begin(), lengths.end(), 0LL) != x)
    {
        cout << "Invalid input" << endl;
        return 1;
    }

    if (n == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    priority_queue<int, vector<int>, greater<int>> pq(lengths.begin(), lengths.end());
    long long total_cost = 0;

    while (pq.size() > 1)
    {
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();
        int cost = first + second;
        total_cost += cost;
        pq.push(cost);
    }

    cout << total_cost << endl;
    return 0;
}
