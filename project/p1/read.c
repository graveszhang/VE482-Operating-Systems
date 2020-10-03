//
// Created by Graves Zhang on 9/14/20.
//

#include "read.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int mread(char *line) {
    printf("mumsh $ ");
    fflush(stdout);

    char c;
    int i = 0;

    char buffer[1024];
    memset(buffer, '\0', 1024);

    while ((c = (char) fgetc(stdin)) != '\n') {
        if (c == EOF) { // handle ctrl-d
//            printf("DEBUGG:%s\n", buffer[0]);
            if (buffer[0] != '\0')
                continue;
            else {
                printf("exit\n");
                fflush(stdout);
                exit(0);
            }
        } else {
            buffer[i] = c;
        }
        i += 1;
    }
    buffer[i] = '\0';
    strcpy(line, buffer);
    return 0;
}

