#ifndef MATRIXMULTIPLICATION_FILE_PROCESSING_H
#define MATRIXMULTIPLICATION_FILE_PROCESSING_H

#include "Matrix.h"

/**
 * This function reads a matrix from a file.
 * @param file_name name of the file to be read
 * @return Matrix structure that contains the matrix read from file
 */
Matrix read_matrix (char* file_name);

/**
 * This function writes a matrix to a file.
 * @param file_name name of the file to which the matrix will be written
 * @param  matrix Matrix structure that contains the matrix to be written
 */
void write_matrix (char* file_name, Matrix matrix);

#endif //MATRIXMULTIPLICATION_FILE_PROCESSING_H
