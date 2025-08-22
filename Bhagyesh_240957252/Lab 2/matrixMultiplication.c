#include <stdio.h>
#include <stdlib.h>

void readMatrix(int **mat, int rows, int cols) {
    printf("Enter elements:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", (*(mat + i) + j));
        }
    }
}

void printMatrix(int **mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(*(mat + i) + j));
        }
        printf("\n");
    }
}

void multiplyMatrices(int **a, int **b, int **result, int r1, int c1, int c2) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            *(*(result + i) + j) = 0;
            for (int k = 0; k < c1; k++) {
                *(*(result + i) + j) += *(*(a + i) + k) * *(*(b + k) + j);
            }
        }
    }
}

int main() {
    int r1, c1, r2, c2;
    printf("Enter rows and columns of first matrix: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter rows and columns of second matrix: ");
    scanf("%d %d", &r2, &c2);

    if (c1 != r2) {
        printf("Matrix multiplication not possible!\n");
        return 1;
    }

    int **a = (int **)malloc(r1 * sizeof(int *));
    int **b = (int **)malloc(r2 * sizeof(int *));
    int **result = (int **)malloc(r1 * sizeof(int *));
    for (int i = 0; i < r1; i++) {
        a[i] = (int *)malloc(c1 * sizeof(int));
        result[i] = (int *)malloc(c2 * sizeof(int));
    }
    for (int i = 0; i < r2; i++) {
        b[i] = (int *)malloc(c2 * sizeof(int));
    }

    printf("Enter first matrix:\n");
    readMatrix(a, r1, c1);

    printf("Enter second matrix:\n");
    readMatrix(b, r2, c2);

    multiplyMatrices(a, b, result, r1, c1, c2);

    printf("Resultant Matrix:\n");
    printMatrix(result, r1, c2);

    // Free memory
    for (int i = 0; i < r1; i++) {
        free(a[i]);
        free(result[i]);
    }
    for (int i = 0; i < r2; i++) {
        free(b[i]);
    }
    free(a);
    free(b);
    free(result);

    return 0;
}
