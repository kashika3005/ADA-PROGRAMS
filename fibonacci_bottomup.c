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

void bottom_up(int arr[], int n) {
    if (n <= 0)
        return;

    arr[0] = 0;
    if (n > 1)
        arr[1] = 1;

    for (int i = 2; i < n; i++) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }
}

int main() {
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    int* array = (int*) malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    clock_t start = clock();

    // Run bottom-up Fibonacci 10^6 times to test efficiency
    for (int i = 0; i < 1000000; i++) {
        bottom_up(array, n);
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Time taken is : %f seconds\n", time_taken);
    printf("Fibonacci series up to %d terms is:\n", n);
    print_array(array, n);

    free(array);
    return 0;
}
