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

int mexec(char **cmd, int pipe, int cmdnums) {
    if (cmd[0] == NULL) return 1;
    pid_t pid = fork();
    if (pid == -1) {
        printf("Failed to fork.\n");
        fflush(stdout);
        return 1;
    }
    else if (pid == 0) {
        if (pipe) {
            int pipein = dup(STDIN_FILENO);
            int pipeout = dup(STDOUT_FILENO);
            return mexec_pipe(cmd, 0, cmdnums);
            dup2(pipein, STDIN_FILENO);
            dup2(pipeout, STDOUT_FILENO);
        } else {
            return mexec_single(cmd, 0, cmdnums);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
    }
    return 1;
}

int mexec_single(char **cmd, int left, int right) {
    int end = right;
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
            char * cm[1024]; // duplicate for cmd
            for (int i = left;i<end;++i)
                cm[i] = cmd[i];
            cm[end]=NULL;
            if (execvp(cm[left], cm+left) < 0) {
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

int mexec_pipe(char **cmd, int left, int right) {
    int pipeidx = -1;
    for (int i = left; i < right; ++i) {
        if (!strcmp(cmd[i], "|")) {
            pipeidx = i;
            break;
        }
    }

    if (pipeidx == right - 1) {
        printf(stderr, "Error: Miss pipe parameters.\n");
    }

    int fds[2];     // [0] read end, [1] write end

    if (pipe(fds) == -1) {
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    pid_t pid = vfork();
    if (pid == -1) {
        printf("Failed to fork.\n");
        fflush(stdout);
        return 1;
    } else if (pid == 0) { // child process
        close(fds[0]);
        dup2(fds[1], STDIN_FILENO);
        close(fds[1]);

        return mexec_single(cmd, left, pipeidx);
    } else { // parent process
        int status;
        waitpid(pid, &status, 0);
        int exitCode = WEXITSTATUS(status);

        if (exitCode != 0) { // chile process error
            char info[4096] = {0};
            char line[2048];
            close(fds[1]);
            dup2(fds[0], STDIN_FILENO);
            close(fds[0]);
            while (fgets(line, 2048, stdin) != NULL) { // read error message from child process
                strcat(info, line);
            }
            printf("%s", info); // print error

        } else if (pipeidx + 1 < right) {
            close(fds[1]);
            dup2(fds[0], STDIN_FILENO);
            close(fds[0]);
            return mexec_single(cmd, pipeidx + 1, right);
        }
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