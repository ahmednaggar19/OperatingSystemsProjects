#include "CommandExecuter.h"
#include "RegisteredCommands.h"
#include "../environment/Variables.h"
#include "../parser/ParseResult.h"
#include "../utils/Constants.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>

char* USR_HOME = "~";
char* UP_DIR = "..";

void execute_cd (ParseResult parsed_cmd) {
	if (parsed_cmd.arguments[1] != NULL) {
		if (!strcmp (parsed_cmd.arguments[1], USR_HOME)) {
			if (chdir (lookup_variable ("HOME")) == -1) {
				/// TODO : Error Handling
			}
		} else if (!strcmp (parsed_cmd.arguments[1], UP_DIR)){
			if (chdir (UP_DIR) == -1) {
				/// TODO : Error Handling
			}
		} else if (chdir(parsed_cmd.arguments[1]) == -1) {
			/// TODO : Error Handling
		} else {
		
		}
	}
}

void execute_history (ParseResult parsed_cmd) {
	FILE* file_pointer;
	file_pointer = fopen(HISTORY_FILE_NAME, "r");
	if (file_pointer != NULL) {
		char cmd[CMD_MAX_SIZE];
		while (fgets(cmd, sizeof cmd, file_pointer) != NULL) {
			printf ("%s", cmd);
		}
		fclose(file_pointer);
	} else {
		///TODO : Error Handler
	}
}

void extract_var_value (char* expression) {
	char* var_name = malloc (CMD_MAX_SIZE);
	unsigned short var_index = 0;
	unsigned short i;
	bool in_string = false;
	for (i = 0; i < strlen(expression); i++) {
		if (expression[i] == EQUAL) {
			break;
		} else if (expression[i] == SPACE && !in_string) {
			///TODO : Error Handling
			return;
		} else if (expression[i] == QUOTE && !in_string) {
			in_string = true;
			continue;
		} else if (expression[i] == QUOTE && in_string) {
			if (expression[i - 1] != BACK_SLASH) {
				in_string = false;
			}
		} else if (expression[i] == BACK_SLASH) {
			continue;
		}
		var_name[var_index++] = expression[i];
		var_name[var_index] = NULL_CHAR; 
	}
	char* var_value = malloc (CMD_MAX_SIZE);
	var_index = 0;
	for (++i; i < strlen(expression); i++) {
		if (expression[i] == SPACE && !in_string) {
			///TODO : Error Handling
			return;
		} else if (expression[i] == QUOTE && !in_string) {
			in_string = true;
			continue;
		} else if (expression[i] == QUOTE && in_string) {
			in_string = false;
			continue;
		} else if (expression[i] == BACK_SLASH) {
			continue;
		}
		var_value[var_index++] = expression[i];
		var_value[var_index] = NULL_CHAR;	
	}
	set_variable (var_name, var_value);
}

void execute_expression (ParseResult parsed_cmd) {
	if (!strcmp (parsed_cmd.cmd, EXPORT)) {
		extract_var_value (parsed_cmd.arguments[1]);
	} else {
		extract_var_value (parsed_cmd.cmd);
	}
}

void execute_echo (ParseResult parsed_cmd) {
	for (unsigned short i = 1; i < parsed_cmd.args_size; i++) {
		if (parsed_cmd.arguments[i][0] == QUOTE) {
			for (unsigned short j = 1; j < strlen(parsed_cmd.arguments[i]) - 1; j++) {
				printf ("%c", parsed_cmd.arguments[i][j]);
			}
			printf (" ");
		} else {
			printf ("%s", parsed_cmd.arguments[i]);
		}
	}
}

char* get_cmd_filepath (char* cmd) {
	char* delim = ":";
	char* PATH = "PATH";
	char* PATH_VALUE = lookup_variable(PATH);
	char* path = strtok (PATH_VALUE, delim);
	size_t cmd_len = strlen (cmd);
	while (path != NULL) {
		char* test_path;
		test_path = strcpy (test_path, path);
		test_path = strncat (test_path, "/", 1);
		test_path = strncat (test_path, cmd, cmd_len);
		if (access (test_path, X_OK) == 0) {
			return test_path;
		}
		path = strtok (NULL, delim);
	}
	return NULL;
}

void execute_general (ParseResult parsed_cmd) {
	pid_t pid;
	siginfo_t childstat;
	pid = fork();
	if (!pid) {
		char* code_filepath = get_cmd_filepath(parsed_cmd.cmd);
		if (code_filepath != NULL) {
			execv(code_filepath, parsed_cmd.arguments);
		} else {
			printf ("INVALID COMMAND\n");	
		}		
		///TODO : insert Error Handling
		kill (getpid(), SIGQUIT);
		return;
	}
	if (!parsed_cmd.is_background) {
		waitid (P_PID, pid, &childstat, WEXITED);
	}
	return;
}

bool is_expression (ParseResult parsed_cmd) {
	if (!strcmp (parsed_cmd.cmd, EXPORT)) {
		return (strchr (parsed_cmd.arguments[1], EQUAL) != NULL);
	} else {
		for (unsigned short i = 0; i < strlen(parsed_cmd.cmd); i++) {
			if (parsed_cmd.cmd[i] == EQUAL) {
				return true;
			}
		}
	}
	return false;
}

void execute_command (ParseResult parsed_cmd) {
	if (!strcmp (CD, parsed_cmd.cmd)) {
		execute_cd (parsed_cmd);
	} else if (!strcmp (HISTORY, parsed_cmd.cmd)) { 
		execute_history (parsed_cmd);
	} else if (!strcmp (ECHO, parsed_cmd.cmd)) {
		execute_echo (parsed_cmd);
	} else if (is_expression(parsed_cmd)){
		execute_expression(parsed_cmd);
	} else {
		execute_general (parsed_cmd);
	}
	return;
}

void save_command (char* cmd) {
	FILE* file_pointer;
	file_pointer = fopen(HISTORY_FILE_NAME, "a");
	if (file_pointer != NULL) {
		fprintf (file_pointer,"%s", cmd);
		fclose(file_pointer);
	} else {
		///TODO : Error Handler
	}
}
