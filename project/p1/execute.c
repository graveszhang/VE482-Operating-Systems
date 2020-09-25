//
// Created by Graves Zhang on 9/14/20.
//

#include "execute.h"
#include "redirect.h"
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int mexec(char** cmd, int pipe, int cmdnums){
    if (cmd[0] == NULL)
        return 1;

    if (!pipe) {
        mexec_single(cmd,cmdnums);
        return 0;
    }

    int i = 0, j = 1;
    int pipeIdx[256];
    memset(pipeIdx, '\0', 256);
    pipeIdx[0] = -1;

    while(cmd[i] != NULL){
        if (strcmp(cmd[i], "|") == 0){
            pipeIdx[j++] = i;
        }
        i++;
    }
    pipeIdx[j] = i;

    int din = dup(STDIN_FILENO);
    int dout = dup(STDOUT_FILENO);

    mexec_pipe(cmd, pipeIdx, j);

    dup2(din, STDIN_FILENO);
    dup2(dout, STDOUT_FILENO);
    return 0;
}

int mexec_single(char** cmd, int cmdnums) {
    if (strcmp(cmd[0], "cd") == 0) {
        builtin_cd(cmd, cmdnums);
        return 0;
    }
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        redirection(cmd);
        if (strcmp(cmd[0], "pwd") == 0) {
            builtin_pwd(cmd);
            exit(0);
        }
        if (execvp(cmd[0], cmd) < 0) {
            printf("Error: Fail to execute %s\n", cmd[0]);
            fflush(stdout);
            exit(0);
        }
    } else if (pid == -1) {
        printf("Error: Child process creation was unsuccessful.");
        return 1;
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
//        wait(NULL);
        return 0;
    }
    return 0;
}

int mexec_pipe(char** cmd, int* pipeIdx, int cmdnums) {
    int c = 0;
    while (c < cmdnums) {
        int j = 0;
        char *cmdp[1024];
        memset(cmdp, '\0', 1024);

        for (int i = pipeIdx[c] + 1; i <= pipeIdx[c + 1] - 1; i++) {
            cmdp[j++] = cmd[i];
        }

        int fds[2];

        if (c != cmdnums - 1) {
            if (pipe(fds) == -1) {
                printf("Error: Failed to pipe.\n");
                fflush(stdout);
                return 1;
            }
        }
        pid_t pid = fork();

        if (pid == -1) {
            printf("Error: Fail to fork");
            fflush(stdout);
            return 1;
        } else if (pid == 0) {
            if (c != cmdnums - 1) {
                close(fds[0]);
                dup2(fds[1], STDOUT_FILENO);
                close(fds[1]);
            }
            redirection(cmdp);
            if (execvp(cmdp[0], cmdp) < 0) {
                printf("Error: Fail to execute %s\n", cmdp[0]);
                fflush(stdout);
                exit(0);
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
            close(fds[1]);
            dup2(fds[0], STDIN_FILENO);
            close(fds[0]);
        }
        c++;
    }
    return 0;
}

void builtin_pwd(char **cmd){
//    printf("Congrats! You are using built-in pwd!\n");
    char dir[1024];
    if (getcwd(dir, sizeof(dir)) == NULL) {
        printf("Error in getting current directory.\n");
        fflush(stdout);
    }
    printf("%s\n", dir);
    fflush(stdout);
}

void builtin_cd(char **cmd, int cmdnums) {
//    printf("Congrats! You are using built-in cd!\n");
    if (cmdnums < 2) {
        char *home = getenv("HOME");
        chdir(home);
    } else if (cmdnums > 2) {
        fprintf(stderr, "Too many arguments for cd.\n");
    } else {
        if (chdir(cmd[1]) < 0) {
            fprintf(stderr, "Cannot change to directory \"%s\".\n", cmd[1]);
            fflush(stdout);
        }
    }
}

