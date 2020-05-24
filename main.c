#include "main.h"
#include "base.h"
#include "help.h"

void transform(char [], char *, char *);
int assert_number(char *, int, base10, base10, base10 *, char *);

char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *lowercase = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, char *argv[]) {
	const int buffermax = 1024;
	char buffer[buffermax];
	base10 base_i;
	base10 base_o;
	base10 decimal;

	if (argc-1 == 1 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		printf("%s", help_full);
	} else if (argc-1 == 3) {
		if (
			assert_number(argv[1], 10, 2, strlen(digits), &base_i, "initial base") ||
			assert_number(argv[2], 10, 2, strlen(digits), &base_o, "final base") ||
			assert_number(argv[3], (int) base_i , 1, 0, &decimal, "number")
		) return -1;
		if (base_to_n(decimal, (int) base_o, digits, buffer, buffermax))
			fprintf(stderr, "Error: Length of result exceeded buffer capacity. Only a partial of the result will be displayed.\n");
		printf("%s\n", buffer);
	} else {
		fprintf(stderr, "%s", help_minimal);
		return -1;
	}

	return 0;
}

void transform(char string[], char *initial, char *final) {
	for (int i = 0; string[i] != '\0'; i++)
		for (int j = 0; initial[j] != '\0'; j++)
			if (string[i] == initial[j]) {
				string[i] = final[j];
				break;
			}
}

int assert_number(char *string, int base, base10 min, base10 max, base10 *number, char *name) {
	transform(string, uppercase, lowercase);
	if (base_verify(string, base, digits)) {
		fprintf(stderr, "Error: %s contains illegal characters. Please write in base %d.\n", name, base);
		return -1;
	}
	*number = base_to_10(string, base, digits);
	if (max >= min) {
		if (*number < min) {
			fprintf(stderr, "Error: %s cannot be smaller than %llu.\n", name, min);
			return -2;
		}
		if (*number > max) {
			fprintf(stderr, "Error: %s cannot be larger than %llu.\n", name, max);
			return -3;
		}
	}
	return 0;
}
