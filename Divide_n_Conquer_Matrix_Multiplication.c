#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generate random array
void random_array(int arr[], int n) {
    for (int j = 0; j < n; j++) {
        arr[j] = rand() % 4;
    }
}

// Allocate and initialize matrix with zeros
int** allocate_Matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int)); // calloc initializes to 0
    }
    return matrix;
}

// Free matrix
void free_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

// Add two matrices
int** add_matrix(int **A, int **B, int n) {
    int** C = allocate_Matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Trim matrix (for odd-size handling)
int** trim_matrix(int** C, int n) {
    int** matrix = allocate_Matrix(n - 1);
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1; j++)
            matrix[i][j] = C[i][j];
    return matrix;
}

// Divide & Conquer matrix multiplication
int** Divide_and_Conquer(int **A, int **B, int n) {
    if (n == 1) {
        int** result = allocate_Matrix(1);
        result[0][0] = A[0][0] * B[0][0];
        return result;
    }

    if (n == 2) {
        int A11 = A[0][0], A12 = A[0][1];
        int A21 = A[1][0], A22 = A[1][1];
        int B11 = B[0][0], B12 = B[0][1];
        int B21 = B[1][0], B22 = B[1][1];

        int** C = allocate_Matrix(2);
        C[0][0] = A11 * B11 + A12 * B21;
        C[0][1] = A11 * B12 + A12 * B22;
        C[1][0] = A21 * B11 + A22 * B21;
        C[1][1] = A21 * B12 + A22 * B22;
        return C;
    }

    int newsize = (n % 2 == 0) ? n / 2 : (n + 1) / 2;
    int pad = (n % 2 == 0) ? 0 : 1;

    int** A_padded = allocate_Matrix(n + pad);
    int** B_padded = allocate_Matrix(n + pad);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A_padded[i][j] = A[i][j];
            B_padded[i][j] = B[i][j];
        }

    int N = n + pad;
    int** A11 = allocate_Matrix(newsize);
    int** A12 = allocate_Matrix(newsize);
    int** A21 = allocate_Matrix(newsize);
    int** A22 = allocate_Matrix(newsize);
    int** B11 = allocate_Matrix(newsize);
    int** B12 = allocate_Matrix(newsize);
    int** B21 = allocate_Matrix(newsize);
    int** B22 = allocate_Matrix(newsize);

    for (int i = 0; i < newsize; i++)
        for (int j = 0; j < newsize; j++) {
            A11[i][j] = A_padded[i][j];
            B11[i][j] = B_padded[i][j];
            A12[i][j] = A_padded[i][j + newsize];
            B12[i][j] = B_padded[i][j + newsize];
            A21[i][j] = A_padded[i + newsize][j];
            B21[i][j] = B_padded[i + newsize][j];
            A22[i][j] = A_padded[i + newsize][j + newsize];
            B22[i][j] = B_padded[i + newsize][j + newsize];
        }

    // Recursive multiplications
    int** M1 = Divide_and_Conquer(A11, B11, newsize);
    int** M2 = Divide_and_Conquer(A12, B21, newsize);
    int** M3 = Divide_and_Conquer(A11, B12, newsize);
    int** M4 = Divide_and_Conquer(A12, B22, newsize);
    int** M5 = Divide_and_Conquer(A21, B11, newsize);
    int** M6 = Divide_and_Conquer(A22, B21, newsize);
    int** M7 = Divide_and_Conquer(A21, B12, newsize);
    int** M8 = Divide_and_Conquer(A22, B22, newsize);

    // Combine results
    int** C11 = add_matrix(M1, M2, newsize);
    int** C12 = add_matrix(M3, M4, newsize);
    int** C21 = add_matrix(M5, M6, newsize);
    int** C22 = add_matrix(M7, M8, newsize);

    int** C = allocate_Matrix(N);
    for (int i = 0; i < newsize; i++)
        for (int j = 0; j < newsize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newsize] = C12[i][j];
            C[i + newsize][j] = C21[i][j];
            C[i + newsize][j + newsize] = C22[i][j];
        }

    if (pad == 1) {
        int** trimmed = trim_matrix(C, N);
        free_matrix(C, N);
        C = trimmed;
    }

    // Cleanup
    free_matrix(A11, newsize); free_matrix(A12, newsize);
    free_matrix(A21, newsize); free_matrix(A22, newsize);
    free_matrix(B11, newsize); free_matrix(B12, newsize);
    free_matrix(B21, newsize); free_matrix(B22, newsize);
    free_matrix(M1, newsize);  free_matrix(M2, newsize);
    free_matrix(M3, newsize);  free_matrix(M4, newsize);
    free_matrix(M5, newsize);  free_matrix(M6, newsize);
    free_matrix(M7, newsize);  free_matrix(M8, newsize);
    free_matrix(C11, newsize); free_matrix(C12, newsize);
    free_matrix(C21, newsize); free_matrix(C22, newsize);
    free_matrix(A_padded, N);  free_matrix(B_padded, N);

    return C;
}

int main(){
    int n;
    printf("Enter order of matrix: ");
    scanf("%d", &n);

    int* array1 = (int*)malloc(n * n * sizeof(int));
    int* array2 = (int*)malloc(n * n * sizeof(int));
    if (array1 == NULL || array2 == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }

    int** mat1 = allocate_Matrix(n);
    int** mat2 = allocate_Matrix(n);

    srand(time(0));
    random_array(array1, n * n);
    random_array(array2, n * n);

    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            mat1[i][j] = array1[k];
            mat2[i][j] = array2[k];
            k++;
        }

    clock_t start = clock();
    for (int i = 0; i < 100; i++) {  // reduce repetitions for safety
        int** res = Divide_and_Conquer(mat1, mat2, n);
        free_matrix(res, n);
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to multiply 2 matrices of order %d using divide and conquer: %f seconds\n", n, time_taken);

    free_matrix(mat1, n);
    free_matrix(mat2, n);
    free(array1);
    free(array2);

    return 0;
}
