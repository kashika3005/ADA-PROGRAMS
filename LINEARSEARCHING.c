#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linear_search(int arr[], int size, int key) {
    int found = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == key) {
            printf("Element found at index: %d\n", i);
            found = 1;
        }
    }
    if (!found) {
        printf("Element not found in the array\n");
    }
    return -1;
}

void generate_random_array(int arr[], int n) {
    for (int j = 0; j < n; j++) {
        arr[j] = rand() % 10;  // random number between 0–9
    }
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int value;
    printf("Enter element to be searched between 0 to 9: ");
    scanf("%d", &value);

    int* array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }

    srand(time(0));  // seed for randomness
    generate_random_array(array, n);

    clock_t start = clock();
    linear_search(array, n, value);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to search %d is: %f seconds\n", value, time_taken);

    free(array);
    return 0;
}
