#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read.h"
#include "parse.h"
#include "execute.h"

int main() {
    int valid = 1;
    char* line;
    char** cmd;
    int flag = 0;
    int pipe = 0; // without pipe

    while (valid){
        line = mread();

        if(strstr(line,"|")) // execute_pipe
            pipe = 1;
        else
            pipe = 0;

        if (strcmp(line,"exit") == 0){
            flag = 1;
            printf("exit\n");
            fflush(stdout);
            exit(0);
        }
        cmd = mparse(line);
        valid = mexec(cmd,pipe);
        free(line);
        free(cmd);
    }

    if (flag)
        free(line);
    return 0;
}
