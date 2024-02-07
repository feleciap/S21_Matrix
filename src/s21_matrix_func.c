#include "s21_matrix.h"

int s21_matrix_for_minor(matrix_t *A, int row, int col, matrix_t *result) {
  int result_matrix = OK;
  int num_rows = A->rows;
  int num_columns = A->columns;
  int res_rows = num_rows - 1;
  int res_columns = num_columns - 1;

  if ((row >= A->rows || col >= A->columns) || num_rows < 2 ||
      num_columns < 2) {
  } else {
    if (s21_create_matrix(res_rows, res_columns, result) == OK) {
      for (int k = 0, i = 0; i < num_columns && k < res_columns; i++) {
        if (i == row) continue;
        for (int m = 0, j = 0; j < num_rows && m < res_rows; j++) {
          if (j == col) continue;
          result->matrix[k][m] = A->matrix[i][j];
          m++;
        }
        k++;
      }
    }
  }
  return result_matrix;
}

void s21_copy_matrix(matrix_t A, matrix_t *mat) {
  int i, j;
  for (i = 0; i < A.rows; i++) {
    for (j = 0; j < A.columns; j++) {
      mat->matrix[i][j] = A.matrix[i][j];
    }
  }
}

void s21_swapping(matrix_t *A, int k) {
  int j;
  double temp;
  for (j = 0; j < A->columns; j++) {
    temp = A->matrix[k][j];
    A->matrix[k][j] = A->matrix[k + 1][j];
    A->matrix[k + 1][j] = temp;
  }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int num_rows = A->rows;
  int num_columns = A->columns;
  int result_matrix = ERROR_CALCULATING;
  if (A == NULL || A->matrix == NULL) {
    result_matrix = INCORRECT_MATRIX;
  } else if (num_rows == num_columns) {
    s21_create_matrix(A->rows, A->columns, result);
    result_matrix = OK;
    if (num_rows == 1) {
      result->matrix[0][0] = 1.0;
    } else {
      for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_columns; j++) {
          double minor_determinant = 0;
          matrix_t minor = {0};
          if (s21_matrix_for_minor(A, i, j, &minor) != OK) {
            result_matrix = INCORRECT_MATRIX;
            s21_remove_matrix(&minor);
          }
          if (s21_determinant(&minor, &minor_determinant) != OK) {
            result_matrix = INCORRECT_MATRIX;
            s21_remove_matrix(&minor);
          }
          s21_remove_matrix(&minor);
          double complement = pow(-1, i + j) * minor_determinant;
          result->matrix[i][j] = complement;
        }
      }
    }
  }
  return result_matrix;
}

int s21_determinant(matrix_t *A, double *result) {
  int i = 0, return_result = OK;
  *result = 1;
  if (A->matrix == NULL || 0 < A->rows || 0 < A->columns) {
    if (A->rows != A->columns) {
      return_result = ERROR_CALCULATING;
    } else {
      matrix_t mat = {0};
      double elem;
      return_result = s21_create_matrix(A->rows, A->columns, &mat);
      for (i = 1; i < A->rows; i++) {
        for (int k = 0; k < i; k++) {
          if (A->matrix[k][k] == 0) {
            s21_swapping(A, k);
            *result *= -1;
          }
          if (A->matrix[i][k] != 0) {
            s21_copy_matrix(*A, &mat);
            elem = (-(A->matrix[i][k]) / A->matrix[k][k]);
            for (int j = 0; j < A->columns; j++) {
              mat.matrix[k][j] *= elem;
            }
            for (int j = 0; j < A->columns; j++) {
              A->matrix[i][j] += mat.matrix[k][j];
            }
          }
        }
      }
      for (i = 0; i < A->rows; i++) {
        *result *= A->matrix[i][i];
      }
      if (*result == 0) {
        *result = fabs(*result);
      }
      s21_remove_matrix(&mat);
    }
  } else {
    return_result = INCORRECT_MATRIX;
  }
  return return_result;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int return_result = OK;
  if (s21_is_empty(A)) {
    return_result = INCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    return_result = ERROR_CALCULATING;
  } else {
    double d = 0.0;
    return_result = s21_create_matrix(A->rows, A->columns, result);
    if (return_result == OK && A->rows) {
      s21_determinant(A, &d);
      if (fabs(d) < EPS) {
        return_result = ERROR_CALCULATING;
      } else if (A->rows == 1) {
        if (return_result == OK) {
          result->matrix[0][0] = A->matrix[0][0];
        }
      } else {
        matrix_t tmp1 = {0};
        s21_calc_complements(A, &tmp1);
        matrix_t tmp = {0};
        s21_transpose(&tmp1, &tmp);
        int size = A->rows;
        for (int i = 0; i < size; i++)
          for (int j = 0; j < size; j++)
            result->matrix[i][j] = tmp.matrix[i][j] / d;
        s21_remove_matrix(&tmp1);
        s21_remove_matrix(&tmp);
      }
    }
  }
  return return_result;
}