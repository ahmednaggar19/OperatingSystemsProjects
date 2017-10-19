#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Variables.h"


unsigned int  variables_count = 0;
char* variables[MAX_VARIABLES_COUNT][2];
char* NOT_FOUND = "NOT_FOUND";

const char* lookup_variable( const char* key ) {
	for (unsigned int i = 0; i < variables_count; i++) {
		if (!strcmp(key, variables[i][0])) {
			return variables[i][1];
		}
	}
	return NOT_FOUND;
}

void set_variable( const char* key , const char* value ) {
	if (strcmp(lookup_variable(key), NOT_FOUND)) {
		for (unsigned int i = 0; i < variables_count; i++) {
			if (!strcmp(key, variables[i][0])) {
				variables[i][1] = value;
				return;
			}
		}
	} else {
		if (variables_count >= MAX_VARIABLES_COUNT) {

		} else {
			variables[variables_count][0] = key;
			variables[variables_count][1] = value;
			variables_count++;
		}
	}
}

