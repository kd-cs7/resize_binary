// main file

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

	if(specified_size <= input_file_size) {
		// Cut file 
		if (!cut_file(input_file, output_file, specified_size)) {
			printf("Error: Failed to process the input file.\n");
			fclose(input_file);
			fclose(output_file);
			free(output_filename);
			return 1;
		}
	} else {
		// Expand file
		if (!expand_file(input_file, output_file, specified_size)) {
			printf("Error: Failed to process the input file.\n");
			fclose(input_file);
			fclose(output_file);
			free(output_filename);
			return 1;
		}
	}

	printf("File process successfully, %zu bytes processed.\n", specified_size);
	printf("Output file '%s' was created.\n", output_filename);

	fclose(input_file);
	fclose(output_file);
	free(output_filename);

	return 0;
}

