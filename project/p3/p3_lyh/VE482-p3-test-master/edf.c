//
// Created by liu on 17-12-9.
//

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <limits.h>

int deadline = 0;
int exitflag = 0;
pid_t pid = 0;
unsigned long counter = 0;
clock_t start;

void sigint_cb(int signal)
{
    exitflag = 1;
    printf("pid:%d\tdeadline:%d\ttime:%lu\n", getpid(), deadline, clock() - start);
}

int main(int argc, char *argv[])
{
    start = clock();
    pid = fork();
    if (pid)
    {
        nice(deadline = 2000);
    } else {
        nice(deadline = 1000);
    }

    signal(SIGINT, sigint_cb);

    while (!exitflag)
    {
        if (counter++ == INT_MAX) break;
    }

    sigint_cb(0);


}