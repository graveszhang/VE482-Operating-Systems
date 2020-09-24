//
// Created by Graves Zhang on 9/14/20.
//

#ifndef P1_EXECUTE_H
#define P1_EXECUTE_H
int mexec(char **cmd, int pipe, int cmdnums);
//int mexec_single(char **cmd, int left, int right);
//int mexec_pipe(char **cmd, int left, int right);
void builtin_pwd(char **cmd);

int mexec_pipe(char** cmd, int* pipeIdx, int cmdnums);
int mexec_single(char** arg, int cmdnums);
int builtin_cd(char** arg, int cmdnums);


#endif //P1_EXECUTE_H
