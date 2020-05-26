#include "main.h"
#include "base.h"
#include "help.h"

void error(int, char *, ...);
void transform(char [], char *, char *);
int compare(char *, int, ...);

#define buffermax 1024

#define digits "0123456789abcdefghijklmnopqrstuvwxyz"
#define uppercase "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define lowercase "abcdefghijklmnopqrstuvwxyz"

int main(int argc, char *argv[]) {
	char buffer[buffermax];
	strupr(buffer);

	char group = 'b';
	char display = 'r';
	char include = 0;

	char parse = 'b';
	int i, j;

	int base_count = 0;
	int base_start = 0;
	int base_max = strlen(digits);
	base10 base_temp;
	int number_count = 0;
	int number_start = 0;

	if (argc-1 == 0)
		error(-1, help_minimal);

	/*--------------------------------------------------
	 Parse options.
	--------------------------------------------------*/
	for (i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == '\0') {
				error(-1, help_minimal);
			}
			if (argv[i][1] == '-') {
				if (!compare(argv[i], 1, "--help")) {
					printf("%s", help_full);
					return 0;
				} else if (!strcmp(argv[i], "--group-base")) {
					group = 'b';
				} else if (!strcmp(argv[i], "--group-number")) {
					group = 'n';
				} else if (!strcmp(argv[i], "--display-row")) {
					display = 'r';
				} else if (!strcmp(argv[i], "--display-column")) {
					display = 'c';
				} else if (!strcmp(argv[i], "--include-head")) {
					include = 1;
				} else {
					error(-1, help_minimal);
				}
				continue;
			}
			for (j = 1; argv[i][j] != '\0'; j++)
				switch (argv[i][j]) {
				case 'h':
					printf("%s", help_full);
					return 0;
				case 'b':
					group = 'b';
					break;
				case 'n':
					group = 'n';
					break;
				case 'r':
					display = 'r';
					break;
				case 'c':
					display = 'c';
					break;
				case 'i':
					include = 1;
					break;
				default:
					error(-1, help_minimal);
				}
		} else break;
	}

	/*--------------------------------------------------
	 Count bases and numbers.
	--------------------------------------------------*/
	for (; i < argc; i++) {
		if (i == argc-1) parse = 'n';
		if (!compare(argv[i], 2, "-a", "--array")) {
			if (parse == 'b') {
				parse = 'n';
				continue;
			}
			if (parse == 'n') {
				error(-1, help_minimal);
			}
		} else {
			if (parse == 'b') {
				if (!base_start)
					base_start = i;
				base_count++;
			}
			if (parse == 'n') {
				if (!number_start)
					number_start = i;
				number_count++;
			}
		}
	}

	if (base_count < 2 || number_count < 1)
		error(-1, help_minimal);

	int base_end = base_start + base_count;
	int number_end = number_start + number_count;

	int bases[base_count];
	base10 numbers[number_count];

	/*--------------------------------------------------
	 Validate bases, and store them.
	--------------------------------------------------*/
	for (i = base_start, j = 0; i < base_end; i++, j++) {
		transform(argv[i], uppercase, lowercase);
		if (base_verify(argv[i], 10, digits))
			error(-1, "Error: '%s', from base number %d, is not written in base10.\n", argv[i], j+1);

		base_temp = base_to_10(argv[i], 10, digits);
		if (base_temp < 2)
			error(-1, "Error: '%llu', from base number %d, value cannot be smaller than 2.\n", base_temp, j+1);
		if (base_temp > base_max)
			error(-1, "Error: '%llu', from base number %d, value cannot be larger than %d\n", base_temp, j+1, base_max);

		bases[j] = (int) base_temp;
	}

	/*--------------------------------------------------
	 Validate numbers, and store them.
	--------------------------------------------------*/
	for (i = number_start, j = 0; i < number_end; i++, j++) {
		transform(argv[i], uppercase, lowercase);
		if (base_verify(argv[i], bases[0], digits))
			error(-1, "Error: '%s', from sequence number %d, is not written in base%d.\n", argv[i], j+1, bases[0]);
		numbers[j] = base_to_10(argv[i], bases[0], digits);
	}

	/*--------------------------------------------------
	 Display output, formatted.
	--------------------------------------------------*/
	if (group == 'b') {
		for (i = !include; i < base_count; i++) {
			for (j = 0; j < number_count; j++) {
				base_to_n(numbers[j], bases[i], digits, buffer, buffermax);
				printf("%s", buffer);
				if (display == 'r')
					putchar(' ');
				if (display == 'c')
					putchar('\n');
			}
			if (i < base_count-1)
				putchar('\n');
		}
	}
	if (group == 'n') {
		for (i = 0; i < number_count; i++) {
			for (j = !include; j < base_count; j++) {
				base_to_n(numbers[i], bases[j], digits, buffer, buffermax);
				printf("%s", buffer);
				if (display == 'r')
					putchar(' ');
				if (display == 'c')
					putchar('\n');
			}
			if (i < number_count-1)
				putchar('\n');
		}
	}
	if (display == 'r')
		putchar('\n');

	/*--------------------------------------------------
	 Exit safely.
	--------------------------------------------------*/
	return 0;
}

void error(int code, char *description, ...) {
	va_list args;
	va_start(args, description);
	vfprintf(stderr, description, args);
	va_end(args);
	exit(code);
}

void transform(char string[], char *initial, char *final) {
	for (int i = 0; string[i] != '\0'; i++)
		for (int j = 0; initial[j] != '\0'; j++)
			if (string[i] == initial[j]) {
				string[i] = final[j];
				break;
			}
}

int compare(char *string, int count, ...) {
	va_list args;
	va_start(args, count);
 	for (int i = 0; i < count; i++)
		if (!strcmp(string, va_arg(args, char *)))
			return 0;
	va_end(args);
	return -1;
}
