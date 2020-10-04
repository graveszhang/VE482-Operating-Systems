//
// Created by Graves Zhang on 9/14/20.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"

typedef enum Error{
    Append,
    Out,
    In,
    Pipe,
    Empty,
    File
} Err;

char ** mparse(char *line, Bool *err) {
    const char delim[] = " \t\r\n\a";
    extern int cmdnums;
    int buffersize = 64;
    char **cmd = malloc(buffersize * sizeof(char *));
    char **cmd_backup;

    // Add space in line around >, <, >>, |
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
        } else if (line[i] == '|') {
            if (i > 0 && line[i - 1] != ' ') {
                goodline[j] = ' ';
                j++;
            }
            while (line[i] == '|') goodline[j++] = line[i++];
            goodline[j++] = ' ';
            continue;
        } else {
            goodline[j++] = line[i++];
        }
    }
    goodline[j] = '\0';
    strcpy(line, goodline);
    free(goodline);

//    printf("DEBUG: line is %s\n",line);
//    Add space among words

    /**************************** Error Handling *****************************/

    Err flag = Empty;
    Bool haveIn = False;
    Bool haveOut = False;
    Bool haveFile = False;

    for (int k = 0; k < strlen(line); ++k) {
        if (line[k] == ' ' || line[k] == '\t' || line[k] == '\r' || line[k] == '\n' || line[k] == '\a')
            continue;

        if (flag == Pipe && line[k] == '|') {
            fprintf(stderr, "error: missing program\n");
            fflush(stdout);
            *err = True;
            break;
        } else if ((flag == Out || flag == In || flag == Pipe) && line[k] == '>') {
            fprintf(stderr, "syntax error near unexpected token `%c\'\n", '>');
            fflush(stdout);
            *err = True;
            break;
        } else if ((flag == Out || flag == In || flag == Pipe) && line[k] == '<') {
            fprintf(stderr, "syntax error near unexpected token `%c\'\n", '<');
            fflush(stdout);
            *err = True;
            break;
        } else if ((flag == Out || flag == In) && line[k] == '|') {
            fprintf(stderr, "syntax error near unexpected token `%c\'\n", '|');
            fflush(stdout);
            *err = True;
            break;
        } else if (haveFile == True && haveIn == True && line[k] == '<') {
            fprintf(stderr, "error: duplicated input redirection\n");
            fflush(stdout);
            *err = True;
            break;
        } else if (haveFile == True && haveOut == True && (line[k] == '>' || line[k] == '|')) {
            fprintf(stderr, "error: duplicated output redirection\n");
            fflush(stdout);
            *err = True;
            break;
        }

        if (line[k] == '|') {
            flag = Pipe;
            haveIn = True;
        } else if (line[k] == '>') {
            if (k < strlen(line) - 1) {
                if (line[k + 1] == '>')
                    flag = Append;
                else {
                    flag = Out;
                    haveOut = True;
                }
            } else {
                flag = Out;
                haveOut = True;
            }
        } else if (line[k] == '<') {
            flag = In;
            haveIn = True;
        } else {
            flag = File;
            haveFile = True;
        }
    }

    /**************************** Error Handling *****************************/

    char *arg = strtok(line, delim);
    i = 0;
    while (arg != NULL) {
        cmd[i] = arg;
        i += 1;
        cmdnums += 1;
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

void qparse(char* line, int len) {
    char buffer[1024];
    memset(buffer, '\0', 1024);
    int i = 0, j = 0;
    char prev = '\0';
    while (j < len) {
        char curr = line[j];
        if (curr == '\'' || curr == '\"') {
            if (prev == '\0')
                prev = curr;
            else if (curr == prev)
                prev = '\0';
            else
                buffer[i++] = curr;
        } else
            buffer[i++] = curr;
        j++;
    }
    strcpy(line, buffer);
//    printf("Debug: Quote Parsed -> %s\n", line);
}
