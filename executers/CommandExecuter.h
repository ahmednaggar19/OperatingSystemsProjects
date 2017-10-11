#ifndef COMMANDEXECUTER_INCLUDED
#define COMMANDEXECUTER_INCLUDED

#include "../parser/ParseResult.h"

void execute_command(ParseResult parsed_cmd);

void save_command (char* cmd);
#endif // COMMANDEXECUTER_INCLUDED
