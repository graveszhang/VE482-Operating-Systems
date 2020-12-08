//
// Created by liu on 17-12-9.
//

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

int deadline = 1;
int exitflag = 0;
pid_t pid = 0;
unsigned long counter = 0;
clock_t start;

void sigint_cb(int signal)
{
    exitflag = 1;
    printf("pid:%d\tticket:%d\ttime:%lu\n", getpid(), deadline, clock() - start);
}

int main(int argc, char *argv[])
{
    int nice_val;
    if (argc > 1)
    {
        nice_val = strtol(argv[1], NULL, 10);
    }
    if (nice_val < 2)
    {
        nice_val = 2;
    }
    start = clock();
    pid = fork();
    if (pid)
    {
        nice(deadline = nice_val);
    }

    signal(SIGINT, sigint_cb);

    while (!exitflag)
    {
        counter++;
    }


}