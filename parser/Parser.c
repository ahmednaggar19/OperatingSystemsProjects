#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "Parser.h"
#include "ParseResult.h"
#include "CommandNormalizer.h"
#include "../utils/Constants.h"

unsigned short args_size;


void set_args_size (char cmd[]) {
	args_size = 1;
	bool in_string = false;
	unsigned short cmd_size = strlen(cmd);
	for (unsigned short i = 0; i < cmd_size; i++) {			
		if (cmd[i] == SPACE && !in_string) {
			args_size++;
		} else if (cmd[i] == QUOTE) {
			in_string = (in_string == false ? true : false);
	}
	return;
}

char** get_command_arguments (char cmd[]) {
	char** args;
	set_args_size (cmd);
	char* pch = strtok (cmd, " ");
	args = malloc( (args_size + 1) * (sizeof(char*)) );
	for (unsigned short i = 0; i < args_size; i++) {
		args[i] = malloc (strlen(pch) * 1); // 1 refering to char size    		
		args[i] = pch;
		printf ("arg : %s\n", pch);
		pch = strtok (NULL, " ");
  	}
	printf ("args count : %d\n", args_size);
	args[args_size] = NULL;
	return args;
}

bool is_background_process (char** args) {
	if (args_size == 1) {
		return  (args[args_size - 1][0] == AMPERSEND);
	}	
	return (args[args_size - 2][0] == AMPERSEND);
}

ParseResult parse_command (char cmd[]) {
	normalize_command (cmd);
	ParseResult parse_result;
	char** args = get_command_arguments (cmd);
	parse_result.arguments = args;
	parse_result.cmd = args[0];
	parse_result.args_size = args_size;
	parse_result.is_background = is_background_process(args);
	return parse_result;
}

