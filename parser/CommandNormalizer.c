#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "CommandNormalizer.h"
#include "../utils/Constants.h"


bool is_space (char c) {
    return (c == SPACE);
}

bool is_tab (char c) {
    return c == TAB;
}

void normalize_tabs(char cmd[]) {
    unsigned short str_len = strlen(cmd);
    for (unsigned short i = 0; i < str_len; i++) {
        if (is_tab(cmd[i])) {
            cmd[i] = SPACE;
        }
    }
}

void normalize_spaces (char cmd[]) {
    unsigned short str_len = strlen(cmd);
    bool in_string = false;
    unsigned short j = 0, start_index;
    for (unsigned short i = 0; i < str_len; i++) {
        if ((is_space(cmd[i]) && !in_string)) {
	    j = i;
            while (is_space(cmd[j]) && j <= str_len) {
                j++;
            }
	    start_index = i;
            while (j <= str_len) {
                cmd[++i] = cmd[j++];
            }
            i = start_index;
        } else if (cmd[i] == QUOTE) {
        	in_string = (in_string == false ? true : false);
        }
    }
    return;
}

void normalize_end(char cmd[]) {
    unsigned short str_len = strlen(cmd);
    str_len = strlen(cmd);
    if (is_space(cmd[str_len - 1])) {
        cmd[str_len - 1] = NULL_CHAR;
    }
    str_len = strlen(cmd);
    if ((cmd[str_len - 1]) == AMPERSEND) {
        if (!is_space(cmd[str_len - 2])) {
            cmd[str_len + 1] = NULL_CHAR;
            cmd[str_len] = AMPERSEND;
            cmd[str_len - 1] = SPACE;
        }
    }
    return;
}

void normalize_command(char cmd[]) {
	size_t str_len = strlen(cmd);
	cmd[str_len - 1] = NULL_CHAR;
	normalize_tabs(cmd);
	normalize_spaces(cmd);
	normalize_end(cmd);
	return;
}
