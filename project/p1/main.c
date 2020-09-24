#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "read.h"
#include "parse.h"
#include "execute.h"

int cmdnums = 0; // Global variable, denotes the number of commands

int main() {
    int valid = 1;
    char *line;
    char **cmd;
    int flag = 0;
    int pipe = 0; // without pipe
    while (valid) {
        cmdnums = 0;
        line = mread();
        if (strstr(line, "|")) // execute_pipe
            pipe = 1;
        else
            pipe = 0;

        if (strcmp(line, "exit") == 0) {
            flag = 1;
            printf("exit\n");
            exit(0);
        }
        cmd = mparse(line);
//        printf("Command number is: %d\n",cmdnums);
//        Sometimes above DEBUG sentence will pause for 2-3 seconds for IDK reasons (maybe entangles with ofstream)
        if (cmdnums) {
            if (strcmp(cmd[0], "cd") == 0) {
                builtin_cd(cmd, cmdnums);
            } else {
                valid = mexec(cmd, pipe, cmdnums);
            }
            free(line);
            free(cmd);
        } else { // input nothing
            free(line);
            free(cmd);
            continue;
        }
    }

    if (flag)
        free(line);
    return 0;
}
