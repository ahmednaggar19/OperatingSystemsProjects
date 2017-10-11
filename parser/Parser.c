#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "Parser.h"
#include "ParseResult.h"
#include "CommandNormalizer.h"
#include "../utils/Constants.h"
#include "../environment/Variables.h"

unsigned short args_size;
bool is_valid;

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
	}
	if (cmd[cmd_size - 1] == SPACE) {
		args_size--;
	}
	return;
}

char*  append(char*str, char c) {
     if(strlen(str)  <= 0) {
	str = malloc (2);
	str[0] = c;
	str[1] = NULL_CHAR;
     } else {
     	int str_len = strlen (str);
	//str = realloc (str, str_len + 1);
	str[str_len] = c;
	str[str_len + 1] = NULL_CHAR;
     }
     return str;
}

char** get_command_arguments (char cmd[]) {
	char** args;
	set_args_size (cmd);
	args = malloc( (args_size + 1) * (sizeof(char*)) );
	unsigned short arg_index = 0;
	bool in_string = false;
	char* arg_buffer = "";
	for (unsigned short i = 0; i < strlen(cmd); i++) {
		if (cmd[i] == SPACE && !in_string) {
			args[arg_index++] = strdup(arg_buffer);
			arg_buffer = "\0";
		} else if (cmd[i] == SPACE) {
			arg_buffer = append(arg_buffer, cmd[i]);
		} else if (cmd[i] == QUOTE && !in_string) {
			arg_buffer = append(arg_buffer, cmd[i]);
			in_string = true;
		} else if (cmd[i] == QUOTE) {
			arg_buffer = append(arg_buffer, cmd[i]);
			in_string = false;
		} else {
			arg_buffer = append (arg_buffer, cmd[i]);
		}
	}
  	if (strlen(arg_buffer) > 0) {
  		args[arg_index++] = strdup (arg_buffer);
  	}
	args[arg_index] = NULL;
	return args;
}

bool is_background_process (char** args) {
	if (args_size == 1) {
		return  (args[args_size - 1][0] == AMPERSEND);
	}	
	return (args[args_size - 2][0] == AMPERSEND);
}

bool is_valid_var_char (char c) {
	return isalnum(c) != 0;
}

char* substitute_variables (char cmd[]) {
	size_t cmd_length = strlen(cmd);
	char* extracted_cmd = malloc (CMD_MAX_SIZE);
	unsigned short cmd_index = 0; 
	char* var_accumulator = malloc(CMD_MAX_SIZE);
	unsigned short var_index = 0;
	bool building_var = false;
	extracted_cmd[0] = NULL_CHAR;
	var_accumulator[0] = NULL_CHAR;
	for (unsigned short i = 0; i < cmd_length; i++) {
		if (cmd[i] == VAR_INDICATOR) {
			building_var = true;
		} else if (building_var) {
			if (is_valid_var_char(cmd[i])) {
				var_accumulator[var_index++] = cmd[i];
				var_accumulator[var_index] = NULL_CHAR; 
			} else {
				char* var_value = lookup_variable(var_accumulator);
				if (!strcmp(var_value, "NOT FOUND")) {
					is_valid = false;
				}
				extracted_cmd[cmd_index++] = cmd[i];
			 	extracted_cmd[cmd_index] = NULL_CHAR;
				extracted_cmd = strcat(extracted_cmd, var_value);
				var_accumulator[0] = NULL_CHAR;
				building_var = false;
			}
		} else {
			 extracted_cmd[cmd_index++] = cmd[i];
			 extracted_cmd[cmd_index] = NULL_CHAR;
		}
	}
	if (strlen(var_accumulator) > 0) {
  		extracted_cmd = strcat(extracted_cmd, lookup_variable(var_accumulator));
  	}
	free(var_accumulator);
  	return extracted_cmd;
}


ParseResult parse_command (char cmd[]) {
	is_valid = true;
	normalize_command (cmd);	
	char* extracted_cmd = substitute_variables(cmd);
	ParseResult parse_result;
	parse_result.is_valid = is_valid;
	if (!is_valid) {
		return parse_result;
	}
	char** args = get_command_arguments (extracted_cmd);
	parse_result.arguments = args;
	parse_result.cmd = args[0];
	parse_result.args_size = args_size;
	parse_result.is_background = is_background_process(args);
	
	return parse_result;
}

