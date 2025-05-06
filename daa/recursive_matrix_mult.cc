#include <iostream>

class Matrix {
public:
  int size;
  int **mat;

  Matrix(int n) : size(n) {
    mat = new int *[size];
    for (int i = 0; i < n; i++) {
      mat[i] = new int[size];
      for (int j = 0; j < n; j++) {
        mat[i][j] = 0;
      }
    }
  }

  ~Matrix() {
    for (int i = 0; i < size; i++) {
      delete[] mat[i];
    }
    delete[] mat;
  }

  Matrix(const Matrix &other) : size(other.size) {
    mat = new int *[size];
    for (int i = 0; i < size; i++) {
      mat[i] = new int[size];
      for (int j = 0; j < size; j++) {
        mat[i][j] = other.mat[i][j];
      }
    }
  }

  Matrix operator+(const Matrix &B) const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        result.mat[i][j] = mat[i][j] + B.mat[i][j];
      }
    }
    return result;
  }

  Matrix operator-(const Matrix &B) const {
    Matrix result(size);
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        result.mat[i][j] = mat[i][j] - B.mat[i][j];
      }
    }
    return result;
  }

  void print() const {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        std::cout << mat[i][j] << " ";
      }
      std::cout << "\n";
    }
  }

  static Matrix *multiply(Matrix &A, Matrix &B) {

    int n = A.size;
    Matrix *result = new Matrix(n);

    if (n == 1) {
      result->mat[0][0] = A.mat[0][0] * B.mat[0][0];
      return result;
    }

    int new_size = n / 2;

    Matrix A11(new_size), A12(new_size), A21(new_size), A22(new_size);
    Matrix B11(new_size), B12(new_size), B21(new_size), B22(new_size);

    for (int i = 0; i < new_size; i++) {
      for (int j = 0; j < new_size; j++) {
        A11.mat[i][j] = A.mat[i][j];
        A12.mat[i][j] = A.mat[i][new_size + j];
        A21.mat[i][j] = A.mat[i + new_size][j];
        A22.mat[i][j] = A.mat[i + new_size][j + new_size];

        B11.mat[i][j] = B.mat[i][j];
        B12.mat[i][j] = B.mat[i][new_size + j];
        B21.mat[i][j] = B.mat[i + new_size][j];
        B22.mat[i][j] = B.mat[i + new_size][j + new_size];
      }
    }

    Matrix S1 = B12 - B22;
    Matrix S2 = A11 + A12;
    Matrix S3 = A21 + A22;
    Matrix S4 = B21 - B11;
    Matrix S5 = A11 + A22;
    Matrix S6 = B11 + B22;
    Matrix S7 = A12 - A22;
    Matrix S8 = B21 + B22;
    Matrix S9 = A11 - A21;
    Matrix S10 = B11 + B12;

    Matrix *P1 = multiply(A11, S1);
    Matrix *P2 = multiply(S2, B22);
    Matrix *P3 = multiply(S3, B11);
    Matrix *P4 = multiply(A22, S4);
    Matrix *P5 = multiply(S5, S6);
    Matrix *P6 = multiply(S7, S8);
    Matrix *P7 = multiply(S9, S10);

    Matrix C11 = *P5 + *P4 - *P2 + *P6;
    Matrix C12 = *P1 + *P2;

    Matrix C21 = *P3 + *P4;

    Matrix C22 = *P5 + *P1 - *P3 - *P7;

    for (int i = 0; i < new_size; i++) {
      for (int j = 0; j < new_size; j++) {
        result->mat[i][j] = C11.mat[i][j];
        result->mat[i][j + new_size] = C12.mat[i][j];
        result->mat[i + new_size][j] = C21.mat[i][j];
        result->mat[i + new_size][j + new_size] = C22.mat[i][j];
      }
    }

    return result;
  }
};

int main(void) {

  int n = 4;
  Matrix A(n), B(n);

  A.mat[0][0] = 1;
  A.mat[0][1] = 2;
  A.mat[0][2] = 3;
  A.mat[0][3] = 4;
  A.mat[1][0] = 5;
  A.mat[1][1] = 6;
  A.mat[1][2] = 7;
  A.mat[1][3] = 8;
  A.mat[2][0] = 9;
  A.mat[2][1] = 10;
  A.mat[2][2] = 11;
  A.mat[2][3] = 12;
  A.mat[3][0] = 13;
  A.mat[3][1] = 14;
  A.mat[3][2] = 15;
  A.mat[3][3] = 16;

  B.mat[0][0] = 1;
  B.mat[0][1] = 0;
  B.mat[0][2] = 0;
  B.mat[0][3] = 0;
  B.mat[1][0] = 0;
  B.mat[1][1] = 1;
  B.mat[1][2] = 0;
  B.mat[1][3] = 0;
  B.mat[2][0] = 0;
  B.mat[2][1] = 0;
  B.mat[2][2] = 1;
  B.mat[2][3] = 0;
  B.mat[3][0] = 0;
  B.mat[3][1] = 0;
  B.mat[3][2] = 0;
  B.mat[3][3] = 1;

  Matrix *C = Matrix::multiply(A, B);
  C->print();
  return 0;
}
