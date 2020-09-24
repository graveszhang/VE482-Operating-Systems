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

int mexec(char **cmd, int pipe) {
    if (cmd[0] == NULL) return 1;

    if(pipe) {
        int pipein = dup(STDIN_FILENO);
        int pipeout = dup(STDOUT_FILENO);
        mexec_pipe(cmd);
        dup2(pipein, STDIN_FILENO);
        dup2(pipeout, STDOUT_FILENO);
    }
    else
        mexec_single(cmd);
    return 1;
}

int mexec_single(char **cmd) {
    int status;
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        printf("Failed to fork.\n");
        fflush(stdout);
        return 1;
    } else if (pid == 0) { // child process
        redirection(cmd);
        if (strcmp(cmd[0], "pwd") == 0) { // built-in pwd execute in child
            builtin_pwd(cmd);
            free(cmd);
            exit(0);
        } else {
            if (execvp(cmd[0], cmd) < 0) {
                printf("Cannot execute \"%s\"!\n", cmd[0]);
                fflush(stdout);
                exit(0);
            }
        }
    } else {
        waitpid(pid,&status,0);
    }
    return 1;
}

int mexec_pipe(char **cmd) {


    int pipefd[2];     // [0] read end, [1] write end

    if (pipe(pipefd) == -1) {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }
    int pid;

    pid = fork();
    if (pid == -1)
        perror("fork");
    if (pid == 0) {
        close(STDOUT_FILENO);
        dup(pipefd[1]);
        mexec_single(cmd);// this should be left
    } else {
        close(STDIN_FILENO);
        dup(pipefd[0]);
        close(pipefd[1]);
        mexec_single(cmd); // this should be right
    }


    return 1;
}

void builtin_pwd(char **cmd){
    char dir[1024];
    if (getcwd(dir, sizeof(dir)) == NULL) {
        printf("Error in getting current directory.\n");
        fflush(stdout);
    }
    printf("%s\n", dir);
    fflush(stdout);
}

void builtin_cd(char **cmd, int cmdnums) {
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