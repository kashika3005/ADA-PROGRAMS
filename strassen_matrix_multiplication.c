#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int **allocate_Matrix(int n) {
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        mat[i] = (int *)malloc(n * sizeof(int));
    return mat;
}

void free_matrix(int **mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

void random_array(int *arr, int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 10; // values 0–9
}

void add_matrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void sub_matrix(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

int **Strassen_method(int **A, int **B, int n) {
    int **C = allocate_Matrix(n);

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int k = n / 2;

    // Allocate submatrices
    int **A11 = allocate_Matrix(k);
    int **A12 = allocate_Matrix(k);
    int **A21 = allocate_Matrix(k);
    int **A22 = allocate_Matrix(k);
    int **B11 = allocate_Matrix(k);
    int **B12 = allocate_Matrix(k);
    int **B21 = allocate_Matrix(k);
    int **B22 = allocate_Matrix(k);

    // Divide matrices into submatrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // Allocate temporary matrices
    int **M1, **M2, **M3, **M4, **M5, **M6, **M7;
    int **AResult = allocate_Matrix(k);
    int **BResult = allocate_Matrix(k);

    // M1 = (A11 + A22) * (B11 + B22)
    add_matrix(A11, A22, AResult, k);
    add_matrix(B11, B22, BResult, k);
    M1 = Strassen_method(AResult, BResult, k);

    // M2 = (A21 + A22) * B11
    add_matrix(A21, A22, AResult, k);
    M2 = Strassen_method(AResult, B11, k);

    // M3 = A11 * (B12 - B22)
    sub_matrix(B12, B22, BResult, k);
    M3 = Strassen_method(A11, BResult, k);

    // M4 = A22 * (B21 - B11)
    sub_matrix(B21, B11, BResult, k);
    M4 = Strassen_method(A22, BResult, k);

    // M5 = (A11 + A12) * B22
    add_matrix(A11, A12, AResult, k);
    M5 = Strassen_method(AResult, B22, k);

    // M6 = (A21 - A11) * (B11 + B12)
    sub_matrix(A21, A11, AResult, k);
    add_matrix(B11, B12, BResult, k);
    M6 = Strassen_method(AResult, BResult, k);

    // M7 = (A12 - A22) * (B21 + B22)
    sub_matrix(A12, A22, AResult, k);
    add_matrix(B21, B22, BResult, k);
    M7 = Strassen_method(AResult, BResult, k);

    // Combine results into C
    int **C11 = allocate_Matrix(k);
    int **C12 = allocate_Matrix(k);
    int **C21 = allocate_Matrix(k);
    int **C22 = allocate_Matrix(k);

    int **temp1 = allocate_Matrix(k);
    int **temp2 = allocate_Matrix(k);

    // C11 = M1 + M4 - M5 + M7
    add_matrix(M1, M4, temp1, k);
    sub_matrix(temp1, M5, temp2, k);
    add_matrix(temp2, M7, C11, k);

    // C12 = M3 + M5
    add_matrix(M3, M5, C12, k);

    // C21 = M2 + M4
    add_matrix(M2, M4, C21, k);

    // C22 = M1 - M2 + M3 + M6
    sub_matrix(M1, M2, temp1, k);
    add_matrix(temp1, M3, temp2, k);
    add_matrix(temp2, M6, C22, k);

    // Combine submatrices into result C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }

    // Free all allocated memory
    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(AResult, k); free_matrix(BResult, k);
    free_matrix(M1, k); free_matrix(M2, k); free_matrix(M3, k);
    free_matrix(M4, k); free_matrix(M5, k); free_matrix(M6, k); free_matrix(M7, k);
    free_matrix(C11, k); free_matrix(C12, k); free_matrix(C21, k); free_matrix(C22, k);
    free_matrix(temp1, k); free_matrix(temp2, k);

    return C;
}
int main() {
    int n, p;
    printf("Enter positive power of 2 for order of matrix:");
    scanf("%d", &p);
    n = pow(2, p);

    int* array1 = (int*)malloc((n*n) * sizeof(int));
    int* array2 = (int*)malloc((n*n) * sizeof(int));

    if (array1 == NULL || array2 == NULL) {
        printf("Memory allocation failed");
        return 0;
    }

    int **mat1 = allocate_Matrix(n);
    int **mat2 = allocate_Matrix(n);

    random_array(array1, (n*n));
    random_array(array2, (n*n));

    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mat1[i][j] = array1[k];
            mat2[i][j] = array2[k];
            k++;
        }
    }

    clock_t start = clock();
    for (int i = 0; i < 1000; i++) {
        int **result = Strassen_method(mat1, mat2, n);
        free_matrix(result, n); // ✅ Free after each iteration
    }
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to multiply 2 matrices of order %d using Strassen's method: %f seconds\n", n, time_taken);

    free(array1);
    free(array2);
    free_matrix(mat1, n);
    free_matrix(mat2, n);
    return 0;
}

