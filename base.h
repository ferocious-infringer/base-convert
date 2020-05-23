#ifndef base
#define base base

int base_verify(char *, int, char *);
	// return: 0 if valid, -1 if invalid.
unsigned long long base_to_10(char *, int, char *);
int base_to_n(unsigned long long, int, char *, char *, int);
	// return: 0 if operation was successful, -1 if output is longer than buffer.

#endif
