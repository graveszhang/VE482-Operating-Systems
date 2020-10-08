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
pid_t mainpid;
jmp_buf environment;

enum {
    F_NOT_EXIST_IN,
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
        job->state[i] = -1;
    }
    job->content[i] = '\0';
    job->fb = Back; // back for default
    job->id = 1;
    job->pidnums = 0;
}

void initJobList(Job *joblist){
    for (int i = 0; i < 128; i++){
        initJob(&(joblist[i]));
    }
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

void printJob(Job *joblist,int jobnums){
    if (!jobnums)
        return;
    for (int i = 0; i < jobnums; ++i) {
        printf("[%d] ",joblist[i].id);
        fflush(stdout);
        if (JobIsRunning(joblist[i])){
            printf("running ");
        } else {
            printf("done ");
        }
        fflush(stdout);
        printf("%s\n", joblist[i].content);
        fflush(stdout);
    }
}

int main() {
    int in = dup(STDIN_FILENO);
    int out = dup(STDOUT_FILENO);
    int idx;
    int pipe; // without pipe
    int result = -1;
    char c;
    char *cmd[1024];
    char line[1024];
    char goodline[1024];
    char *qcmd[1024];
    Bool rdc;
    Bool qdc;
    Job joblist[128];
    initJobList(joblist);
    mainpid = getpid();
    setpgid(0, 0);
    signal(SIGINT, sigint_handler);
//    signal(SIGINT,SIG_DFL); // DFL directly exit the program

    if (sigsetjmp(environment, 1) == 2) {
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
    }

    while (1) {
        memset(cmd, '\0', 1024);
        memset(line, '\0', 1024);
        memset(goodline, '\0', 1024);
        memset(qcmd, '\0', 1024);

        rdc = 0;
        qdc = 0;
        idx = 0;
        pipe = 0;
        cmdnums = 0;

        printf("mumsh $ ");
        fflush(stdout);

        while(1) {
            c = (char) fgetc(stdin);
            if (idx >= 1024) break;

            if (c == '\n') {
                if (idx == 0) {
                    printf("mumsh $ ");
                    continue;
                }
                rdc = Redirection_Complete(line, idx);
                qdc = Quotation_Complete(line);

                if (rdc == -1) break;
                if (qdc == True && rdc == True) {
                    qparse(goodline, line, idx);
                    break;
                } else if (qdc == False) {
                    line[idx++] = '\n';
                    printf("> ");
                    fflush(stdout);
                    continue;
                } else if (rdc == False) {
                    printf("> ");
                    fflush(stdout);
                    continue;
                }
            } else if (c == EOF) {
                if (line[0] != '\0') {
                    fflush(stdin);
                    continue;
                } else {
                    printf("exit\n");
                    fflush(stdout);
                    return 0;
                }
            } else line[idx] = c;
            idx++;
        }
        if (rdc == -1)
            continue;
        if(line[0] == '\n') continue;

        if (strcmp(line, "exit") == 0 && line[4] == '\0'){
            printf("exit\n");
            return 0;
        }

        int id = 0;
        while(id < 1024 && line[id]){
            if (goodline[id] == '1'){
                id++;
                continue;
            }
            if (line[id] == '|'){
                pipe = 1;
                break;
            }
            id++;
        }

        if (strcmp(line, "jobs") == 0 && line[4] == '\0'){
            printJob(joblist,jobnums);
            continue;
        }
        Job job;
        initJob(&job);
        for (int i = 0; i < 1024; i++){
            job.content[i] = line[i];
        }
        job.id = jobnums + 1;
        if (line[idx - 1] == '&'){
            line[idx - 1] = '\0';
            job.fb = Back;
            printf("[%d] ", job.id);
            fflush(stdout);
            printf(" %s\n", job.content);
            fflush(stdout);
        }
        else job.fb = Front;
        job.pidnums = 0;
//        printf("Debug: Job FB is %d\n",job.FB);
//        printf("Debug: Job id is %d\n",job.id);

        Bool Errparse = False;
        mparse(cmd, line, &Errparse, goodline, qcmd);
        if (Errparse == True)
            continue;

        if (cmdnums) {
            if (pipe == 0 && strcmp(cmd[0], "cd") == 0) {
                builtin_cd(cmd,cmdnums);
            } else {
                result = mexec(cmd, cmdnums, pipe, &job, joblist, jobnums, mainpid, qcmd);
                if (job.fb == Back) {
                    joblist[jobnums] = job;
                    jobnums += 1;
                    jobnums %= 128;
                }
                switch (result) {
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
        }
    }
}
