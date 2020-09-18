//
// Created by Graves Zhang on 9/14/20.
//
#include <string.h>
#include <stdlib.h>
#include "parse.h"
char ** mparse(char *line){
    const char delim[] = " \t\r\n\a";
    int buffersize = 64;
    char **cmd = malloc(buffersize * sizeof(char*));
    char **cmd_backup;
    char *arg = strtok(line,delim);
    int i = 0;
    while (arg!=NULL){
        cmd[i] = arg;
        i += 1;
        if (i >= buffersize) {
            buffersize += 64;
            cmd_backup = cmd;
            cmd = realloc(cmd, buffersize * sizeof(char*));
            if (!cmd) {
                free(cmd_backup);
                exit(1);
            }
        }
        arg = strtok(NULL,delim);
    }
    cmd[i] = NULL;
    return cmd;
}