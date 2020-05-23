#include "index.h"
#include "input.h"
#include "base.h"

unsigned long long base_i;
unsigned long long base_o;
unsigned long long base10;

#define buffermax 1024
char buffer[buffermax];
char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *lowercase = "abcdefghijklmnopqrstuvwxyz";

unsigned long long get_number(int, char *, int, int);

int main(int argc, char *argv[]) {
	base_i = get_number(10, "Initial base: ", 2, (int) strlen(digits));
	base_o = get_number(10, "Final base: ", 2, (int) strlen(digits));
	base10 = get_number((int) base_i, "Number in initial base: ", 1, 0);

	if (base_to_n(base10, (int) base_o, digits, buffer, buffermax))
		fprintf(stderr, "Error: Length of result exceeded buffer capacity. Only a partial of result will be displayed.\n");
	printf("Number in final base: %s\n", buffer);

	return 0;
}

unsigned long long get_number(int base, char *message, int min, int max) {
	unsigned long long number;
	for(;;) {
		get_input(buffer, buffermax, message);
		transform(buffer, uppercase, lowercase);
		if (base_verify(buffer, base, digits)) {
			fprintf(stderr, "Error: Input contains illegal characters. Please write in base %d.\n", base);
			continue;
		}
		number = base_to_10(buffer, base, digits);
		if (max >= min) {
			if (number < min) {
				fprintf(stderr, "Error: Input cannot be smaller than %d.\n", min);
				continue;
			}
			if (number > max) {
				fprintf(stderr, "Error: Input cannot be larger than %d.\n", max);
				continue;
			}
		}
		break;
	}
	return number;
}
