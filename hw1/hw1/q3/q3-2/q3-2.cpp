#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <vector>
using namespace std;
struct vec
{
    long long x;
    long long y;
    int id;
    int rank;
};

bool compare(const vec &v1, const vec &v2)
{
    double cross = v1.x * v2.y - v1.y * v2.x;
    // cout << v1.x << " " << v1.y << " " << "cross " << v2.x << " " << v2.y << '\n';
    // cout << "cross : " << cross << '\n';
    if (cross < 0)
    {
        // cout << v1.x << " " << v1.y << " " << "after " << v2.x << " " << v2.y << '\n';
        return false;
    }
    else if (cross > 0)
    {
        // cout << v1.x << " " << v1.y << " " << "before " << v2.x << " " << v2.y << '\n';
        return true;
    }
    else
    {
        double magV1 = v1.x * v1.x + v1.y * v1.y;
        double magV2 = v2.x * v2.x + v2.y * v2.y;
        return magV1 < magV2;
    }
}

int main()
{
    int n;
    cin >> n;
    vec *v = (vec *)calloc(n, sizeof(vec));
    long long minY = LLONG_MAX;
    long long minX = LLONG_MAX;
    int minId = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].x >> v[i].y;
        v[i].id = i + 1;
        if (v[i].x < minX || (v[i].x == minX && v[i].y < minY))
        {
            minX = v[i].x;
            minY = v[i].y;
            minId = i;
        }
    }
    vector<vec> vecs(n - 1);
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        if (i != minId)
        {
            vecs[idx].x = v[i].x - v[minId].x;
            vecs[idx].y = v[i].y - v[minId].y;
            vecs[idx].id = v[i].id;
            idx++;
        }
    }

    sort(vecs.begin(), vecs.end(), compare);
    cout << v[minId].id << ' ';
    for (int i = 0; i < (n - 1); i++)
    {
        cout << vecs[i].id << ' ';
    }
    cout << '\n';
    return 0;
}