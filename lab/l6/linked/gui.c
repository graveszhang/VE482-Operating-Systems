#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logic.h"
#include "gui.h"

newmain(int argc, char *argv[]){
    if (argc < 3)
        return 0;

    srand(time(NULL));
    char filename[20];
    char sin[100];
    int flag = 1;
        printf("***************************************************");
        printf("*************Welcome to Menu Interface!************");
        printf("***************************************************");

    while (flag)
    {
        printf("***************** DATA OPTIONS ******************\n");
        printf("*** A. rand_int.txt (read random integers) ******\n");
        printf("*** B. rand_double.txt (read random doubles) ****\n");
        printf("*** C. rand_string.txt (read random strings) ****\n");
        printf("*** D. exit (exit the program) ******************\n");
        printf("***************** DATA OPTIONS ******************\n");

        int i = 3;
        for (int m = 0; m < 100; ++m)
            sin[m] = '\0';

        while (i == 3)
        {
            for (i = 0; i < 3; ++i) {
                printf("> ");
                fgets(sin, 999, stdin);
                sin[strlen(sin) - 1] = '\0';
                if (!strcmp(sin, "exit")) {
                    flag = 0;
                    break;
                }

                strcpy(filename, "rand");
                int len = strlen(filename);
                if (len){
                    filename[len] = '_';
                    strcpy(filename + len + 1, DATA_TYPES[i]);
                    if (strcmp(filename, sin) == 0) {
                        break;
                    }
                }
            }
        }
        if (!flag) break;        

        printf("***************** SORT OPTIONS ******************\n");
        printf("*** A. inc (output in increasing order) *********\n");
        printf("*** B. dec (output in decreasing order) *********\n");
        printf("*** C. rand (output in random order) ************\n");
        printf("*** D. exit (exit the program) ******************\n");
        printf("***************** SORT OPTIONS ******************\n");

        int j = 3;
        for (int n = 0; n < 100; ++n)
            sin[n] = '\0';

        while (j == 3)
        {
            for (j = 0; j < 3; ++j) {
                printf("> ");
                fgets(sin, 999, stdin);
                sin[strlen(sin) - 1] = '\0';
                if (!strcmp(sin, "exit")) {
                    flag = 0;
                    break;
                }

                if (strcmp(SORT_TYPES[j], sin) == 0) {
                    break;
                }
            }   
        }
        if (!flag) break;
        sort(i, j);
        printf("The sorting is completed successfully! Want to try again?(Y/N)\n");
        for (int l = 0; l < 100; ++l)
            sin[l] = '\0';
        printf("> ");
        fgets(sin, 999, stdin);
        sin[strlen(sin) - 1] = '\0';
        if (sin == 'N') {
            flag = 0;
            break;
        }
        if (!flag) break;        
    }
    return 0;
}

oldmain(int argc, char *argv[]){
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

    return 0;
}