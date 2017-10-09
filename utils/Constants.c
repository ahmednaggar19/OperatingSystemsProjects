#include "Constants.h"

char AMPERSEND;
char NULL_CHAR;
char SPACE;
char TAB;
char NLINE;
char QUOTE;

unsigned short CMD_MAX_SIZE = 512;

void setup_constants () {
	SPACE = ' ';
	TAB = '\t';
	AMPERSEND = '&';
	NULL_CHAR = '\0';
	CMD_MAX_SIZE = 512;
	NLINE = '\n';
	QUOTE = 34;
}

