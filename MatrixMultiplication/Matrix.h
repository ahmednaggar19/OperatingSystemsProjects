#ifndef MATRIXMULTIPLICATION_MATRIX_H
#define MATRIXMULTIPLICATION_MATRIX_H

/**
 * This structue contains the matrix information.
 * values : 2D array of matrix values.
 * rows_count : number of matrix rows.
 * cols_count : number of matrix columns.
 */
typedef struct Matrix_Info {
    int** values;
    int rows_count;
    int cols_count;
} Matrix;

#endif //MATRIXMULTIPLICATION_MATRIX_H
