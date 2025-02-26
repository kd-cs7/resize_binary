// manage input and output files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 16

FILE *open_file(const char *filename, const char *mode) {
	FILE *file = fopen(filename, mode);
	if (file == NULL) {
		printf("Error: Could not open file '%s'.\n", filename);
	}
	return file;
}

char *create_output_filename(const char *input_filename) {
	size_t input_filename_len = strlen(input_filename);
	char *output_filename = (char *)malloc(input_filename_len + 9); // Add "resized_" and '\0'
	if (output_filename == NULL) {
		return NULL;
	}
	strcpy(output_filename, "resized_");
	strcat(output_filename, input_filename);
	return output_filename;
}

