#ifndef PARSERESULT_INCLUDED
#define PARSERESULT_INCLUDED

#include <stdbool.h>

typedef struct ParseResult {
	char* cmd;
	char** arguments;
	unsigned short args_size;
	bool is_background;
	bool is_valid;
}ParseResult;
 

#endif // PARSERESULT_INCLUDED
