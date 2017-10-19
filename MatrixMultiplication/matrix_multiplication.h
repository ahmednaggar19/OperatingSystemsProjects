#include "Matrix.h"

#ifndef MATRIXMULTIPLICATION_MATRIX_MULTIPLICATION_H
#define MATRIXMULTIPLICATION_MATRIX_MULTIPLICATION_H

/**
 * This function multiply two matrices using N threads.
 * @param a first matrix
 * @param b second matrix
 * @return result matrix with int values and positive values for
 * col and row if multiplication was successful, and
 * negative values for col and row if failed
 * to multiply matrices
 */
Matrix multiply_matrices_N_threads (Matrix a, Matrix b);

/**
 * This function multiply two matrices using NxM threads.
 * @param a first matrix
 * @param b second matrix
 * @return esult matrix with int values and positive values for
 * col and row if multiplication was successful, and
 * negative values for col and row if failed
 * to multiply matrices
 */
Matrix multiply_matrices_NM_threads (Matrix a, Matrix b);

#endif //MATRIXMULTIPLICATION_MATRIX_MULTIPLICATION_H
