#include <iostream>
#include <vector>
using namespace std;
vector<long long> a(2 * 1e5), temp(2 * 1e5);

long long countSplit(int l, int mid, int r)
{
    int i = l, j = mid + 1;
    long long ans = 0;
    int k = l;

    while (i <= mid && j <= r)
    {
        // if a[i] > a[j], then a[i] > a[j+1], a[i+1] > a[j], a[i+2] > a[j]....... a[left] > a[j] (since left has been sorted)
        // so the number of inversion is mid - i + 1

        if (a[i] <= a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
            ans += (mid - i + 1);
        }
    }

    while (i <= mid)
        temp[k++] = a[i++];
    while (j <= r)
        temp[k++] = a[j++];

    for (int i = l; i <= r; i++)
        a[i] = temp[i];

    return ans;
}

long long countInversion(int l, int r)
{
    if (l >= r) // base case
        return 0;

    int mid = (l + r) / 2;
    long long left = countInversion(l, mid);
    long long right = countInversion(mid + 1, r);
    long long cross = countSplit(l, mid, r);

    return left + right + cross;
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout << countInversion(0, n - 1) << '\n';
    return 0;
}
