#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

class Point
{
public:
    long long x;
    long long y;
    int id;

    Point(long long x = 0, long long y = 0, int id = 0) : x(x), y(y), id(id) {}
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    Point *p = (Point *)malloc(n * sizeof(Point));
    Point *query = (Point *)malloc(n * sizeof(Point));
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].x >> p[i].y;
        p[i].id = i;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> query[i].x >> query[i].y;
    }

    int *ans = (int *)malloc(m * sizeof(int));

    for (int i = 0; i < m; i++)
    {
        int l = 0, r = n - 1, mid = l + (r - l) / 2;
        while (l <= r)
        {
            mid = (l + r) / 2;
            Point v1 = Point(p[mid].x - query[i].x, p[mid].y - query[i].y);
            Point v2 = Point(p[mid + 1].x - query[i].x, p[mid + 1].y - query[i].y);
            long long product = v1.x * v2.y - v2.x * v1.y;
            if (product > 0)
            {
                l = mid + 1;
            }
            else if (product <= 0)
            {
                r = mid - 1;
            }
        }
        ans[i] = p[l].id + 1;
    }
    for (int i = 0; i < m; i++)
    {
        cout << ans[i] << '\n';
    }
    return 0;
}
