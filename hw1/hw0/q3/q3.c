/* probID: W0-C-MergeSortedArrays */
#include <stdio.h>
void MergeSortedArrays(int A[], int n, int B[], int m, int C[])
{
    int cnt = 0;
    int i = 0, j = 0;
    while (i < n && j < m)
    {
        if (A[i] <= B[j])
        {
            C[cnt] = A[i];
            cnt++;
            i++;
        }
        else
        {
            C[cnt] = B[j];
            cnt++;
            j++;
        }
    }
    while (i < n)
    {
        C[cnt] = A[i];
        cnt++;
        i++;
    }
    while (j < m)
    {
        C[cnt] = B[j];
        cnt++;
        j++;
    }
}