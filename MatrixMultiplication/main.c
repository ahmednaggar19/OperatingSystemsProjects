#include <stdio.h>
#include "file_processing.h"
#include "matrix_multiplication.h"
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>


char* A_FILE = "a";
char* B_FILE = "b";
char* C_FILE = "c";

/**
 * This function produce a name of the output file by.
 * concatenating the desired file_name and int suffix
 * @param file_name desired output file name
 * @param suffix  number suffix
 * @return the new concatenated name
 */
char *get_method_file_name(char* file_name, int suffix) {
    int str_len = strlen(file_name);
    char* new_name = malloc(str_len + 3);
    new_name = strcpy(new_name,file_name);
    new_name[str_len] = '_';
    new_name[str_len + 1] = ('0' + suffix);
    new_name[str_len + 2] = '\0';
    return new_name;
}

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
    if (res.cols_count == -1) {
        return;
    }
    gettimeofday(&stop, NULL); //end checking time
    printf("Method 1:\nNumber of Threads : %d\n", a.rows_count);
    printf("Seconds taken: %lu s\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu us\n\n", stop.tv_usec - start.tv_usec);
    write_matrix(get_method_file_name(result_matrix_file_name, 1), res);
    // =================================================== //
    gettimeofday(&start, NULL); //start checking time
    res = multiply_matrices_NM_threads(a, b);
    gettimeofday(&stop, NULL); //end checking time
    printf("Method 2:\nNumber of Threads : %d\n", a.rows_count * b.cols_count);
    printf("Seconds taken %lu s\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu us\n", stop.tv_usec - start.tv_usec);
    write_matrix(get_method_file_name(result_matrix_file_name, 2), res);
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
        printf ("Invalid Number of arguments ! \n");
        return 0;
    }

    Matrix a = read_matrix(matrix_A_file_name);
    Matrix b = read_matrix(matrix_B_file_name);
    multiply_matrices(a, b, result_matrix_file_name);
}