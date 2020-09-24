//
// Created by Graves Zhang on 9/14/20.
//

#ifndef P1_EXECUTE_H
#define P1_EXECUTE_H
int mexec(char **cmd, int pipe);
int mexec_single(char **cmd);
int mexec_pipe(char **cmd);
void builtin_pwd(char **cmd);
void builtin_cd(char **cmd, int cmdnums);
#endif //P1_EXECUTE_H
