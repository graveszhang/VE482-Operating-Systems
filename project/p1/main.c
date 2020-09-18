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
    int freel = 0, freec = 0;
    while (valid){
        line = mread();
        freel = 1;
        if (strcmp(line,"exit") == 0){
            printf("exit\n");
            fflush(stdout);
            break;
        }
        cmd = mparse(line);
        freec = 1;

//        for (int i = 0; i < 4; i++)
//            printf("cmd[%d] is %s\n", i, cmd[i]);

        valid = mexec(cmd);
    }
    if (freel)
        free(line);
    if (freec)
        free(cmd);
    return 0;
}
