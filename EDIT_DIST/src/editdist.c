#include "editdist.h"

/*
void test_single_compare(char *file_path1, char *file_path2, char *output_address, int verbose)
{
    //ќбъ€вление переменных
    int i;
    EMPT_CHAR_MATRIX *wrd_tbl1, *wrd_tbl2;

    //»нициализаци€ переменных
    //»нициализаци€ таблицы слов дл€ файла 1
    wrd_tbl1 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl1->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl1->table = (char**) calloc(wrd_tbl1->max_len, sizeof(char*));
    for (i = 0; i<wrd_tbl1->max_len; i++)
        wrd_tbl1->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    wrd_tbl1->rows = 0;
    //»нициализаци€ таблицы слов дл€ файла 2
    wrd_tbl2 = (EMPT_CHAR_MATRIX*) malloc(sizeof(EMPT_CHAR_MATRIX));
    wrd_tbl2->max_len = CHAR_MATRIX_ROWS;
    wrd_tbl2->table = (char**) calloc(wrd_tbl2->max_len, sizeof(char*));
    for (i = 0; i<wrd_tbl2->max_len; i++)
        wrd_tbl2->table[i] = (char*) calloc(WORD_LEN, sizeof(char));
    wrd_tbl2->rows = 0;

    compare(file_path1, file_path2, output_address, wrd_tbl1, wrd_tbl2, verbose);    
    
    free_2d_array_char(wrd_tbl1->table, wrd_tbl1->max_len, verbose);
    free_2d_array_char(wrd_tbl2->table, wrd_tbl2->max_len, verbose);
    free((void*) wrd_tbl1);
    free((void*) wrd_tbl2);
}


void compare(char *file_path1, char *file_path2, char *output_file_path, EMPT_CHAR_MATRIX* wt1, EMPT_CHAR_MATRIX* wt2, int verbose)
{
    char * F_NAME = "compare";
    if (verbose)
        printf("::%s ->\n\tвход в функицю\n", F_NAME);
    
    //ќбъ€вление переменных
    int res;
    double proc;
    char *str1, *str2, output[OUTPUT_STR_LEN];

    //»нициализаци€ переменных
    str1 = read_from_file(file_path1, verbose);
    str2 = read_from_file(file_path2, verbose);

    create_string_table(str1, wt1, verbose);
    create_string_table(str2, wt2, verbose);

    res = edit_distance_matrix(wt1, wt2, verbose);

    proc = 1.0 - ((double) res / ((double) (wt1->rows > wt2->rows ? wt1->rows : wt2->rows)));
    sprintf(output, "%s|%d|%s|%d|%d|%.6f", file_path1, wt1->rows, file_path2, wt2->rows, res, proc);
    write_to_file(output_file_path, output, "w", verbose);

    free((void*) str1);
    free((void*) str2);
}
*/

int edit_distance_matrix(EMPT_CHAR_MATRIX* wt1, EMPT_CHAR_MATRIX* wt2)
{
    int x_coord, y_coord, res, **matrix, i;
    
    matrix = create_zero_matrix(wt1->rows+1, wt2->rows+1);
    
    for (x_coord = 1; x_coord <= wt1->rows; x_coord++)
        matrix[x_coord][0] = matrix[x_coord-1][0] + 1;
    for (y_coord = 1; y_coord <= wt2->rows; y_coord++)
        matrix[0][y_coord] = matrix[0][y_coord-1] + 1;

    if (wt1->rows == 0)
        return wt2->rows;
    if (wt2->rows == 0)
        return wt1->rows;

    for (x_coord = 1; x_coord <= wt1->rows; x_coord++)
        for (y_coord = 1; y_coord <= wt2->rows; y_coord++)
            matrix[x_coord][y_coord] = MIN_3_VAL(
                matrix[x_coord-1][y_coord] + 1,
                matrix[x_coord][y_coord-1] + 1,
                matrix[x_coord-1][y_coord-1] + ((strcmp(wt1->table[x_coord], wt2->table[y_coord]) == 0) ? 0 : 1)
            );

    res = matrix[wt1->rows][wt2->rows];

    for (i=0; i<wt1->rows+1; i++)
        free((void *) matrix[i]);
    free ((void *) matrix);

    return res;
}

int** create_zero_matrix(int rows, int cols)
{
    int row;
    int **matrix;

    matrix = (int**) calloc(rows, sizeof(int));
    for (row = 0; row < rows; row++)
        matrix[row] = (int*) calloc(cols, sizeof(int));
    matrix[0][0] = 0;

    return matrix;
}
