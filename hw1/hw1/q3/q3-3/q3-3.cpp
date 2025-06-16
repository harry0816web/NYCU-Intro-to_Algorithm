#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <stack>
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
    if (cross < 0)
    {
        return false;
    }
    else if (cross > 0)
    {
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

    vector<vec> hulls;
    hulls.push_back(v[minId]);
    hulls[0].x = 0;
    hulls[0].y = 0;
    hulls.push_back(vecs[0]);
    idx = 1;
    for (int i = 1; i < (int)vecs.size(); i++)
    {
        hulls.push_back(vecs[i]);
        idx++;

        // there might be multiple invalid points
        while (idx > 1)
        {
            vec v1 = {hulls[idx - 1].x - hulls[idx - 2].x, hulls[idx - 1].y - hulls[idx - 2].y};
            vec v2 = {hulls[idx].x - hulls[idx - 2].x, hulls[idx].y - hulls[idx - 2].y};
            double cross = v1.x * v2.y - v1.y * v2.x;

            if (cross <= 0)
            {
                hulls[idx - 1] = hulls[idx];
                idx--;
                hulls.pop_back();
            }
            else
            {
                break; // guarantees that once a valid point is found, all invalid points (including multiple consecutive right turns or collinear points) are eliminated before continuing to the next point
            }
        }
    }

    cout << (int)hulls.size() + 1 << '\n';
    for (int i = 0; i < (int)hulls.size(); i++)
    {
        cout << hulls[i].id << ' ';
    }
    cout << hulls[0].id << '\n';
    return 0;
}