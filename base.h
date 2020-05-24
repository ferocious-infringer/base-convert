#ifndef base
#define base base

typedef unsigned long long int base10;

int base_verify(char *, int, char *);
// return: 0 if valid, -1 if invalid.

base10 base_to_10(char *, int, char *);

int base_to_n(base10, int, char *, char *, int);
// return: 0 if operation was successful,
//        -1 if output is longer than buffer.

#endif
