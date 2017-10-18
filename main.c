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
	if (argc == 1) {
		execute_interactive();
	} else if (argc == 2) {
		execute_batch (argv[1]);
	} else {
		printf ("Too many arguments ! \n");
	}
	/*char* c = "/bin/ls";
	char* parm[] = {"/bin/ls", "-l", NULL, NULL};
	execv (c, parm);*/
	return 0;
}
