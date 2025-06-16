#include <iostream>
#include <vector>
#include <algorithm>

void bucketSort(std::vector<float>& arr) {
    int n = arr.size();
    if (n <= 0)
        return;

    // 1) Create n empty buckets
    std::vector<std::vector<float>> buckets(n);

    // 2) Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i]; // Index in bucket
        buckets[bucketIndex].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    for (int i = 0; i < n; i++) {
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (size_t j = 0; j < buckets[i].size(); j++) {
            arr[index++] = buckets[i][j];
        }
    }
}

int main() {
    std::vector<float> arr = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};

    bucketSort(arr);

    std::cout << "Sorted array is \n";
    for (float num : arr) {
        std::cout << num << " ";
    }
    return 0;
}
// Explanation of bucket division logic
// The logic for dividing elements into buckets is based on the assumption that the input array contains elements in the range [0, 1).
// Each element arr[i] is multiplied by n (the number of elements) to determine its bucket index.
// This ensures that elements are distributed uniformly across the buckets.
// If the data range is 1-10000 and there are 1000 elements, we need to adjust the bucket division logic.
// We can normalize the elements to the range [0, 1) by dividing each element by the maximum value (10000).
// Then, we can use the same logic as before to determine the bucket index.