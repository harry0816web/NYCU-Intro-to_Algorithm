/* probID: W5-A-Quick-Select */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

long long k = 1000000007;

int fastpower(long long a, long n)
{
    if (n == 1)
        return a % k;
    else if (n == 0)
        return 1 % k;
    else
    {
        // odd power
        long long product = fastpower(a, n / 2);
        product = (product * product) % k;
        if (n % 2 == 1)
        {
            product = (product * a) % k;
        }
        return (int)product;
    }
}

int main()
{
    int n;
    cin >> n;
    while (n--)
    {
        int a, b;
        cin >> a >> b;
        int product = fastpower(a, b);
        cout << product << '\n';
    }
}