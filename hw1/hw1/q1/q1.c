/* probID: W1-A-InPlacePartition */
#include <stdio.h>
int In_Place_Partition(int A[], int left, int right, int key)
{
    int temp = A[left];
    A[left] = A[key];
    A[key] = temp;

    int i = left + 1;
    int j = right;
    while (i <= j)
    {
        // search left partition
        while (A[i] < A[left] && i <= j)
        {
            i++;
        }
        // search right partition
        while (A[j] > A[left] && j >= i)
        {
            j--;
        }
        if (i < j)
        {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            i++;
            j--;
        }
    }

    temp = A[left];
    A[left] = A[j];
    A[j] = temp;
    return j;
}
