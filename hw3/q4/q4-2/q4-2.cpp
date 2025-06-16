#include <iostream>
#include <vector>
#include <algorithm>
#define int long long
using namespace std;

struct Event
{
    int y, x1, x2, type;
    Event(int y, int x1, int x2, int type) : y(y), x1(x1), x2(x2), type(type) {}
    Event() {}
    bool operator<(const Event &other) const
    {
        if (y != other.y)
            return y < other.y;
        return type > other.type;
    }
};

struct rect
{
    int x1, y1, x2, y2;
    rect(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
    rect() {}
};

const int MAXN = 200005;
vector<int> x_coords;
vector<int> cnt(4 * MAXN, 0);
vector<int> length(4 * MAXN, 0);

void update_length(int node, int start, int end)
{
    if (cnt[node] > 0)
    {
        length[node] = x_coords[end + 1] - x_coords[start];
    }
    else if (start == end)
    {
        length[node] = 0;
    }
    else
    {
        length[node] = length[2 * node] + length[2 * node + 1];
    }
}

void update(int node, int start, int end, int l, int r, int value)
{
    if (r < l || r < start || end < l)
    {
        return;
    }
    if (l <= start && end <= r)
    {
        cnt[node] += value;
        update_length(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update(2 * node, start, mid, l, r, value);
    update(2 * node + 1, mid + 1, end, l, r, value);
    update_length(node, start, end);
}

int query()
{
    return length[1];
}

signed main()
{
    int n;
    cin >> n;
    vector<rect> rects(n);
    vector<Event> events;

    for (int i = 0; i < n; i++)
    {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        events.push_back(Event(rects[i].y1, rects[i].x1, rects[i].x2, 1));
        events.push_back(Event(rects[i].y2, rects[i].x1, rects[i].x2, -1));
        x_coords.push_back(rects[i].x1);
        x_coords.push_back(rects[i].x2);
    }

    // sort and erase duplicates in x_coords
    sort(x_coords.begin(), x_coords.end());
    x_coords.erase(unique(x_coords.begin(), x_coords.end()), x_coords.end());

    // sort events by y
    sort(events.begin(), events.end());

    long long total_area = 0;
    int prev_y = events[0].y;

    for (auto &event : events)
    {
        if (event.y != prev_y)
        {
            total_area += query() * (event.y - prev_y);
            prev_y = event.y;
        }

        // find x1, x2 index in x_coords
        int l = lower_bound(x_coords.begin(), x_coords.end(), event.x1) - x_coords.begin();
        int r = lower_bound(x_coords.begin(), x_coords.end(), event.x2) - x_coords.begin();

        if (l < r)
        {
            update(1, 0, x_coords.size() - 1, l, r - 1, event.type);
        }
    }

    cout << total_area << endl;

    return 0;
}
