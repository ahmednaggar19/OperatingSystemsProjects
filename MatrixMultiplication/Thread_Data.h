#ifndef MATRIXMULTIPLICATION_THREAD_DATA_H
#define MATRIXMULTIPLICATION_THREAD_DATA_H

#include "Matrix.h"

/**
 * This structure holds arguments to be sent to thread functions
 *  matrix_A : first matrix
 *  matrix_B : second matrix
 *  result_matrix : matrix to hold the result
 *  target_row : the row to be involved in multiplication
 *  target_col : the column to be involved in multiplication
 */
typedef struct Thread_Matrix_Data {
    Matrix matrix_A;
    Matrix matrix_B;
    Matrix result_matrix;
    int target_row;
    int target_col;
}Thread_Matrix_Data;

#endif //MATRIXMULTIPLICATION_THREAD_DATA_H
