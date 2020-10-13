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

int mexec(char** cmd, int cmdnums, int pipe, Job* job, Job* joblist, int jobnums, pid_t mainpid, char** qcmd){
    int pipeidx[16];
    memset(pipeidx, '\0', 16);

    pipeidx[0] = -1;
    if(job->fb == Back){
        job->pidnums = cmdnums + 1;
        joblist[jobnums] = *job;
    }

    if (pipe == 0) {
        int result = mexec_single(cmd, job, joblist, jobnums, mainpid, cmdnums, qcmd);
        return 0;
    }

    int i = 0;
    int j = 1;

    while(cmd[i] != NULL) {
        if (strcmp(qcmd[i], "1") == 0) {
            i++;
            continue;
        }
        if (strcmp(cmd[i], "|") == 0) {
            pipeidx[j++] = i;
        }
        i++;
    }

    pipeidx[j] = i;
    int din = dup(STDIN_FILENO);
    int dout = dup(STDOUT_FILENO);
    mexec_pipe(cmd, pipeidx, j, 0, job, joblist, jobnums, mainpid, qcmd);
    dup2(din, STDIN_FILENO);
    dup2(dout, STDOUT_FILENO);
    return 0;
}

int mexec_single(char** cmd, Job* job, Job* joblist, int jobnums, pid_t mainpid, int cmdnums, char** qcmd) {
    if (strcmp(cmd[0], "cd") == 0) {
        builtin_cd(cmd, cmdnums);
        return 0;
    }
    int fin = dup(STDIN_FILENO);
    int fout = dup(STDOUT_FILENO);
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        if (job->fb == Front) setpgid(0, mainpid);

        redirection(cmd, qcmd);
        if (strcmp(cmd[0], "pwd") == 0) {
            builtin_pwd(cmd);
            exit(0);
        }
        if (execvp(cmd[0], cmd) < 0) {
            printf("%s: command not found\n", cmd[0]);
            fflush(stdout);
            exit(0);
        }
    } else if (pid == -1) {
        printf("Error: Child process creation was unsuccessful.");
        fflush(stdout);
        return 1;
    } else if (pid > 0) {
        if (job->fb == Back) {
            joblist[jobnums] = *job;
            job->pidnums = 1;
            job->pid[0] = pid;
        }
        if (job->fb == Front) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            int status;
            waitpid(pid, &status, WNOHANG | WUNTRACED);
        }
    }
    dup2(fin, STDIN_FILENO);
    dup2(fout, STDOUT_FILENO);
    return 0;
}

int mexec_pipe(char** cmd, int* pipeidx, int cmnum, int cnt, Job* job, Job* joblist, int jobnums, pid_t mainpid, char** qcmd) {
    if (cnt == cmnum)
        return 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int rdout = 0;
    int rdin = 0;
    char *cmdp[1024];
    char *goodcmdp[1024];
    memset(cmdp, '\0', 1024);
    memset(goodcmdp, '\0', 1024);

    for (i = pipeidx[cnt] + 1; i <= pipeidx[cnt + 1] - 1; i++) {
        goodcmdp[j] = qcmd[i];
        cmdp[j++] = cmd[i];
    }

    while (k < 1024 && cmdp[k]) {
        if (strcmp(goodcmdp[k], "1") == 0) {
            k++;
            continue;
        }
        if (strcmp(cmdp[k], ">") == 0 || strcmp(cmdp[k], ">>") == 0) {
            rdout = 1;
            break;
        }
        if (strcmp(cmdp[k], "<") == 0) {
            rdin = 1;
            break;
        }
        k++;
    }

    if (cnt == 0 && rdout == 1) {
        printf("error: duplicated output redirection\n");
        fflush(stdout);
        return 1;
    }
    if (cnt == cmnum - 1 && rdin == 1) {
        printf("error: duplicated input redirection\n");
        fflush(stdout);
        return 1;
    }

    int fd[2];

    if (cnt != cmnum - 1) {
        if (pipe(fd) == -1) {
            printf("Error: Failed to pipe.\n");
            fflush(stdout);
            return 1;
        }
    }
    pid_t pid = vfork();

    if (pid == -1) {
        printf("Error: Fail to fork\n");
        fflush(stdout);
        return 1;
    }

    if (pid == 0) {
        if (job->fb == Front) setpgid(0, mainpid);
        if (cnt != cmnum - 1) {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        }

        redirection(cmdp, goodcmdp);

        if (strcmp(cmdp[0], "pwd") == 0) {
            builtin_pwd(cmdp);
            exit(0);
        }
        if (execvp(cmdp[0], cmdp) < 0) {
            printf("%s: command not found\n", cmdp[0]);
            fflush(stdout);
            exit(0);
        }
    } else {
        if (job->fb == Back) {
            job->pid[cnt] = pid;
            joblist[jobnums] = *job;
        }

        if (cnt != cmnum - 1) {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        cnt += 1;
        mexec_pipe(cmd, pipeidx, cmnum, cnt, job, joblist, jobnums, mainpid, qcmd);

        if (job->fb == Front) {
            int status;
            waitpid(pid, &status, 0);
        } else {
            waitpid(pid, &job->state[cnt], WNOHANG);
        }
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

