#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void initialize_array(int arr[], int n) {
    for (int k = 0; k < n; k++) {
        arr[k] = -1;
    }
}

int memoization(int arr[], int n) {  // Using recursion + memoization
    if (arr[n] != -1)
        return arr[n];

    if (n <= 1) { // base case
        arr[n] = n;
        return arr[n];
    }

    arr[n] = memoization(arr, n - 1) + memoization(arr, n - 2);
    return arr[n];
}

int main() {
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    int* array = (int*) malloc((n + 1) * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    initialize_array(array, n + 1);

    clock_t start = clock();

    // Call memoized Fibonacci 10^6 times for performance measurement
    for (int i = 0; i < 1000000; i++) {
        memoization(array, n);
    }

    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken is : %f seconds\n", time_taken);

    printf("Fibonacci series up to %d terms is:\n", n);
    print_array(array, n + 1);

    free(array);
    return 0;
}
