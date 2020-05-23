#include "input.h"

void get_input(char buffer[], int buffermax, char *message) {
	int c;
	int i = 0;
	printf("%s", message);
	while ((c = getchar()) != EOF && c != '\n') {
		if (i >= buffermax-1) {
			fprintf(stderr, "Error: Input stream is too long. Expected maximum %d characters.\n", buffermax-1);
			exhaust_input();
			i = 0;
			printf("%s", message);
		}
		buffer[i++] = c;
	}
	buffer[i] = '\0';
}

void exhaust_input(void) {
	int c;
	while ((c = getchar()) != EOF && c != '\n');
}

void transform(char string[], char *initial, char *final) {
	for (int i = 0; string[i] != '\0'; i++)
		for (int j = 0; initial[j] != '\0'; j++)
			if (string[i] == initial[j]) {
				string[i] = final[j];
				break;
			}
}
