#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#include "matrix_multiplication.h"
#include "Thread_Data.h"

void set_error_matrix (Matrix *matrix) {
    matrix->rows_count = -1;
    matrix->cols_count = -1;
    printf("Error in Dimensions");
}

void initialze_matrix_values (Matrix *matrix, int rows_length, int cols_length) {
    matrix->values = malloc(rows_length * (sizeof(int*)));
    for (int i = 0; i < rows_length; i++) {
        matrix->values[i] = malloc(cols_length * sizeof(int));
    }
    matrix->rows_count = rows_length;
    matrix->cols_count = cols_length;
}

void *multiply_row_by_matrix (void *thread_data) {
    struct Thread_Matrix_Data * thread_matrices;
    thread_matrices = (struct Thread_Matrix_Data *)thread_data;
    Matrix matrix_A = thread_matrices->matrix_A;
    Matrix matrix_B = thread_matrices->matrix_B;
    int row_index = thread_matrices->target_row;
    for (int i = 0; i < matrix_A.cols_count; i++) {
        int sum = 0;
        for (int j = 0; j < matrix_B.rows_count; j++) {
            sum += matrix_A.values[row_index][j] * matrix_B.values[j][i];
        }
        thread_matrices->result_matrix.values[row_index][i] = sum;
    }
    pthread_exit(NULL);
}

void *multiply_row_by_column (void *thread_data) {
    struct Thread_Matrix_Data * thread_matrices;
    thread_matrices = (struct Thread_Matrix_Data *)thread_data;
    Matrix matrix_A = thread_matrices->matrix_A;
    Matrix matrix_B = thread_matrices->matrix_B;
    int row_index = thread_matrices->target_row;
    int col_index = thread_matrices->target_col;
    int sum = 0;
    for (int i = 0; i < matrix_A.cols_count; i++) {
        sum += matrix_A.values[row_index][i] * matrix_B.values[i][col_index];
    }
    thread_matrices->result_matrix.values[row_index][col_index] = sum;
    pthread_exit(NULL);
}

Matrix multiply_matrices_N_threads (Matrix a, Matrix b) {
    Matrix result_matrix;
    // illegal multiplication check
    if (a.cols_count != b.rows_count) {
        set_error_matrix(&result_matrix);
        return result_matrix;
    }
    initialze_matrix_values(&result_matrix, a.rows_count, b.cols_count);
    pthread_t threads[a.rows_count];
    struct Thread_Matrix_Data thread_data[a.rows_count];
    int rc;
    for (int i = 0; i < a.rows_count; i++) {
        thread_data[i].matrix_A = a;
        thread_data[i].matrix_B = b;
        thread_data[i].result_matrix = result_matrix;
        thread_data[i].target_row = i;
        rc = pthread_create(&threads[i], NULL, multiply_row_by_matrix,
                            (void *)&thread_data[i]);

        if (rc) {
            //printf("Error:unable to create thread, %d" ,rc);
            set_error_matrix(&result_matrix);
            return result_matrix;
        }
    }
    void* status;
    for(int i = 0; i < a.rows_count; i++ ) {
        rc = pthread_join(threads[i], &status);
        if (rc) {
            //printf("Error:unable to create thread, %d" ,rc);
            set_error_matrix(&result_matrix);
            return result_matrix;
        }
    }
    return result_matrix;
}

Matrix multiply_matrices_NM_threads (Matrix a, Matrix b) {
    Matrix result_matrix;
    // illegal multiplication check
    if (a.cols_count != b.rows_count) {
        set_error_matrix(&result_matrix);
        return result_matrix;
    }
    initialze_matrix_values(&result_matrix, a.rows_count, b.cols_count);

    pthread_t threads[a.rows_count][b.cols_count];

    struct Thread_Matrix_Data thread_data[a.rows_count][b.cols_count];

    int rc;

    for (int i = 0; i < a.rows_count; i++) {
        for (int j = 0; j < b.cols_count; j++) {
            thread_data[i][j].matrix_A = a;
            thread_data[i][j].matrix_B = b;
            thread_data[i][j].result_matrix = result_matrix;
            thread_data[i][j].target_row = i;
            thread_data[i][j].target_col = j;
            rc = pthread_create(&threads[i][j], NULL, multiply_row_by_column,
                                (void *) &thread_data[i][j]);

            if (rc) {
                //printf("Error:unable to create thread, %d" ,rc);
                set_error_matrix(&result_matrix);
                return result_matrix;
            }
        }
    }
    void* status;
    for(int i = 0; i < a.rows_count; i++ ) {
        for (int j = 0; j < b.rows_count; j++) {
            rc = pthread_join(threads[i][j], &status);
            if (rc) {
                //printf("Error:unable to create thread, %d" ,rc);
                set_error_matrix(&result_matrix);
                return result_matrix;
            }
        }
    }
    return result_matrix;
}
