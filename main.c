const char *help_minimal = ""
	"usage: base-convert base1 base2 number                                           \n"
	"       base-convert {-i|--interactive}                                           \n"
	"       base-convert {-h|--help}                                                  \n";
const char *help_full = ""
	"Usage                                                                            \n"
	"        base-convert base1 base2 number                                          \n"
	"        base-convert {-i|--interactive}                                          \n"
	"        base-convert {-h|--help}                                                 \n"
	"                                                                                 \n"
	"Description                                                                      \n"
	"        Convert numbers from one base representation to another.                 \n"
	"                                                                                 \n"
	"Arguments                                                                        \n"
	"        number               : The number to be converted to another base.       \n"
	"                               This must be written in the representation of the \n"
	"                               initial base.                                     \n"
	"        base1                : Serve as the initial base for the number.         \n"
	"        base2                : The base that the number will converts into.      \n"
	"                                                                                 \n"
	"Options                                                                          \n"
	"        -i,                  : Use an interactive prompts to insert values.      \n"
	"        --interactive          When an input stream is entered incorrectly, this \n"
	"                               will trigger the entry to be re-entered in the    \n"
	"                               proper form.                                      \n"
	"        -h, --help           : Show this help file.                              \n"
	"                                                                                 \n"
	"Examples                                                                         \n"
	"                base-convert 2 10 1010010001010101                               \n"
	"        Show the representation of the number '1010010001010101' from base2 into \n"
	"        base10.                                                                  \n"
	"                                                                                 \n"
	"                base-convert --interactive                                       \n"
	"        Run in interactive mode, where number, base1 and base2 will be prompted  \n"
	"        for entry.                                                               \n";

#include "main.h"
#include "input.h"
#include "base.h"

char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
base10 base_i;
base10 base_o;
base10 decimal;

int assert_number(char *, int, base10, base10, base10 *, char *);
base10 get_number(int, base10, base10, char *, char *);
void show_number(base10, int, char *);

int main(int argc, char *argv[]) {
	switch (argc-1) {
	case 1:
		if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			printf("%s", help_full);
			break;
		}
		if (!strcmp(argv[1], "-i") || !strcmp(argv[1], "--interactive")) {
			base_i = get_number(10, 2, strlen(digits), "initial base", "Initial base: ");
			base_o = get_number(10, 2, strlen(digits), "final base", "Final base: ");
			decimal = get_number((int) base_i, 1, 0, "number", "Number in initial base: ");
			show_number(decimal, (int) base_o, "Number in final base: ");
			break;
		}
		goto error;
	case 3:
		if (
			assert_number(argv[1], 10, 2, strlen(digits), &base_i, "initial base") ||
			assert_number(argv[2], 10, 2, strlen(digits), &base_o, "final base") ||
			assert_number(argv[3], (int) base_i , 1, 0, &decimal, "number")
		) goto error;
		show_number(decimal, (int) base_o, "");
		break;
	default: goto error;
	}

	return 0;
	error:
		fprintf(stderr, "%s", help_minimal);
		return -1;
}

#define buffermax 1024
char buffer[buffermax];
char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *lowercase = "abcdefghijklmnopqrstuvwxyz";

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

base10 get_number(int base, base10 min, base10 max, char *name, char *message) {
	base10 number;
	for(;;) {
		get_input(buffer, buffermax, message);
		if (assert_number(buffer, base, min, max, &number, name))
			continue;
		break;
	}
	return number;
}

void show_number(base10 number, int base, char *message) {
	if (base_to_n(number, base, digits, buffer, buffermax))
		fprintf(stderr, "Error: Length of result exceeded buffer capacity. Only a partial of the result will be displayed.\n");
	printf("%s%s\n", message, buffer);
}
