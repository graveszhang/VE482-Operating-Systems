#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include "read.h"
#include "parse.h"
#include "execute.h"

int cmdnums = 0; // Global variable, denotes the number of commands
jmp_buf environment;

enum {
    NONE_EXIST_PROGRAM,
    F_NOT_EXIST_IN,
    F_PERMISSION_DENIED_OUT,
    DUP_REDIRECTION_IN,
    DUP_REDIRECTION_OUT,
    SYNTAX_ERROR_IN,
    SYNTAX_ERROR_OUT,
    SYNTAX_ERROR_PIPE,
    MISSING_PROGRAM,
    NONE_EXIST_CD
};

void sigint_handler(int sig){ // handle ctrl-c
    #ifdef DEBUG
    printf("CTRL-C is disabled.\n");
    #endif
    printf("\n");
    siglongjmp(environment, 2);
}

int main() {

    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);

    int result = -1;
    char *line;
    char **cmd;
    int pipe = 0; // without pipe
    signal(SIGINT, sigint_handler);
//    signal(SIGINT,SIG_DFL); // DFL directly exit the program

    if (sigsetjmp(environment, 1) == 2) {
        if (cmdnums) free(cmd);
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
    }

    while (1) {
        cmdnums = 0;
        line = mread();
        if (strstr(line, "|")) // execute_pipe
            pipe = 1;
        else
            pipe = 0;

        if (strcmp(line, "exit") == 0 && line[4] == '\0') {
            printf("exit\n");
            exit(0);
        }

        cmd = mparse(line);
//        printf("Command number is: %d\n",cmdnums);
        if (cmdnums) {
            if (strcmp(cmd[0], "cd") == 0) {
                builtin_cd(cmd, cmdnums);
            } else {
                result = mexec(cmd, pipe, cmdnums);
                switch (result) { // ERROR HANDLING 4,5,6,7
                    case DUP_REDIRECTION_IN:
                        fprintf(stderr, "error: duplicated input redirection\n");
                        break;
                    case DUP_REDIRECTION_OUT:
                        fprintf(stderr, "error: duplicated output redirection\n");
                        break;
                    case SYNTAX_ERROR_IN:
                        fprintf(stderr, "syntax error near unexpected token `<'\n");
                        break;
                    case SYNTAX_ERROR_OUT:
                        fprintf(stderr, "syntax error near unexpected token `>'\n");
                        break;
                    case SYNTAX_ERROR_PIPE:
                        fprintf(stderr, "syntax error near unexpected token `|'\n");
                        break;
                    case MISSING_PROGRAM:
                        fprintf(stderr, "error: missing program\n");
                        break;
                }
            }
            free(line);
            free(cmd);

        } else { // input nothing
            free(line);
            free(cmd);
        }
    }
    return 0;
}
