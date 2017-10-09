#ifndef FILEREADER_INCLUDED
#define FILEREADER_INCLUDED

#include <stdio.h>

typedef struct FileReadResult {
	char* file_lines;
	unsigned int lines_count;
}FileReadResult;
 
FileReadResult read_file (char* file_name);

#endif // FILEREADER_INCLUDED
