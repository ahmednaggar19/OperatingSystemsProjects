#include <stdio.h>
#include "file_processing.h"
#include "matrix_multiplication.h"
#include <sys/time.h>


char* A_FILE = "a";
char* B_FILE = "b";
char* C_FILE = "c";

/**
 * function to multiply matrices using two different threading methods.
 * and output time usage and threads created.
 * @param a first matrix
 * @param b second matrix
 * @param result_matrix_file_name result matrix file name to which the matrix
 * will be saved
 */
void multiply_matrices(Matrix a, Matrix b, char* result_matrix_file_name) {
    Matrix res;
    struct timeval stop, start;
    gettimeofday(&start, NULL); //start checking time
    res = multiply_matrices_N_threads(a, b);
    gettimeofday(&stop, NULL); //end checking time
    printf("Method 1:\nNumber of Threads : %d\n", a.rows_count);
    printf("Seconds taken: %lu s\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu us\n", stop.tv_usec - start.tv_usec);
    gettimeofday(&start, NULL); //start checking time
    res = multiply_matrices_NM_threads(a, b);
    gettimeofday(&stop, NULL); //end checking time
    printf("Method 2:\nNumber of Threads : %d\n", a.rows_count * b.cols_count);
    printf("Seconds taken %lu s\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu us\n", stop.tv_usec - start.tv_usec);

    write_matrix(result_matrix_file_name,res);
}

int main (int argc, char* argv[]) {
    char* matrix_A_file_name;
    char* matrix_B_file_name;
    char* result_matrix_file_name;
    if (argc == 4) {
        matrix_A_file_name = argv[1];
        matrix_B_file_name = argv[2];
        result_matrix_file_name = argv[3];
    } else if (argc == 1) {
        matrix_A_file_name = A_FILE;
        matrix_B_file_name = B_FILE;
        result_matrix_file_name = C_FILE;
    } else {
        printf ("InValid Number of arguments ! \n");
        return 0;
    }

    Matrix a = read_matrix(matrix_A_file_name);
    Matrix b = read_matrix(matrix_B_file_name);
    multiply_matrices(a, b, result_matrix_file_name);
}