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

void iterative(int arr[], int n) {
    int a = 0;
    int b = 1;
    int c;

    // Generate Fibonacci series iteratively
    for (int i = 0; i < n; i++) {
        arr[i] = a;
        c = a + b;
        a = b;
        b = c;
    }
}

int main() {
    int n;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    int* array = (int*) malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    clock_t start = clock();

    // Repeat Fibonacci generation 10^6 times to measure performance
    for (int i = 0; i < 1000000; i++) {
        iterative(array, n);
    }

    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken is : %f seconds\n", time_taken);

    printf("Fibonacci series up to %d terms is: ", n);
    print_array(array, n);

    free(array);
    return 0;
}
