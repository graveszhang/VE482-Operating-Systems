//
// Created by Graves Zhang on 9/14/20.
//

#include "execute.h"
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int mexec(char **cmd){
    if (cmd[0] == NULL) return 1;
    int status;
    pid_t pid;
    pid = fork();
    if(pid != 0){
        wait(&status);
    } else{
        execvp(cmd[0], cmd);
    }
    return 1;
}
