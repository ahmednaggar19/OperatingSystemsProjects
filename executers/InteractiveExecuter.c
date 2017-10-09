#include <stdio.h>

#include "InteractiveExecuter.h"
#include "CommandExecuter.h"
#include "../utils/Constants.h"
#include "../parser/Parser.h"
#include "RegisteredCommands.h"

char prompt[] = "\nShell >> ";

void execute_interactive () {
	printf ("Please Type (exit) to exit the Shell\n");
	while (true) {
		printf("%s", prompt);
		char cmd[CMD_MAX_SIZE];
		fgets(cmd, CMD_MAX_SIZE, stdin);
		ParseResult parse_result = parse_command(cmd);
		if (!strcmp(parse_result.cmd, EXIT)) {
			return;
		}
		execute_command(parse_result);
	}
}

