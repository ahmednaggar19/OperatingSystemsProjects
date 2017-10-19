#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_processing.h"

#define MAT_INFO_MAX_LENGTH 100

char* ROW = "row";
char* COL = "col";
char EQUAL = '=';
char SPACE = ' ';
char NULL_CHAR = '\0';

typedef struct matrix_info {
    int rows_count;
    int cols_count;
};

int get_attribute_value (char* attribute, char* str) {
    char* occurrence_pointer = strstr(str, attribute);
    int str_len = strlen(str);
    if (occurrence_pointer != NULL) {
        int i;
        for (i = 0; i < str_len; i++) {
            if (&str[i] == occurrence_pointer) {
                break;
            }
        }
        while (i < str_len && str[i] != EQUAL) {
            i++;
        }
        if (i < str_len && str[i] == EQUAL) {
            i++;
            int start = i;
            while (i < str_len && str[i] != SPACE) {
                i++;
            }
            char* number = malloc(i - start + 1);
            number = strncpy(number, &str[start], i - start);
            number[i - start + 1] = NULL_CHAR;
            return atoi(number);
        }
    }
    return -1;
}

struct matrix_info get_matrix_info (char * str) {
    struct matrix_info mat_info;
    mat_info.rows_count = get_attribute_value(ROW, str);
    mat_info.cols_count = get_attribute_value(COL, str);
    return mat_info;
}

Matrix read_matrix (char* file_name) {
    FILE* file_pointer;
    file_pointer = fopen(file_name, "r");
    Matrix matrix;
    if (file_pointer != NULL) {
        char matrix_info_str[MAT_INFO_MAX_LENGTH];
        if (fgets(matrix_info_str, sizeof matrix_info_str, file_pointer) != NULL) {
            struct matrix_info mat_info = get_matrix_info(matrix_info_str);
            int** elements = malloc(mat_info.rows_count * (sizeof (int*)));
            for (int i = 0; i < mat_info.rows_count; i++) {
                elements[i] = malloc(mat_info.cols_count * sizeof(int));
            }
            for (int i = 0; i < mat_info.rows_count; i++) {
                for (int j = 0; j < mat_info.cols_count; j++) {
                    fscanf(file_pointer, "%d", &elements[i][j]);
                }
            }
            matrix.values = elements;
            matrix.rows_count = mat_info.rows_count;
            matrix.cols_count = mat_info.cols_count;
        } else {
            printf ("Error : Unable to read matrix info\n");
        }
        fclose(file_pointer);
    } else {
        printf ("Error : Unable to access this file\n");
    }
    return matrix;
}

void write_matrix (char* file_name, Matrix matrix) {
    FILE* file_pointer;
    file_pointer = fopen(file_name, "w");
    if (file_pointer != NULL) {
        for (int i = 0; i < matrix.rows_count; i++) {
            for (int j = 0; j < matrix.cols_count; j++) {
                fprintf(file_pointer, "%d\t", matrix.values[i][j]);
            }
            fprintf(file_pointer, "\n");
        }
        fclose(file_pointer);
    } else {
        printf ("Error : Unable to access this file\n");
    }
}
