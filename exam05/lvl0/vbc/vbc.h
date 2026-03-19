#ifndef VBC_H
#define VBC_H

#include <stdio.h> // printf()
#include <ctype.h> // isdigit()
#include <unistd.h> // write()

int safe_write(int fd, const char *str, size_t len);
int print_unexpected_end(void);
int print_unexpected_token(char c);
int parse_factor(char *expr, int *pos, int len, int *error);
int parse_term(char *expr, int *pos, int len, int *error);
int parse_expression(char *expr, int *pos, int len, int *error);
int calculate(char *expr, int *error);

#endif
