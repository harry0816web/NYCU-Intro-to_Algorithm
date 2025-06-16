#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
struct event
{
    int start;
    int end;
    int reward;
};
bool cmp(event a, event b)
{
    if (a.end == b.end)
        return a.start < b.start;
    return a.end < b.end;
}

// int binary_search(vector<event> events, int l, int r, int k)
// {
//     if (l >= r)
//     {
//         if (events[l].end < k)
//         {
//             return l;
//         }
//         return -1;
//     }

//     int mid = (l + r) / 2;
//     if (events[mid].end < k)
//         return binary_search(events, mid + 1, r, k);
//     else if (events[mid].end >= k)
//         return binary_search(events, l, mid - 1, k);
//     return -1;
// }
int binary_search(const vector<event> &events, int l, int r, int k)
{
    int result = -1;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (events[mid].end < k)
        {
            result = mid; // 記錄當前符合條件的最大索引
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return result;
}

signed main()
{
    int n;
    cin >> n;
    vector<event> events(n + 1);
    vector<int> reward(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> events[i].start >> events[i].end >> events[i].reward;
    }
    events[0].reward = 0;
    events[0].start = -1;
    events[0].end = -1;
    sort(events.begin(), events.end(), cmp);
    for (int i = 1; i <= n; i++)
    {
        reward[i] = events[i].reward;
    }
    reward[0] = 0;
    int prev_event = 0;
    for (int i = 1; i <= n; i++)
    {
        prev_event = binary_search(events, 1, i - 1, events[i].start);
        if (prev_event == -1)
        {
            reward[i] = max(reward[i - 1], reward[i]);
        }
        else
        {
            reward[i] = max(reward[prev_event] + reward[i], reward[i - 1]);
        }
    }
    cout << reward[n] << endl;
    return 0;
}
