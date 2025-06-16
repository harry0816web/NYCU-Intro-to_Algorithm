#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
#define aaa cout << x[r + 1] << "----" << x[l] << endl;
const int maxn = 205;
double x[maxn << 2]; // 所有的x的数据
// 每一条线段
struct segment
{
    double y;
    double l;
    double r;
    int flag; // 1 or -1: 入边or出边
    segment() {}
    segment(double y, double l, double r, int flag) : y(y), l(l), r(r), flag(flag) {}
    bool operator<(const segment &res)
    {
        return y < res.y;
    }
} seg[maxn << 1];

// 线段树维护所有的单位线段（离散后的）
struct node
{
    int cov;
    double len;
} node[maxn << 2];
void pushdown(int rt, int l, int r)
{
    if (node[rt].cov)
        node[rt].len = x[r + 1] - x[l];
    else if (l == r)
        node[rt].len = 0;
    else
        node[rt].len = node[rt << 1].len + node[rt << 1 | 1].len;
}
void update(int rt, int l, int r, int L, int R, int cov)
{
    if (L <= l && r <= R)
    {
        node[rt].cov += cov;
        pushdown(rt, l, r);
        return;
    }
    int mid = (l + r) >> 1;
    if (L <= mid)
        update(rt << 1, l, mid, L, R, cov);
    if (R > mid)
        update(rt << 1 | 1, mid + 1, r, L, R, cov);
    // pushdown
    pushdown(rt, l, r);
    return;
}

int main()
{
    int n;
    int q = 1;
    memset(x, 0, sizeof x);
    scanf("%d", &n);
    double x1, y1, x2, y2;
    int count = 0;
    for (int i = 0; i < n; ++i)
    {
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        seg[count] = segment(y1, x1, x2, 1);
        x[count++] = x1;
        seg[count] = segment(y2, x1, x2, -1);
        // segment[i].y = y1;segment[i].l = x1;segment[i].r = x2;segment[i].flag = 1;
        // segment[i + 1].y = y2;segment[i + n].l = x1;segment[i + n].r = x2;segment[i + n].flag = -1;

        x[count++] = x2;
    }
    // 离散
    sort(seg, seg + count);
    sort(x, x + count);

    int sz = unique(x, x + count) - x;
    double ans = 0;
    for (int i = 0; i < count; ++i)
    {
        int l = lower_bound(x, x + sz, seg[i].l) - x;
        int r = lower_bound(x, x + sz, seg[i].r) - x - 1;
        update(1, 0, sz, l, r, seg[i].flag);
        ans += node[1].len * (seg[i + 1].y - seg[i].y);
    }
    printf("%d\n", (int)ans);
}
