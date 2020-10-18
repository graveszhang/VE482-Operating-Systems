//
// Created by grave on 2020/10/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "linkedlist.h"

const char *DATA_TYPES[3] = {"int.txt", "double.txt", "string.txt"};
const char *SORT_TYPES[3] = {"inc", "dec", "rand"};

int int_inc(const void *a, const void *b) {
    int A = *(int *) (((Node *) a)->data);
    int B = *(int *) (((Node *) b)->data);
    if (A==B) return 0;
    return A > B ? 1 : -1;
}

int double_inc(const void *a, const void *b) {
    double A = *(double *) (((Node *) a)->data);
    double B = *(double *) (((Node *) b)->data);
    if (A==B) return 0;
    return A > B ? 1 : -1;
}

int int_dec(const void *a, const void *b) {
    return -int_inc(a, b);
}

int double_dec(const void *a, const void *b) {
    return -double_inc(a, b);
}

int string_inc(const void *a, const void *b) {
    return strcmp((char *) (((Node *) a)->data), (char *) (((Node *) b)->data));
}

int string_dec(const void *a, const void *b) {
    return strcmp((char *) (((Node *) b)->data), (char *) (((Node *) a)->data));
}

int all_rand(const void *a, const void *b) {
    return (rand() % 2) * 2 - 1;
}

int (*const cmp[3][3])(const void *, const void *) = {
        {int_inc,    int_dec,    all_rand},
        {double_inc, double_dec, all_rand},
        {string_inc, string_dec, all_rand}
};

void int_print(FILE *file, const void *a) {
    fprintf(file, "%d", *(int *) (a));
}

void double_print(FILE *file, const void *a) {
    fprintf(file, "%lf", *(double *) (a));
}

void string_print(FILE *file, const void *a) {
    fprintf(file, "%s", (char *) (a));
}

void (*const print[3])(FILE *file, const void *) = {
        int_print, double_print, string_print
};

void sort(int i, int j) {
    char filename[20];
    int len = 0;

    // Create a file
    strcpy(filename, "rand");
    len = strlen(filename);
    if (len) {
        filename[len] = '_';
        strcpy(filename + len + 1, DATA_TYPES[i]);
    }
    FILE *file = fopen(filename, "r");
    if (!file)
        return;

    // Start parsing
    printf("reading %s\n", filename);
    char buf[1024];
    List *newlist;
    list_init(&newlist);
    while (!feof(file)) {
        fgets(buf, 1024, file);
        char *pos = strchr(buf, '=');
        if (!pos)
            continue;
        len = pos - buf;
        *pos = '\0';
        void *data;
        char *str = (char *) malloc(sizeof(char) * (len + 1));
        strcpy(str, buf);
        switch (i) {
            case 0: // int
                data = malloc(sizeof(int));
                *((int *) data) = strtol(pos + 1, NULL, 10);
                break;
            case 1: // double
                data = malloc(sizeof(double));
                *((double *) data) = strtod(pos + 1, NULL);
                break;
            case 2: // str
                len = strlen(pos + 1);
                data = malloc(sizeof(char) * (len + 1));
                strcpy(data, pos + 1);
                pos = data + strlen(data) - 1;
                while(*pos=='\n')
                    *(pos--)='\0';
                break;
            default:
                break;
        }
        list_insert(newlist, str, data);
    }
    fclose(file);

    // Start sorting
    printf("sorting elements\n");
    list_sort(newlist, cmp[i][j]);
    strcpy(filename, SORT_TYPES[j]);
    len = strlen(filename);
    if (len) {
        filename[len] = '_';
        strcpy(filename + len + 1, DATA_TYPES[i]);
    }

    // Start output to newfile
    printf("writing %s\n", filename);
    FILE *output = fopen(filename, "w");
    list_print(newlist, output, print[i]);
    fclose(output);
    list_free(newlist);
}

int main(int argc, char *argv[]) {
    if (argc < 3)
        return 0;

    srand(time(NULL));
    char filename[20];
    int i = 0;
    int j = 0;

    for (i = 0; i < 3; ++i) {
        strcpy(filename, "rand");
        int len = strlen(filename);
        if (len){
            filename[len] = '_';
            strcpy(filename + len + 1, DATA_TYPES[i]);
            if (strcmp(filename, argv[1]) == 0) {
                break;
            }
        }
    }

    for (j = 0; j < 3; ++j) {
        if (strcmp(SORT_TYPES[j], argv[2]) == 0) {
            break;
        }
    }
    sort(i, j);
    return 0;
}
