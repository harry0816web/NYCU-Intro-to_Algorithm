#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define int long long
using namespace std;

struct Event
{
    int y, x1, x2, type; // y 為橫坐標，x1 和 x2 為水平邊界，type = 1 (進入), -1 (離開)
    Event(int y, int x1, int x2, int type) : y(y), x1(x1), x2(x2), type(type) {}
    bool operator<(const Event &other) const
    {
        return y < other.y; // 根據 y 坐標排序事件
    }
};

struct rect
{
    int x1, y1, x2, y2;
    rect(int _x1, int _y1, int _x2, int _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
    rect() {}
};

const int MAXN = 100005;
vector<int> x_coords(1); // 初始化時添加一個 dummy 元素
vector<int> cnt(4 * (MAXN + 1));
vector<int> length(4 * (MAXN + 1));

void update(int node, int start, int end, int l, int r, int value)
{
    // 如果當前區間不在範圍內，直接返回
    if (start > end || start > r || end < l)
    {
        return;
    }

    // 如果當前區間完全包含在[l, r]內，更新該區間
    if (start >= l && end <= r)
    {
        cnt[node] += value;
    }
    else
    {
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, value);       // 更新左子區間
        update(2 * node + 1, mid + 1, end, l, r, value); // 更新右子區間
    }

    // 更新當前節點的區間長度
    if (cnt[node] > 0)
    {
        length[node] = x_coords[end + 1] - x_coords[start];
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
}

int query()
{
    return length[1];
}

signed main()
{
    int n;
    cin >> n;
    vector<rect> rects(n + 1); // 初始化時添加一個 dummy 元素
    vector<Event> events;
    for (int i = 1; i <= n; i++)
    {
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
        events.push_back(Event(rects[i].y1, rects[i].x1, rects[i].x2, 1));
        events.push_back(Event(rects[i].y2, rects[i].x1, rects[i].x2, -1));
        x_coords.push_back(rects[i].x1);
        x_coords.push_back(rects[i].x2);
    }

    // 對 x 坐標進行離散化
    sort(x_coords.begin() + 1, x_coords.end());                                   // 1-based
    x_coords.erase(unique(x_coords.begin() + 1, x_coords.end()), x_coords.end()); // 1-based

    // 排序所有事件，按照 y 坐標遞增順序處理
    sort(events.begin(), events.end());

    long long total_area = 0;
    int prev_y = events[0].y;

    for (auto &event : events)
    {
        total_area += query() * (event.y - prev_y);
        int l = lower_bound(x_coords.begin() + 1, x_coords.end(), event.x1) - x_coords.begin();
        int r = lower_bound(x_coords.begin() + 1, x_coords.end(), event.x2) - x_coords.begin();
        update(1, 1, x_coords.size() - 1, l, r - 1, event.type);
        prev_y = event.y;
    }

    cout << total_area << endl;

    return 0;
}