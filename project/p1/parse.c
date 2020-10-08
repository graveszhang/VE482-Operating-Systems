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

char ** mparse(char **cmd, char *line, Bool *err, char *qline, char **qcmd) {
    const char delim[] = " ";

    extern int cmdnums;
    char goodqline[1024];
    char goodline[1024];
    memset(goodqline, '\0', 1024);
    memset(goodline, '\0', 1024);

    // Add space in line around >, <, >>, |
    int i = 0;
    int j = 0;
    while (line[i] != '\0'){
        if (qline[i] == '1'){
            goodqline[j] = qline[i];
            goodline[j++] = line[i++];
        }
        if (line[i] == '<'){
            if (i > 0 && line[i-1] != ' '){
                goodline[j] = ' ';
                goodqline[j++] = ' ';
            }
            while (line[i] == '<') {
                goodqline[j] = qline[i];
                goodline[j++] = line[i++];
            }

            if (line[i] != '\0'&& line[i] != ' '){
                goodline[j] = ' ';
                goodqline[j++] = ' ';
            }
        }
        else if (line[i] == '>'){
            if (i > 0 && line[i-1] != ' '){
                goodline[j] = ' ';
                goodqline[j++] = ' ';
            }
            while (line[i] == '>') {
                goodqline[j] = qline[i];
                goodline[j++] = line[i++];
            }
            if (line[i] != '\0'&& line[i] != ' '){
                goodline[j] = ' ';
                goodqline[j++] = ' ';
            }
        }
        else if (line[i] == '|'){
            if (i > 0 && line[i-1] != ' '){
                goodline[j] = ' ';
                goodqline[j++] = ' ';
            }
            while (line[i] == '|'){
                goodqline[j] = qline[i];
                goodline[j++] = line[i++];
            }
            if (line[i] != '\0'&& line[i] != ' '){
                goodline[j] = ' ';
                goodqline[j++] = ' ';
            }
        }
        else {
            goodqline[j] = qline[i];
            goodline[j++] = line[i++];
        }
    }
    strcpy(line, goodline);
    strcpy(qline, goodqline);

//    printf("DEBUG: line is %s\n",line);
//    Add space among words

    /**************************** Error Handling *****************************/

//    Err flag = Empty;
//    Bool haveIn = False;
//    Bool haveOut = False;
//    Bool haveFile = False;
//
//    for (int k = 0; k < strlen(line); ++k) {
//        if (line[k] == ' ' || line[k] == '\t' || line[k] == '\r' || line[k] == '\n' || line[k] == '\a')
//            continue;
//
//        if (flag == Pipe && line[k] == '|') {
//            fprintf(stderr, "error: missing program\n");
//            fflush(stdout);
//            *err = True;
//            break;
//        } else if ((flag == Out || flag == In || flag == Pipe) && line[k] == '>') {
//            fprintf(stderr, "syntax error near unexpected token `%c\'\n", '>');
//            fflush(stdout);
//            *err = True;
//            break;
//        } else if ((flag == Out || flag == In || flag == Pipe) && line[k] == '<') {
//            fprintf(stderr, "syntax error near unexpected token `%c\'\n", '<');
//            fflush(stdout);
//            *err = True;
//            break;
//        } else if ((flag == Out || flag == In) && line[k] == '|') {
//            fprintf(stderr, "syntax error near unexpected token `%c\'\n", '|');
//            fflush(stdout);
//            *err = True;
//            break;
//        } else if (haveFile == True && haveIn == True && line[k] == '<') {
//            fprintf(stderr, "error: duplicated input redirection\n");
//            fflush(stdout);
//            *err = True;
//            break;
//        } else if (haveFile == True && haveOut == True && (line[k] == '>' || line[k] == '|')) {
//            fprintf(stderr, "error: duplicated output redirection\n");
//            fflush(stdout);
//            *err = True;
//            break;
//        }
//
//        if (line[k] == '|') {
//            flag = Pipe;
//            haveIn = True;
//        } else if (line[k] == '>') {
//            if (k < strlen(line) - 1) {
//                if (line[k + 1] == '>')
//                    flag = Append;
//                else {
//                    flag = Out;
//                    haveOut = True;
//                }
//            } else {
//                flag = Out;
//                haveOut = True;
//            }
//        } else if (line[k] == '<') {
//            flag = In;
//            haveIn = True;
//        } else {
//            flag = File;
//            haveFile = True;
//        }
//    }

    /**************************** Error Handling *****************************/

    char *arg;
    arg = strtok(line, delim);
    int k = 0;
    while (arg != NULL) {
        cmdnums += 1;
        cmd[k++] = arg;
        arg = strtok(NULL, delim);
    }

    char *aarg;
    aarg = strtok(qline, delim);
    int kk = 0;
    while (aarg != NULL) {
        qcmd[kk++] = aarg;
        aarg = strtok(NULL, delim);
    }

    int m = 0;
    while (m < 1023 && cmd[m] && cmd[m + 1]) {
        if (strcmp(qcmd[m], "1") == 0 || strcmp(qcmd[m + 1], "1") == 0) {
            m++;
            continue;
        }
        if (strcmp(cmd[m], "|") == 0 && strcmp(cmd[m + 1], "|") == 0) {
            fprintf(stderr, "error: missing program\n");
            fflush(stdout);
            *err = True;
            break;
        }
        if (strcmp(cmd[m], ">") == 0 || strcmp(cmd[m], "<") == 0 || strcmp(cmd[m], "|") == 0) {
            if ((strcmp(cmd[m + 1], ">") == 0 || strcmp(cmd[m + 1], "<") == 0 || strcmp(cmd[m + 1], "|") == 0)) {
                printf("syntax error near unexpected token `%s\'\n", cmd[m + 1]);
                fflush(stdout);
                *err = True;
                break;
            }
        }
        m++;
    }
    return cmd;
}

void qparse(char* qlines, char* line, int len) {
    char pline[1024];
    char qline[1024];
    memset(pline, '\0', 1024);
    memset(qline, '\0', 1024);
    int i = 0;
    int j = 0;
    char prev = '\0';
    int Isquote = 0;
    while (j < len) {
        char curr = line[j];
        if (curr == '\'' || curr == '\"'){
            if (prev == '\0') {
                prev = curr;
                Isquote = 1;
            }
            else if (curr == prev) {
                prev = '\0';
                Isquote = 0;
            }
            else{
                qline[i] = '0';
                pline[i++] = curr;
            }
        }
        else{
            if (Isquote == 1) {
                qline[i] = '1';
            }
            else qline[i] = '0';
            if (curr == ' ') qline[i] = ' ';
            pline[i++] = curr;
        }
        j++;
    }
    strcpy(line, pline);
    strcpy(qlines, qline);
}