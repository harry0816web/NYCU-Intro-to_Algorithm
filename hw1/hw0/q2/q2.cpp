#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    int *arr;
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}