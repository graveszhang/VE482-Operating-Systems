//
// Created by Graves Zhang on 9/18/20.
//

#include "redirect.h"

void redirection(char **cmd){
    int i = 0;
    while (cmd[i] != NULL) {
        if (strcmp(cmd[i], ">") == 0) {
            rout(cmd[i + 1]);
            rnxt(cmd, i);
            --i;
        } else if (strcmp(cmd[i], ">>") == 0) {
            rapp(cmd[i + 1]);
            rnxt(cmd, i);
            --i;
        } else if (strcmp(cmd[i], "<") == 0) {
            rin(cmd[i + 1]);
            rnxt(cmd, i);
            --i;
        }
        i++;
    }
}

static void rout(char *filename){
    if (filename == NULL)
        printf("Error! No file name found.\n");
    umask(0000);
    int fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd_out > 0)
        dup2(fd_out, 1);
    else
        printf("File: %s IO Error!", filename);
    close(fd_out);
}

static void rin(char *filename) {
    if (filename == NULL)
        printf("Error! No file name found.\n");
    int fd_in = open(filename, O_RDONLY);
    if (fd_in > 0)
        dup2(fd_in, 0);
    else
        printf("File: %s IO Error!", filename);
    close(fd_in);
}

static void rapp(char *filename) {
    if (filename == NULL)
        printf("Error! No file name found.\n");;
    umask(0000);
    int fd_out = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0777);
    if (fd_out > 0)
        dup2(fd_out, 1);
    else
        printf("File: %s IO Error!", filename);
    close(fd_out);
}

static void rnxt(char **cmd, int index) {
    do {
        cmd[index] = cmd[index + 2];
        index++;
    } while (cmd[index] != NULL);
    cmd[index] = NULL;
}