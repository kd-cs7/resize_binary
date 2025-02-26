// cut and expand input file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHUNK_SIZE 16

int cut_file(FILE *input_file, FILE *output_file, long specified_size) {
	unsigned char *buf = (unsigned char *)malloc(CHUNK_SIZE);
	if (buf == NULL) {
		printf("Error: Memory allocation failed for buffer.\n");
		return 0;
	}

	size_t bytes_read;
	size_t total_bytes_read = 0;

	while (total_bytes_read < specified_size && (bytes_read = fread(buf, 1, CHUNK_SIZE, input_file)) > 0) {
		// Adjust the read size
		if (total_bytes_read + bytes_read > specified_size) {
			bytes_read = specified_size - total_bytes_read;
		}

		fwrite(buf, 1, bytes_read, output_file);
		total_bytes_read += bytes_read;
	}

	free(buf);
	return total_bytes_read == specified_size;
}

int expand_file(FILE *input_file, FILE *output_file, long specified_size) {
	unsigned char *buf = (unsigned char *)malloc(CHUNK_SIZE);
	if (buf == NULL) {
		printf("Error: Memory allocation failed for buffer.\n");
		return 0;
	}

	size_t bytes_read;
	size_t total_bytes_write = 0;

	while ((bytes_read = fread(buf, 1, CHUNK_SIZE, input_file)) > 0) {
		fwrite(buf, 1, bytes_read, output_file);
		total_bytes_write += bytes_read;
	}

	//padding
	while (total_bytes_write < specified_size) {
		size_t bytes_write;

		// Adjust the write size
		if (specified_size - total_bytes_write > CHUNK_SIZE) {
			bytes_write = CHUNK_SIZE;
		} else {
			bytes_write = specified_size - total_bytes_write;
		}
		
		memset(buf, 0, bytes_write);
		fwrite(buf, 1, bytes_write, output_file);
		total_bytes_write += bytes_write;
	}

	free(buf);
	return total_bytes_write == specified_size;
}

