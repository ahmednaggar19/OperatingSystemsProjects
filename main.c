#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#include "parser/Parser.h"
#include "parser/ParseResult.h"
#include "utils/Constants.h"
*/
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
	return 0;
}
