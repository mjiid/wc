#ifndef HELPER_H
#define HELPER_H
#include <stdio.h>

int get_bytes(FILE *fp);
int get_lines(FILE *fp);
int get_words(FILE *fp);
int get_chars(FILE *fp);
int count(FILE *fp, char* op);
void print_usage();
void print_result(int lines, int words, int bytes, char* filename);
void print_error(char* message);
FILE *tmp();

#define BUFFER_SIZE 4096

#endif
