//
// Created by Graves Zhang on 9/18/20.
//

#ifndef P1_REDIRECT_H
#define P1_REDIRECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void redirection(char **cmd);
static void rout(char *filename);
static void rin(char *filename);
static void rapp(char *filename);
static void rnxt(char **cmd, int index);

#endif //P1_REDIRECT_H
