#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int** allocateMatrix(int n) {
    int **mat = (int**) malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        mat[i] = (int*) malloc(n * sizeof(int));
        memset(mat[i], 0, n * sizeof(int));
    }
    return mat;
}


void freeMatrix(int** mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}


void add(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}


void subtract(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}


void iterativeMultiply(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}


void divideAndConquerMultiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;

    
    int **A11 = allocateMatrix(newSize);
    int **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize);
    int **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize);
    int **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize);
    int **B22 = allocateMatrix(newSize);
    int **C11 = allocateMatrix(newSize);
    int **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize);
    int **C22 = allocateMatrix(newSize);
    int **M1 = allocateMatrix(newSize);
    int **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize);
    int **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize);
    int **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);

    
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    
    divideAndConquerMultiply(A11, B11, M1, newSize);
    divideAndConquerMultiply(A12, B21, M2, newSize);
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++)
            C11[i][j] = M1[i][j] + M2[i][j];

    divideAndConquerMultiply(A11, B12, M3, newSize);
    divideAndConquerMultiply(A12, B22, M4, newSize);
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++)
            C12[i][j] = M3[i][j] + M4[i][j];

    divideAndConquerMultiply(A21, B11, M5, newSize);
    divideAndConquerMultiply(A22, B21, M6, newSize);
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++)
            C21[i][j] = M5[i][j] + M6[i][j];

    divideAndConquerMultiply(A21, B12, M7, newSize);
    divideAndConquerMultiply(A22, B22, M4, newSize); // reuse M4
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++)
            C22[i][j] = M7[i][j] + M4[i][j];

   
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(M1, newSize); freeMatrix(M2, newSize);
    freeMatrix(M3, newSize); freeMatrix(M4, newSize);
    freeMatrix(M5, newSize); freeMatrix(M6, newSize);
    freeMatrix(M7, newSize);
}


void strassenMultiply(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;

    int **A11 = allocateMatrix(newSize);
    int **A12 = allocateMatrix(newSize);
    int **A21 = allocateMatrix(newSize);
    int **A22 = allocateMatrix(newSize);
    int **B11 = allocateMatrix(newSize);
    int **B12 = allocateMatrix(newSize);
    int **B21 = allocateMatrix(newSize);
    int **B22 = allocateMatrix(newSize);
    int **C11 = allocateMatrix(newSize);
    int **C12 = allocateMatrix(newSize);
    int **C21 = allocateMatrix(newSize);
    int **C22 = allocateMatrix(newSize);
    int **M1 = allocateMatrix(newSize);
    int **M2 = allocateMatrix(newSize);
    int **M3 = allocateMatrix(newSize);
    int **M4 = allocateMatrix(newSize);
    int **M5 = allocateMatrix(newSize);
    int **M6 = allocateMatrix(newSize);
    int **M7 = allocateMatrix(newSize);
    int **AResult = allocateMatrix(newSize);
    int **BResult = allocateMatrix(newSize);

   
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    
    add(A11, A22, AResult, newSize);
    add(B11, B22, BResult, newSize);
    strassenMultiply(AResult, BResult, M1, newSize);

    add(A21, A22, AResult, newSize);
    strassenMultiply(AResult, B11, M2, newSize);

    subtract(B12, B22, BResult, newSize);
    strassenMultiply(A11, BResult, M3, newSize);

    subtract(B21, B11, BResult, newSize);
    strassenMultiply(A22, BResult, M4, newSize);

    add(A11, A12, AResult, newSize);
    strassenMultiply(AResult, B22, M5, newSize);

    subtract(A21, A11, AResult, newSize);
    add(B11, B12, BResult, newSize);
    strassenMultiply(AResult, BResult, M6, newSize);

    subtract(A12, A22, AResult, newSize);
    add(B21, B22, BResult, newSize);
    strassenMultiply(AResult, BResult, M7, newSize);

    // Combine results
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
            C12[i][j] = M3[i][j] + M5[i][j];
            C21[i][j] = M2[i][j] + M4[i][j];
            C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
        }
    }

    // Combine final C matrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }

    // Free memory
    freeMatrix(A11, newSize); freeMatrix(A12, newSize);
    freeMatrix(A21, newSize); freeMatrix(A22, newSize);
    freeMatrix(B11, newSize); freeMatrix(B12, newSize);
    freeMatrix(B21, newSize); freeMatrix(B22, newSize);
    freeMatrix(C11, newSize); freeMatrix(C12, newSize);
    freeMatrix(C21, newSize); freeMatrix(C22, newSize);
    freeMatrix(M1, newSize); freeMatrix(M2, newSize);
    freeMatrix(M3, newSize); freeMatrix(M4, newSize);
    freeMatrix(M5, newSize); freeMatrix(M6, newSize);
    freeMatrix(M7, newSize); freeMatrix(AResult, newSize);
    freeMatrix(BResult, newSize);
}

// Print matrix
void printMatrix(int **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

int main() {
    int n;
    printf("Enter size of matrices (power of 2): ");
    scanf("%d", &n);

    int **A = allocateMatrix(n);
    int **B = allocateMatrix(n);
    int **C = allocateMatrix(n);

    printf("Enter matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    printf("\nIterative Multiplication Result:\n");
    iterativeMultiply(A, B, C, n);
    printMatrix(C, n);

    printf("\nDivide and Conquer Multiplication Result:\n");
    for (int i = 0; i < n; i++)
        memset(C[i], 0, n * sizeof(int));
    divideAndConquerMultiply(A, B, C, n);
    printMatrix(C, n);

    printf("\nStrassen's Multiplication Result:\n");
    for (int i = 0; i < n; i++)
        memset(C[i], 0, n * sizeof(int));
    strassenMultiply(A, B, C, n);
    printMatrix(C, n);

    freeMatrix(A, n);
    freeMatrix(B, n);
    freeMatrix(C, n);
    return 0;
}
