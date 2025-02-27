#ifndef MAIN_H 
#define MAIN_H

#include <stdio.h>

FILE *open_file(const char *filename, const char *mode);
char *create_output_filename(const char *input_filename);
int cut_file(FILE *input_file, FILE *output_file, long specified_size);
int expand_file(FILE *input_file, FILE *output_file, long specified_size);
int is_positive_integer(const char *str);

#endif

