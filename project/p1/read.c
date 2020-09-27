//
// Created by Graves Zhang on 9/14/20.
//

#include "read.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char * mread() {
    printf("mumsh $ ");
    fflush(stdout);

    char c;
    int i = 0;
    int buffersize = 1024;

    char *buffer = malloc(sizeof(char) * buffersize);

    if (!buffer) {
        free(buffer);
        exit(1);
    }
//    while (1) {
//        c = (char) getchar();
//        if (c == EOF) {
//            if (buffer[0])
//                continue;
//            else {
//                printf("exit\n");
//                fflush(stdout);
//                return 0;
//            }
//        } else if (c == '\n'){
//            break;
//        } else {
//            buffer[i] = c;
//            i += 1;
//        }
    while((c = (char)fgetc(stdin)) != '\n') {
        if (i >= buffersize) {
            buffersize += 1024;
            char *buffer_backup = buffer;
            buffer = realloc(buffer, buffersize);
            if (!buffer) {
                buffer = buffer_backup;
                exit(1);
            } else {
                buffer_backup = NULL;
            }
        }
        if (c == EOF || !c) { //c reads nothing
//            printf("DEBUGG:%s\n", buffer[0]);
            if (buffer[0])
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
    return buffer;
}

