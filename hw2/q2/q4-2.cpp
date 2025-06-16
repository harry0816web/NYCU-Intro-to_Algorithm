#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

long long less_than_target(long long mid, long long n)
{
    long long cnt = 0;
    for (long long i = 1; i <= n; i++)
    {
        cnt += min(mid / i, (long long)n);
    }
    return cnt;
}

int main()
{
    long long n;
    cin >> n;

    long long target = (n * n) / 2 + 1;
    long long left = 1, right = n * n, ans = -1;
    while (left <= right)
    {
        long long mid = left + (right - left) / 2;
        if (less_than_target(mid, n) < target)
        {
            left = mid + 1;
        }
        else if (less_than_target(mid, n) > target)
        {
            ans = mid;
            right = mid - 1;
        }
        else
        {
            ans = mid;
            break;
        }
    }

    cout << ans << '\n';
    return 0;
}
