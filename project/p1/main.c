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
    while (valid){
        line = mread();
        if (!strcmp(line,"exit")){
            printf("exit\n");
            break;
        }
        cmd = mparse(line);
        valid = mexec(cmd);
    }
    free(line);
    free(cmd);
    return 0;
}
