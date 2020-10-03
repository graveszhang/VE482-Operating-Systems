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
int jobnums = 0; // Global variable, denotes the number of jobs

jmp_buf environment;

enum {
    F_NOT_EXIST_IN,
    F_PERMISSION_DENIED_OUT,
    DUP_REDIRECTION_IN,
    DUP_REDIRECTION_OUT,
    SYNTAX_ERROR_IN,
    SYNTAX_ERROR_OUT,
    SYNTAX_ERROR_PIPE,
    MISSING_PROGRAM
};

void sigint_handler(int sig){ // handle ctrl-c
    #ifdef DEBUG
    printf("CTRL-C is disabled.\n");
    #endif
    printf("\n");
    siglongjmp(environment, 2);
}

void initJob(Job *job){
    int i = 0;
    for (i = 0; i < PIPENUMS; ++i) {
        job->pid[i] = 0;
        job->state[i] = 0;
    }
    job->content[i] = '\0';
    job->fb = Back; // back for default
    job->id = 1;
    job->pidnums = 0;
}

Bool JobIsRunning(Job job){
    Bool Running = False;
    for (int i = 0; i < job.pidnums; ++i){
        int status;
        if (!waitpid(job.pid[i],&status,WNOHANG)){
            Running = True;
            break;
        } else{
            job.state[i] = 1; // Still running
        }
    }
    return Running;
}

void printJob(Job *joblist){
    if (!jobnums)
        return;
    for (int i = 0; i < jobnums; ++i) {
        printf("[%d] ",joblist[i].id);
        fflush(stdout);
        if (JobIsRunning(joblist[i])){
            printf("running ");
            fflush(stdout);
        } else {
            printf("done ");
            fflush(stdout);
        }
        printf("%s\n", joblist[i].content);
        fflush(stdout);
    }
}

int main() {
    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);

    Job joblist[128];
    for (int j = 0; j < 128; ++j)
        initJob(&joblist[j]);

    int result = -1;
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
        char line[1024];
        cmdnums = 0;
        int flag = mread(line);
        if (flag == -1)
            return 0;

        /********** Job Initialization **********/

        Job job;
        initJob(&job); // set for default values
        job.id = jobnums + 1;

        for (int k = 0; k < 1024; ++k)
            job.content[k] = line[k]; // include the last &

        if (strlen(line)) {
            char last = line[strlen(line) - 1];
            if (last == '&') {
                job.fb = Back;
                line[strlen(line) - 1] = '\n';
                line[strlen(line)] = '\0';
                printf("[%d] ", job.id);
                fflush(stdout);
                printf("%s \n", job.content);
                fflush(stdout);
            } else
                job.fb = Front;
        }
//        printf("Debug: Job FB is %d\n",job.FB);
//        printf("Debug: Job id is %d\n",job.id);

        /********** Job Initialization **********/

        if (strstr(line, "|")) // execute_pipe
            pipe = 1;
        else
            pipe = 0;

        if (strcmp(line, "\0") == 0) {
            continue;
        }

        if (strcmp(line, "exit") == 0 && line[4] == '\0') {
            printf("exit\n");
            return 0;
        }
        if (strcmp(line, "jobs") == 0 && line[4] == '\0') {
            printJob(joblist);
            continue;
        }
        cmd = mparse(line);
        if (cmdnums) {
            if (strcmp(cmd[0], "cd") == 0) {
                builtin_cd(cmd, cmdnums);
            } else {
                result = mexec(cmd, pipe, cmdnums,joblist,&job,jobnums);
                if (job.fb == Back) {
                    joblist[jobnums] = job;
                    jobnums += 1;
                    jobnums %= 128;
                }
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
            free(cmd);

        } else { // input nothing
            free(cmd);
        }
    }
    return 0;
}
