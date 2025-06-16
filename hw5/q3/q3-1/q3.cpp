#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;
struct event
{
    int start;
    int end;
};
bool cmp(event a, event b)
{
    if (a.end == b.end)
        return a.start < b.start;
    return a.end < b.end;
}
signed main()
{
    int n;
    cin >> n;
    int last_end = -1;
    vector<event> events(n);
    for (int i = 0; i < n; i++)
    {
        cin >> events[i].start >> events[i].end;
    }
    sort(events.begin(), events.end(), cmp);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (events[i].start >= last_end)
        {
            ans++;
            last_end = events[i].end;
        }
    }
    cout << ans << endl;
    return 0;
}
