#include <stdio.h>
#include <stdlib.h>

void matrix_multiply(int **A, int **B, int **C, int n) {

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        C[i][j] += A[i][k] * B[k][i];
      }
    }
  }
}

int **new_matrix(int size) {

  int **A = calloc(size, sizeof(int *));

  for (int i = 0; i < size; i++) {
    A[i] = calloc(size, sizeof(int));
  }
  return A;
}

int main(void) {

  int A_vals[3][3] = {{1, 2, 3}, {1, 2, 1}, {1, 1, 9}};
  int B_vals[3][3] = {{1, 2, 3}, {1, 2, 1}, {1, 1, 9}};
  int **A = new_matrix(3);
  int **B = new_matrix(3);
  int **C = new_matrix(3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A[i][j] = A_vals[i][j];
      B[i][j] = B_vals[i][j];
    }
  }

  matrix_multiply(A, B, C, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%d ", C[i][j]);
    }
    printf("\n");
  }
}
