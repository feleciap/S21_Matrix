#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define INCORRECT_MATRIX 1
#define ERROR_CALCULATING 2
#define EPS 1.e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0

// s21_matrix
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_create_matrix(int rows, int columns, matrix_t *res);
void s21_remove_matrix(matrix_t *A);
int s21_check_matrix(matrix_t *matrix);

// s21_matrix_func
int s21_matrix_for_minor(matrix_t *A, int row, int col, matrix_t *result);
void s21_copy_matrix(matrix_t A, matrix_t *mat);
void s21_swapping(matrix_t *A, int k);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// s21_matrix_arithmetics
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int check_valid_arithmetic_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_is_empty(matrix_t *matrix);

#endif  // S21_MATRIX_H