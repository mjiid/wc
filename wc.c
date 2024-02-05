#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"



int main(int argc, char* argv[]) {
		
	if (argc == 1) {
		// No arguments, No text file:
		if (fgetc(stdin) != EOF) {
			// Create a temporary file:
			FILE *fp = tmp();
	
			int words = get_words(fp);
			int bytes = get_bytes(fp) + 1; // +1 for the character consumed in the condition above.
			int lines = get_lines(fp);
                        fclose(fp);
        
			print_result(lines, words, bytes, "");
			return EXIT_SUCCESS;
		}	
	
		print_usage();
		return EXIT_FAILURE;
	}
	
	if (argc == 2) {
		// 1 argument, Should be the text file or standard input.
		char *arg = argv[1];
		
		FILE *fp;
		
		// Check if a file exists with the given name or option:	
		if (arg[0] == '-') {
			fp = tmp();
	
			if (fp == NULL) {
                		print_error("Error creating temporary file");
                		return EXIT_FAILURE;
        		}

			int cnt = count(fp, arg);
			if (cnt == -1) {
				print_error("Invalid command-line argument");
				return EXIT_FAILURE;
			}

			printf("%d\n", cnt);
			return EXIT_SUCCESS;	
		} else {
			fp = fopen(arg, "r");
			if (fp == NULL) {
				print_error("File does not exist");
				return EXIT_FAILURE;	
			}
			int lines = get_lines(fp);
			int words = get_words(fp);
			int bytes = get_bytes(fp);
			fclose(fp);
        
			print_result(lines, words, bytes, arg);
			return EXIT_SUCCESS;
		}

		return EXIT_FAILURE;
	}


	if (argc == 3) {
		// 2 Arguments, Should be the filename and the option for the program:
		char* op = argv[1];
		char* filename = argv[2];

		FILE *fp = fopen(filename, "r");
		if (fp == NULL) {
			print_error("File does not exist");
			return EXIT_FAILURE;
		}

		int result = count(fp, op);
		
		if (result == -1) {
			print_error("Invalid command-line argument");
			return EXIT_FAILURE;
		}
		
		printf("%d\t%s\n", result, filename);
		return EXIT_SUCCESS;
	}


	print_usage();
	return EXIT_FAILURE;
}


