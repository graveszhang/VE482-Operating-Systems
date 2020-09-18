//
// Created by Graves Zhang on 9/14/20.
//

#include "execute.h"
#include "redirect.h"
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int mexec(char **cmd) {
    if (cmd[0] == NULL) return 1;
    int status;
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        printf("Failed to fork.\n");
        fflush(stdout);
        return 1;
    }
    if (pid != 0) {
        wait(&status);
    } else {
        redirection(cmd);
        if (execvp(cmd[0], cmd) < 0) {
            printf("Cannot execute \"%s\"!\n", cmd[0]);
            fflush(stdout);
            exit(0);
        }

    }
    return 1;
}