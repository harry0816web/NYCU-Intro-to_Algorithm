/* probID: W3-A-QuickSort */
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <cstdlib>

using namespace std;
int In_Place_Partition(int A[], int left, int right, int key)
{
    // replace left with key
    int temp = A[key];
    A[key] = A[left];
    A[left] = temp;

    int l = left + 1;
    int r = right;
    while (l <= r)
    {
        while (A[l] <= A[left] && l <= r)
        {
            l++;
        }
        while (A[r] >= A[left] && r >= l)
        {
            r--;
        }

        if (l < r)
        {
            temp = A[l];
            A[l] = A[r];
            A[r] = temp;
            l++;
            r--;
        }
    }
    // when l >= r, means that no more interval needs to be processed
    // r points to the final position where the key should be
    temp = A[left];
    A[left] = A[r];
    A[r] = temp;
    return r;
}

void recursive_quick_sort(int A[], int left, int right)
{
    // 1. If right - left < 1, then return.
    if (right - left < 1)
        return;
    // 2. Pick a random index from [left...right], say, i.
    int i = left + rand() % (right - left + 1);

    // 3. Partition around the randomly picked index.
    int key = In_Place_Partition(A, left, right, i);

    recursive_quick_sort(A, left, key - 1);
    recursive_quick_sort(A, key + 1, right);
}

void quick_sort(int A[], int n)
{
    recursive_quick_sort(A, 0, n - 1);
}
