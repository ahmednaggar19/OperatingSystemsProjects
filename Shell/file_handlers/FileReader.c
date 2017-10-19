#include "FileReader.h"
#include "../utils/Constants.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


unsigned int MAX_LINES = 100;

FileReadResult read_file (char* file_name) {
	FileReadResult read_result;
	/*FILE* file_pointer;
	file_pointer = fopen(file_name, "r");
	char* file_lines[MAX_LINES];
	unsigned int line_index = 0;
	if (file_pointer != NULL) {
		char cmd[CMD_MAX_SIZE];
		while (fgets(cmd, sizeof cmd, file_pointer) != NULL) {
			file_lines[line_index] = malloc (sizeof (cmd));
			file_lines[line_index] = strdup(cmd);
			line_index++;
			if (line_index >= MAX_LINES) {
				break;
			}
		}
		fclose(file_pointer);
		read_result.file_lines = file_lines;
		read_result.lines_count = line_index;
		
		return read_result; 
	} else {
		///TODO : Error Handler
	}
	read_result.lines_count = 0;*/
	return read_result;
}
