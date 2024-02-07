#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int return_result = SUCCESS;
  if (!s21_check_matrix(A) && !s21_check_matrix(B) &&
      A->columns == B->columns && A->rows == B->rows) {
    for (int i = 0; i < A->rows && return_result; i++) {
      for (int j = 0; j < A->columns && return_result; j++) {
        if (round(A->matrix[i][j] * pow(10, 7)) !=
            round(B->matrix[i][j] * pow(10, 7))) {
          return_result = FAILURE;
        }
      }
    }
  } else {
    return_result = FAILURE;
  }
  return return_result;
}

int s21_check_matrix(matrix_t *matrix) {
  int return_result = OK;
  if (matrix == NULL || matrix->matrix == NULL || matrix->rows <= 0 ||
      matrix->columns <= 0) {
    return_result = INCORRECT_MATRIX;
  }
  return return_result;
}

int s21_create_matrix(int rows, int columns, matrix_t *res) {
  int return_result = OK;
  if (!(columns > 0 && rows > 0 && res != NULL)) {
    return_result = INCORRECT_MATRIX;
  }
  if (!return_result) {
    res->matrix = NULL;
    res->rows = rows;
    res->columns = columns;
  }
  if (!return_result) {
    if (!(res->matrix = calloc(rows, sizeof(double *)))) {
      return_result = INCORRECT_MATRIX;
      res->matrix = NULL;
    }
  }
  for (int i = 0; i < rows && !return_result; i++) {
    if (!(res->matrix[i] = calloc(columns, sizeof(double)))) {
      res->rows = i;
      return_result = 1;
      s21_remove_matrix(res);
    }
  }
  return return_result;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  A->rows = 0;
  A->columns = 0;
}
