//
// Created by Graves Zhang on 9/14/20.
//

#ifndef P1_EXECUTE_H
#define P1_EXECUTE_H
#include <unistd.h>
# define PIPENUMS 16

typedef enum _FB{
    Front = 0,
    Back = 1
} FB;

typedef struct _Job{
    pid_t pid[PIPENUMS];
    int pidnums;
    int id;
    int state[PIPENUMS];
    FB fb; // 1 for back, 0 for front
    char content[1024];
}Job;


typedef enum _bool{
    False = 0,
    True = 1
} Bool;

int mexec(char **cmd, int pipe, int cmdnums, Job* joblist, Job* job, int jobnums);
int mexec_pipe(char** cmd, int* pipeIdx, int cmdnums, int cnt, Job* joblist, Job* job, int jobnums);
int mexec_single(char** cmd, int cmdnums, Job* joblist, Job* job, int jobnums);
void builtin_cd(char** cmd, int cmdnums);
void builtin_pwd(char **cmd);

#endif //P1_EXECUTE_H
