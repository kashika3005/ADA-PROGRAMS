#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary Search Function
int binary_search(int arr[], int size, int key) {
    int low = 0, high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == key) {
            return mid;
        } 
        else if (arr[mid] > key) {
            high = mid - 1;
        } 
        else {
            low = mid + 1;
        }
    }

    return -1;
}

// Comparison function for qsort
int compare(const void* a, const void* b) {
    // Must dereference pointers, not cast directly to int
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int key;
    printf("Enter element to be searched (0–99): ");
    scanf("%d", &key);

    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }

    srand(time(0));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;  // random values 0–99
    }

    // Sort array before performing binary search
    qsort(arr, n, sizeof(int), compare);

    clock_t start = clock();
    int result = binary_search(arr, n, key);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (result != -1) {
        printf("Element %d found at index %d\n", key, result);
    } else {
        printf("Element %d not found in the array\n", key);
    }

    printf("Time taken to search %d is: %f seconds\n", key, time_taken);

    free(arr);
    return 0;
}
