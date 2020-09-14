//
// Created by Graves Zhang on 9/14/20.
//

#include "read.h"
#include <stdio.h>
#include <stdlib.h>
char * mread() {
    printf("mumsh $ ");

    int c;
    int i = 0;
    int buffersize = 1024;

    char *buffer = malloc(sizeof(char) * buffersize);

    if (!buffer) {
        exit(1);
    }

    while ((c=getchar())!=EOF) {

        if (c == '\n') {
            buffer[i] = '\0';
            return buffer;
        } else {
            buffer[i] = c;
        }
        i += 1;

        if (i >= buffersize) {
            buffersize += 1024;
            buffer = realloc(buffer, buffersize);
            if (!buffer) {
                exit(1);
            }
        }
    }
}

