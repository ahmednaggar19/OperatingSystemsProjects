#include <stdio.h>

#include "InteractiveExecuter.h"
#include "CommandExecuter.h"
#include "../utils/Constants.h"
#include "../parser/Parser.h"
#include "RegisteredCommands.h"

char prompt[] = "\nShell >> ";

void execute_interactive () {
	while (true) {
		printf("%s", prompt);
		char cmd[CMD_MAX_SIZE];
		fgets(cmd, CMD_MAX_SIZE, stdin);
		save_command(cmd);
		ParseResult parse_result = parse_command(cmd);
		if (!strcmp(parse_result.cmd, EXIT)) {
			return;
		} else if (!parse_result.is_valid) {
			printf  ("ERROR");
		}
		execute_command(parse_result);
	}
}

