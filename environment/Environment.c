#include "Environment.h"
#include "Variables.h"
#include "../executers/RegisteredCommands.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void setup_environment () {
	char* PATH = "PATH";
	char* HOME = "HOME";	
	char* path_value = getenv(PATH);
	char* home_value = getenv(HOME);
	char* CWD = "CWD";
	char cwd_value[1024];
	if (getcwd(cwd_value, sizeof(cwd_value)) != NULL) {
		set_variable (CWD, cwd_value);	
	}
	set_variable (PATH, path_value);
	set_variable (HOME, home_value);
	/// loading registered commands
	setup_registered_commands();
}
