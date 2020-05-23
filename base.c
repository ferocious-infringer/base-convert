#include "base.h"

int base_verify(char *string, int base, char *digits) {
	int i, j;
	for (i = 0; string[i] != '\0'; i++) {
		for (j = 0; digits[j] != '\0'; j++)
			if (string[i] == digits[j])
				break;
		if (j >= base)
			return -1;
	}
	return 0;
}

unsigned long long base_to_10(char *string, int base, char *digits) {
	unsigned long long number = 0;
	for (int i = 0; string[i] != '\0'; i++) {
		number *= base;
		for (int j = 0; digits[j] != '\0'; j++)
			if (string[i] == digits[j]) {
				number += j;
				break;
			}
	}
	return number;
}

int base_to_n(unsigned long long number, int base, char *digits, char *string, int buffermax) {
	int i = 0;
	while (number > 0) {
		if (i >= buffermax-1) {
			string[i] = '\0';
			return -1;
		}
		string[i++] = digits[number % base];
		number /= base;
	}
	string[i] = '\0';
	
	char c;
	int m = i-- / 2;
	for (int j = 0; j < m; j++, i--) {
		c = string[j];
		string[j] = string[i];
		string[i] = c;
	}

	return 0;
}
