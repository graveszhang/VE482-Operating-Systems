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
            break;
        }
        cmd = mparse(line);
        valid = mexecute(line,cmd);
    }
    free(line);
    free(cmd);
    return 0;
}
