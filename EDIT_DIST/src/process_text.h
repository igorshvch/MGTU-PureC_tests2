#include "readwrite.h"
#include "strtbl.h"
#include "editdist.h"

#ifndef EMPT_CHAR_MATRIX
    struct my_matrix {
        char** table;
        int rows;
        int max_len;
    };
    #define EMPT_CHAR_MATRIX struct my_matrix
    #define CHAR_MATRIX_ROWS 5000 //������������ ���������� ���� � �������
    #define WORD_LEN 400 //������������ ����� ������ �����
#endif


int count_edit_dist(int test_mode, char *path_file1, char *path_file2, FILE *input, char *stream1, char *stream2);