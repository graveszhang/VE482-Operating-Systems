//
// Created by Graves Zhang on 9/14/20.
//

#ifndef P1_EXECUTE_H
#define P1_EXECUTE_H
int mexec(char **cmd, int pipe, int cmdnums);
int mexec_pipe(char** cmd, int* pipeIdx, int cmdnums, int cnt);
int mexec_single(char** cmd, int cmdnums);
void builtin_cd(char** cmd, int cmdnums);
void builtin_pwd(char **cmd);

#endif //P1_EXECUTE_H
