//
// Created by Graves Zhang on 9/14/20.
//

#ifndef P1_PARSE_H
#define P1_PARSE_H
#include "execute.h"
char ** mparse(char **cmd, char *line, Bool *err, char *qline, char **qcmd);
void qparse(char* qlines, char* line, int len);

#endif //P1_PARSE_H
