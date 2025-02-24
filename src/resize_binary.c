#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

#define CHUNK_SIZE 16

int is_positive_integer(const char *str) {
	if (*str == 0) {
		return 0;
	}
	while (*str) {
		if (!isdigit(*str)) {
			return 0;
		}
		str++;
	}
	return 1;
}

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

int process_file(FILE *input_file, FILE *output_file, long specified_size) {
	unsigned char *buf = (unsigned char *)malloc(CHUNK_SIZE);
	if (buf == NULL) {
		printf("Error: Memory allocation failed for buffer.\n");
		return 0;
	}

	size_t bytes_read;
	size_t total_bytes_read = 0;

	while (total_bytes_read < specified_size && (bytes_read = fread(buf, 1, CHUNK_SIZE, input_file)) > 0) {
		// Adjust the read size if it exceeds the specified size
		if (total_bytes_read + bytes_read > specified_size) {
			bytes_read = specified_size - total_bytes_read;
		}

		fwrite(buf, 1, bytes_read, output_file);
		total_bytes_read += bytes_read;
	}

	free(buf);
	return total_bytes_read == specified_size;
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Error: Not enough arguments provided.\n");
		return 1;
	}

	// Open input file
	const char *input_filename = argv[1];
	FILE *input_file = open_file(input_filename, "rb");
	if (input_file == NULL) {
		return 1;
	}

	// Get input file size
	fseek(input_file, 0, SEEK_END);
	long input_file_size = ftell(input_file);
	if (input_file_size > LONG_MAX) {
		printf("Error: Input file size is too large.\n");
		fclose(input_file);
		return 1;
	}
	rewind(input_file);

	// Check the specified size for resizing
	if (!is_positive_integer(argv[2])) {
		printf("Error: Invalid resize input file size.\n");
		fclose(input_file);
		return 1;
	}
	long specified_size = atol(argv[2]);

	// Create output file name
	char *output_filename = create_output_filename(input_filename);
	if (output_filename == NULL) {
		printf("Error: Memory allocation failed for output filename.\n");
		fclose(input_file);
		return 1;
	}

	// Open output file
	FILE *output_file = open_file(output_filename, "wb");
	if (output_file == NULL) {
		free(output_filename);
		fclose(input_file);
		return 1;
	}

	// Read from input and write to output
	if (!process_file(input_file, output_file, specified_size)) {
		printf("Error: Failed to process the input file.\n");
		fclose(input_file);
		fclose(output_file);
		free(output_filename);
		return 1;
	}

	printf("File read successfully, %zu bytes processed.\n", specified_size);
	printf("Output file '%s' was created.\n", output_filename);

	fclose(input_file);
	fclose(output_file);
	free(output_filename);

	return 0;
}

