#include "Constants.h"

char AMPERSEND;
char NULL_CHAR;
char SPACE;
char TAB;
char NLINE;
char QUOTE;
char EQUAL;
char BACK_SLASH;
char VAR_INDICATOR;
char* HISTORY_FILE_NAME;
char* LOGS_FILE_NAME;

unsigned short CMD_MAX_SIZE = 512;

void setup_constants () {
	SPACE = ' ';
	TAB = '\t';
	AMPERSEND = '&';
	NULL_CHAR = '\0';
	CMD_MAX_SIZE = 512;
	NLINE = '\n';
	QUOTE = 34;
	EQUAL = '=';
	BACK_SLASH = 92;
	VAR_INDICATOR = '$';
	HISTORY_FILE_NAME = "files/history.txt";
	LOGS_FILE_NAME = "files/logs.txt";
}

