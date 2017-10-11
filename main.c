#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE
#include <unistd.h>

#include "environment/Environment.h"
#include "executers/BatchExecuter.h"
#include "executers/InteractiveExecuter.h"

int main(int argc, char* argv[]) {
	setup_environment();
	if (argc <= 1) {
		execute_interactive();
	} else {
		execute_batch (argv[1]);
	}
	/*char cmd[11] = "/bin/ls -l"; 
	ParseResult parse = parse_command(cmd);
	printf ("CMD : %s\n", parse.cmd);
	for (int i = 0; i < parse.args_size; i++) {
		printf ("ARG%d : %s\n", i,parse.arguments[i]); 
	}
	execv (parse.cmd, parse.arguments);*/
	return 0;
}
