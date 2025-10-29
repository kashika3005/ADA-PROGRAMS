#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to generate random numbers in an array
void random_array(int arr[], int n) {
    for (int j = 0; j < n; j++) {
        arr[j] = rand() % 100; // random number 0–99
    }
}

// Function to dynamically allocate a square matrix
int** allocate_Matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }
    return matrix;
}

// Function to multiply two n×n matrices
int** multiply(int **mat1, int **mat2, int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0; // initialize to zero
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                matrix[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return matrix;
}

int main() {
    int n;
    printf("Enter order of matrix: ");
    scanf("%d", &n);

    // Each matrix has n*n elements → need n*n random numbers
    int* array1 = (int*)malloc(n * n * sizeof(int));
    int* array2 = (int*)malloc(n * n * sizeof(int));

    if (array1 == NULL || array2 == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }

    // Allocate matrices
    int** mat1 = allocate_Matrix(n);
    int** mat2 = allocate_Matrix(n);

    srand(time(0));
    random_array(array1, n * n);
    random_array(array2, n * n);

    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat1[i][j] = array1[k];
            mat2[i][j] = array2[k];
            k++;
        }
    }

    clock_t start = clock();
    for (int i = 0; i < 1000; i++) { // multiply 1000 times
        int** result = multiply(mat1, mat2, n);
        // Free result matrix after each multiplication to prevent memory leaks
        for (int r = 0; r < n; r++) {
            free(result[r]);
        }
        free(result);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to multiply 2 matrices of order %d (1000 times): %f seconds\n", n, time_taken);

    // Free all dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(mat1[i]);
        free(mat2[i]);
    }
    free(mat1);
    free(mat2);
    free(array1);
    free(array2);

    return 0;
}
