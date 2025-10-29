#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Function to get 'n'th Fibonacci number (not the series)
int recursive(int n) {
    if (n <= 1)
        return n; // base case
    return recursive(n - 1) + recursive(n - 2);
}

// Function to generate Fibonacci series up to 'n' terms
void print_fib_series(int n) {
    for (int j = 0; j < n; j++) {
        recursive(j);
    }
}

int main() {
    int n;
    printf("Enter the number of terms: ");
    scanf("%d", &n);

    clock_t start = clock();

    // Call 10^6 times to measure performance
    for (int i = 0; i < 1000000; i++) {
        print_fib_series(n);
    }

    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken is : %f seconds\n", time_taken);

    return 0;
}
