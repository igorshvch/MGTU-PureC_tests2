#ifndef BASIC_FILES
    #define BASIC_FILES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <locale.h>
    #include <conio.h>
    #include <windows.h>
#endif

#define CHUNK_SIZE 20000 //начальная длина строки

char* read_from_file(int test_mode, FILE *input, char *stream, char *file_name);
int write_to_file(char *file_name, char *my_string);