#include "BatchExecuter.h"
#include "CommandExecuter.h"
#include "RegisteredCommands.h"
#include "../parser/Parser.h"
#include "../utils/Constants.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void execute_batch (char* batch_name) {
	FILE* file_pointer;
	file_pointer = fopen(batch_name, "r");
	if (file_pointer != NULL) {
		char cmd[CMD_MAX_SIZE];
		while (fgets(cmd, sizeof cmd, file_pointer) != NULL) {
			save_command(cmd);
			ParseResult parse_result = parse_command(cmd);
			if (!strcmp(parse_result.cmd, EXIT)) {
				return;
			}
			execute_command(parse_result);
		}
		fclose(file_pointer);
	} else {
		///TODO : Error Handler
	}
	return;
}
