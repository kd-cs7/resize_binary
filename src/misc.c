// Miscellaneous functions

#include <ctype.h>

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
