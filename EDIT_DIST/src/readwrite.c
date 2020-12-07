#include "readwrite.h"

char* read_from_file(int test_mode, FILE *input, char *stream, char *file_name)
{
    int c, i, j;
    char *my_string;

    if (!test_mode) {
        input = fopen(file_name, "r");
    }

    i = 0;
    my_string = (char*) calloc(CHUNK_SIZE, sizeof(char));

    while (i < CHUNK_SIZE-1) {
        if (!test_mode) {
            if ((c=fgetc(input)) == '|')
                break;
        }
        else {
            c = stream[i];
            if (c == '|')
                break;
        }
        my_string[i] = c;
        i++;
    }
    my_string[i++] = c;
    my_string[i] = '\0';
    
    if (!test_mode)
        fclose(input);

    return my_string;
}


int write_to_file(char *file_name, char *my_string)
{
    FILE *output;

    output = fopen(file_name, "a");

    fprintf(output,  "%s\n", my_string);

    fclose(output);
    return 0;
}