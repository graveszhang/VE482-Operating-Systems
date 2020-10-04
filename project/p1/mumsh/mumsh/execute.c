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

int mexec(char** cmd, int pipe, int cmdnums, Job* joblist, Job* job, int jobnums) {
    if (cmd[0] == NULL)
        return 1;

    if (job->fb == Back){
        joblist[jobnums] = *job;
        job->pidnums = cmdnums + 1;
    }


    if (!pipe) {
        mexec_single(cmd, cmdnums, joblist, job, jobnums);
        return 0;
    }

    int i = 0, j = 1;
    int pipeIdx[512];
    memset(pipeIdx, '\0', 512);
    pipeIdx[0] = -1;

    while (cmd[i] != NULL) {
        if (strcmp(cmd[i], "|") == 0) {
            pipeIdx[j++] = i;
        }
        i++;
    }
    pipeIdx[j] = i;

    int din = dup(STDIN_FILENO);
    int dout = dup(STDOUT_FILENO);

    mexec_pipe(cmd, pipeIdx, j, 0, joblist, job, jobnums);

    dup2(din, STDIN_FILENO);
    dup2(dout, STDOUT_FILENO);
    return 0;
}

int mexec_single(char** cmd, int cmdnums, Job* joblist, Job* job, int jobnums) {
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
//            printf("Error: Fail to execute %s\n", cmd[0]);
            fprintf(stderr, "%s: command not found\n", cmd[0]);
            fflush(stdout);
            exit(0);
        }
    } else if (pid == -1) {
        printf("Error: Child process creation was unsuccessful.");
        return 1;
    } else if (pid > 0) {
        if (job->fb == Front) {
            int status;
            waitpid(pid, &status, 0);
        } else if (job->fb == Back) {
            job->pid[0] = pid;
            job->pidnums = 1;
            joblist[jobnums] = *job;
        } else {
            int status;
            waitpid(pid, &status, WNOHANG|WUNTRACED);
        }

        return 0;
    }
    return 0;
}

int mexec_pipe(char** cmd, int* pipeIdx, int cmdnums, int cnt, Job* joblist, Job* job, int jobnums) {
    if (cnt == cmdnums) return 0;

    int j = 0;
    char *cmdp[1024];
    memset(cmdp, '\0', 1024);

    for (int i = pipeIdx[cnt] + 1; i <= pipeIdx[cnt + 1] - 1; i++) {
        cmdp[j++] = cmd[i];
    }

    int fds[2];

    if (cnt != cmdnums - 1) {
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
        if (cnt != cmdnums - 1) {
            close(fds[0]);
            dup2(fds[1], STDOUT_FILENO);
            close(fds[1]);
        }
        redirection(cmdp);
        if (execvp(cmdp[0], cmdp) < 0) {
//            printf("Error: Fail to execute %s\n", cmdp[0]);
            fprintf(stderr, "%s: command not found\n", cmdp[0]);
            fflush(stdout);
            exit(0);
        }
    } else {
        if (job->fb == Back) {
            job->pid[cnt] = pid;
            job->pidnums = 1;
            joblist[jobnums] = *job;
        }

        if (cnt != cmdnums - 1) {
            close(fds[1]);
            dup2(fds[0], STDIN_FILENO);
            close(fds[0]);
        }
        cnt += 1;
        mexec_pipe(cmd, pipeIdx, cmdnums, cnt, joblist, job, jobnums);
        if (job->fb == Front) {
            int status;
            waitpid(pid, &status, 0);
        } else
            waitpid(pid, &job->state[cnt], 0);
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
            fflush(stdout);
            fprintf(stderr, "%s: No such file or directory\n", cmd[1]);
            fflush(stdout);
        }
    }
}

