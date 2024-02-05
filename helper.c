#include "helper.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 4096

int get_bytes(FILE *fp) {
	int bytes = 0;
	fseek(fp, 0, SEEK_END);
	bytes = ftell(fp);
	fseek(fp, 0, SEEK_SET);
        return bytes;
}


int get_lines(FILE *fp) {
	int lines = -1;
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) lines++;
	fseek(fp, 0, SEEK_SET);
	return lines;
}


int get_words(FILE *fp) {
	int words = 0;
        int inWord = 0;
        char c;
        while ((c = fgetc(fp)) != EOF) {
        	if (isspace(c)) {
        	// If whitespace is encountered, set the flag to indicate not in a word
        		inWord = 0;
         	} else {
         		// If a non-whitespace character is encountered, check the flag
         		// If not in a word (flag is 0), increment the word count and set the flag
         		if (!inWord) {
         			words++;
                		inWord = 1;
         		}
        	}
	}
	fseek(fp, 0, SEEK_SET);
        return words;
}


int get_chars(FILE *fp) {
	int characters = 0;
    	char c;
    	while ((c = fgetc(fp)) != EOF) {
        	characters++;
    	}
    	
	fseek(fp, 0, SEEK_SET);
    	return characters;
}


int count(FILE *fp, char* op) {
	
	int result = -1;

	// Support the command line option -c: Outputs the number of bytes.
        if (strcmp(op, "-c") == 0) {
        	int bytes = get_bytes(fp);
		result = bytes;
        } else if (strcmp(op, "-l") == 0) {
           	// Support the command line option -l: Outputs the number of lines.
	   	int lines = get_lines(fp);
                result = lines;
        } else if (strcmp(op, "-w") == 0) {
        	// Support the command line option -w: Outputs the number of words:      
		int words = get_words(fp);
                result = words;
        } else if (strcmp(op, "-m") == 0) {
       		// Support the command line option -m: Outputs the number of characters:
		// The answer to this depends on the locale of the computer:
        	int count = (MB_CUR_MAX > 1) ? get_chars(fp) : get_bytes(fp);
        	result = count;
	}
	

	fseek(fp, 0, SEEK_SET);
	fclose(fp);
	return result;
}


void print_usage() {
	printf("Usage: program_name [OPTION] [FILE]\n");
}


FILE *tmp() {
	// Create a temporary file:
        FILE *fp = tmpfile();
        if (fp == NULL) {
      		perror("Error creating temporary file");
                return NULL;
       	}

        char buffer[BUFFER_SIZE];
       	size_t bytesRead;

        // Read from stdin and write to the temporary file in blocks
        while ((bytesRead = fread(buffer, 1, sizeof(buffer), stdin)) > 0) {
        	fwrite(buffer, 1, bytesRead, fp);
        }

        fseek(fp, 0, SEEK_SET);
	return fp;
}


void print_result(int lines, int words, int bytes, char* filename) {
    printf("%d\t%d\t%d\t%s\n", lines, words, bytes, filename);
}


void print_error(char* message) {
    fprintf(stderr, "%s\n", message);
}
