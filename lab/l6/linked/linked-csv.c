//
// Created by grave on 2020/11/8.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-csv.h"

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
         tok && *tok;
         tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

void fileInType(){ // General API for multi-filetypes support
    FILE* stream = fopen("input", "r");
    char* data1[64];
    char* data2[64];
    char* data3[64];
    char line[1024];
    int i = 0, j = 0, k = 0;
    while (fgets(line, 1024, stream))
    {
        char* tmp = strdup(line);
        data[i] = getfield(tmp, 1);
        data[j] = getfield(tmp, 2);
        data[k] = getfield(tmp, 3);
        i += 1;
        j += 1;
        k += 1;
        free(tmp);
    }
}