#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_result = SUCCESS;
  if (A->matrix != NULL && B->matrix != NULL && 0 < A->rows && 0 < B->rows &&
      0 < A->columns && 0 < B->columns) {
    if ((A->rows != B->rows) || (A->columns != B->columns)) {
      return_result = ERROR_CALCULATING;
    } else {
      return_result = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  } else {
    return_result = INCORRECT_MATRIX;
  }
  return return_result;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_result = OK;
  if (s21_is_empty(A) || s21_is_empty(A)) {
    return_result = 1;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    return_result = ERROR_CALCULATING;
  } else if (!return_result) {
    return_result = s21_create_matrix(A->rows, A->columns, result);
    if (!return_result) {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return return_result;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int return_result = s21_create_matrix(A->rows, A->columns, result);

  if (return_result == OK) {
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
  }

  return return_result;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_result = OK;
  if (s21_is_empty(A) || s21_is_empty(B)) {
    return_result = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    return_result = ERROR_CALCULATING;
  } else {
    return_result = s21_create_matrix(A->rows, B->columns, result);

    if (!return_result) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int m = 0; m < B->rows; m++)
            result->matrix[i][j] += A->matrix[i][m] * B->matrix[m][j];
        }
      }
    }
  }

  return return_result;
}

int s21_is_empty(matrix_t *matrix) {
  int res = 0;
  if (matrix == NULL || matrix->matrix == NULL || matrix->rows <= 0 ||
      matrix->columns <= 0) {
    res = 1;
  } else {
    res = 0;
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int return_result = OK;
  if (A->matrix == NULL || 0 > A->rows || 0 > A->columns) {
    return_result = INCORRECT_MATRIX;
  } else {
    return_result = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return return_result;
}