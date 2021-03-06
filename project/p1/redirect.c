//
// Created by Graves Zhang on 9/18/20.
//

#include "redirect.h"

void redirection(char **cmd, char **qcmd) {
    int numin = 0;
    int numout = 0;
    int i = 0;
    while (cmd[i] != NULL) {
        if (strcmp(qcmd[i], "1") == 0 || strcmp(qcmd[i], "11") == 0) {
            i += 1;
            continue;
        }
        if (strcmp(cmd[i], "<") == 0) numin += 1;
        else if (strcmp(cmd[i], ">") == 0 || strcmp(cmd[i], ">>") == 0) {
            numout += 1;
        }
        i++;
    }
    if (numout > 1) {
        fprintf(stderr, "error: duplicated output redirection\n");
        fflush(stdout);
        exit(1);
    }
    if (numin > 1) {
        fprintf(stderr, "error: duplicated input redirection\n");
        fflush(stdout);
        exit(1);
    }
    if (numout == 0 && numin == 0)
        return;

    i = 0;
    while (cmd[i] != NULL) {
        if (strcmp(qcmd[i], "1") == 0 || strcmp(qcmd[i], "11") == 0) {
            i++;
            continue;
        }
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
        fprintf(stderr, "%s: No such file or directory\n", filename);
    umask(0000);
    int fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (fd_out < 0){
        printf("%s: Permission denied\n", filename);
        fflush(stdout);
        exit(1);
    }
    int fd;
    if (fd_out > 0){
        fd = dup2(fd_out, 1);
        if (fd < 0){
            printf("Cannot duplicate file descriptor.\n");
            fflush(stdout);
        }
    }
//    else
//        printf("File: %s IO Error!", filename);
    close(fd_out);
}

static void rin(char *filename) {
    if (filename == NULL)
        fprintf(stderr, "%s: No such file or directory\n", filename);
    int fd_in = open(filename, O_RDONLY);
    if (fd_in < 0) {
        printf("%s: No such file or directory\n", filename);
        fflush(stdout);
        exit(1);
    }
    int fd;
    if (fd_in > 0){
        fd = dup2(fd_in, 0);
        if (fd < 0) {
            printf("Cannot duplicate file descriptor.\n");
            fflush(stdout);
        }
    }
//    else
//        printf("File: %s IO Error!", filename);
    close(fd_in);
}

static void rapp(char *filename) {
    if (filename == NULL)
        fprintf(stderr, "%s: No such file or directory\n", filename);
    umask(0000);
    int fd_out = open(filename, O_APPEND | O_CREAT | O_WRONLY, 0777);
    if (fd_out < 0) {
        printf("%s: Permission denied\n", filename);
        fflush(stdout);
        exit(1);
    }
    int fd;
    if (fd_out > 0) {
        fd = dup2(fd_out, 1);
        if (fd < 0) {
            printf("Cannot duplicate file descriptor.\n");
            fflush(stdout);
        }
    }
//    else
//        printf("File: %s IO Error!", filename);
    close(fd_out);
}

static void rnxt(char **cmd, int index) {
    do {
        cmd[index] = cmd[index + 2];
        index++;
    } while (cmd[index] != NULL);
    cmd[index] = NULL;
}