/* probID: W5-A-Quick-Select */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int In_Place_Partition(int A[], int left, int right, int key)
{
    int temp = A[left]; // store pivot
    A[left] = A[key];   // shift pivot to left
    A[key] = temp;
    int i = left + 1;
    int j = right;
    while (i <= j) // if cross, means that the search has done
    {
        // search left partition
        while (A[i] <= A[left] && i <= j) // if val < pivot, expand the size of left interval
        {
            i++;
        }
        // search right partition
        while (A[j] >= A[left] && j >= i) // if val > pivot, expand the size of right interval
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

int quick_select(int A[], int left, int right, int k)
{
    srand(time(NULL));
    // 1. If left == right
    // return A[left].
    if (left == right)
        return A[left];

    // 2. Pick a random index from [left...right], say, i.
    int i = left + rand() % (right - left + 1);

    // 3. key <-- In_Place_Partition(A, left, right, i);
    int key = In_Place_Partition(A, left, right, i);

    // 4. if A[key] is k-th smallest element, i.e., key == left+k-1,
    // then return A[key].
    int target = left + k - 1;
    if (key == target)
    {
        return A[key];
    }

    // 5. if the k-th smallest element is in A[left ~ key-1],
    // then recurse on A[left...key-1].
    // otherwise, // the k-th smallest element is in A[key + 1 ~ right],
    // then recurse on A[key+1...right]
    else if (key > target)
    {
        return quick_select(A, left, key - 1, k);
    }
    else
    {
        return quick_select(A, key + 1, right, k - (key - left + 1)); // Correct the k value for the right side
    }
}