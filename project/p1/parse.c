//
// Created by Graves Zhang on 9/14/20.
//
#include <string.h>
#include <stdlib.h>
#include "parse.h"
char ** mparse(char *line) {
    const char delim[] = " \t\r\n\a";
    int buffersize = 64;
    char **cmd = malloc(buffersize * sizeof(char *));
    char **cmd_backup;

    // Add space in line around >, <, >>
    char *goodline = malloc(sizeof(char) * 1024);
    int i = 0, j = 0;
    while (line[i] != '\0') {
        if (line[i] == '<') {
            if (i > 0 && line[i - 1] != ' ') {
                goodline[j] = ' ';
                j++;
            }
            while (line[i] == '<') goodline[j++] = line[i++];
            goodline[j++] = ' ';
            continue;
        } else if (line[i] == '>') {
            if (i > 0 && line[i - 1] != ' ') {
                goodline[j] = ' ';
                j++;
            }
            while (line[i] == '>') goodline[j++] = line[i++];
            goodline[j++] = ' ';
            continue;
        } else {
            goodline[j++] = line[i++];
        }
    }
    goodline[j] = '\0';
    strcpy(line, goodline);
    free(goodline);

    char *arg = strtok(line, delim);
    i = 0;
    while (arg != NULL) {
        cmd[i] = arg;
        i += 1;
        if (i >= buffersize) {
            buffersize += 64;
            cmd_backup = cmd;
            cmd = realloc(cmd, buffersize * sizeof(char *));
            if (!cmd) {
                cmd = cmd_backup;
                exit(1);
            }
            else{
                cmd_backup = NULL;
            }
        }
        arg = strtok(NULL, delim);
    }
    cmd[i] = NULL;
    return cmd;
}