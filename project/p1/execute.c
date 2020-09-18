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
    if (pid < 0) {
        printf("Failed to fork.\n");
        fflush(stdout);
        return 1;
    }
    else if (pid == 0) { // child process
        if (execvp(cmd[0],cmd) < 0){
            printf("%s: command not found\n", cmd[0]);
            fflush(stdout);
            exit(0);
    } else { // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }


}
    else { /* parent process
              parent will wait for the child to complete */
        wait(NULL);
        printf("Child Complete");
    }
    return 1;
}