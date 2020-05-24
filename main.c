#include "main.h"
#include "base.h"
#include "help.h"

void transform(char string[], char *initial, char *final) {
	for (int i = 0; string[i] != '\0'; i++)
		for (int j = 0; initial[j] != '\0'; j++)
			if (string[i] == initial[j]) {
				string[i] = final[j];
				break;
			}
}

char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *lowercase = "abcdefghijklmnopqrstuvwxyz";

int main(int argc, char *argv[]) {
	if (argc-1 == 1 && (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))) {
		printf("%s", help_full);
	} else if (argc-1 >= 3) {
		const int buffermax = 1024;
		char buffer[buffermax];
		base10 decimal;
		int basemax = strlen(digits);
		int i;

		for (i = 0; i < argc; i++)
			transform(argv[i], uppercase, lowercase);

		if (base_verify(argv[1], 10, digits) || base_verify(argv[2], 10, digits)) {
			fprintf(stderr, "Error: Bases contains illegal characters. Please write them in base10.\n");
			return -1;
		}

		base10 base_i = base_to_10(argv[1], 10, digits);
		base10 base_o = base_to_10(argv[2], 10, digits);

		if (base_i < 2 || base_o < 2 || base_i > basemax || base_o > basemax) {
			fprintf(stderr, "Error: Bases have illegal value. Make sure they are within the range of 2 and %d.\n", basemax);
			return -1;
		}

		for (int i = 3; i < argc; i++) {
			if (base_verify(argv[i], (int) base_i, digits)) {
				fprintf(stderr, "Error: The number '%s' contains characters that is not part of base%llu.\n", argv[i], base_i);
				return -1;
			}
		}

		for (i = 3; i < argc; i++) {
			decimal = base_to_10(argv[i], (int) base_i, digits);
			base_to_n(decimal, (int) base_o, digits, buffer, buffermax);
			printf("%s%c", buffer, (i == argc-1)? '\n' : ' ');
		}
	} else {
		fprintf(stderr, "%s", help_minimal);
		return -1;
	}
	return 0;
}
