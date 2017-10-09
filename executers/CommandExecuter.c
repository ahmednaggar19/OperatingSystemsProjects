#include "CommandExecuter.h"
#include "RegisteredCommands.h"
#include "../environment/Variables.h"
#include "../parser/ParseResult.h"

#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <wait.h>
#include <unistd.h>

void execute_cd (ParseResult parsed_cmd) {
	if (parsed_cmd.arguments[1] != NULL) {
		if (chdir (parsed_cmd.arguments[1]) == -1) {
			///TODO: Error Handling
		} else {
			///TODO: LOG
		}
	}
}

void execute_history (ParseResult parsed_cmd) {
	
}

void execute_log (ParseResult parsed_cmd) {
	
}

void execute_expression (ParseResult parsed_cmd) {
	
}

void execute_echo (ParseResult parsed_cmd) {
	for (unsigned short i = 1; i < parsed_cmd.args_size; i++) {
		
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
			printf ("NOT REC\n");	
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

void execute_command (ParseResult parsed_cmd) {
	if (!strcmp (CD, parsed_cmd.cmd)) {
		execute_cd (parsed_cmd);
	} else if (!strcmp (HISTORY, parsed_cmd.cmd)) { 
		execute_history (parsed_cmd);
	} else if (!strcmp (LOG, parsed_cmd.cmd)) {
		execute_log (parsed_cmd);
	} else if (!strcmp (ECHO, parsed_cmd.cmd)) {
		execute_echo (parsed_cmd);
	} else {
		execute_general (parsed_cmd);
	}
	return;
}
