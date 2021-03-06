#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define N 1000000
int count = 0;

void *thread_count(void *a) {
    int i, tmp;
    sem_t *Sem = a;
    for (i = 0; i < N; i++) {
        sem_wait(Sem);
        tmp = count;
        tmp = tmp + 1;
        count = tmp;
        sem_post(Sem);
    }
}

int main(int argc, char *argv[]) {
    int i;
    sem_t Sem;
    pthread_t *t = malloc(2 * sizeof(pthread_t));
    if (sem_init(&Sem, 0, 1)) {
        printf("ERROR init semaphore\n");
        exit(0);
    }
    for (i = 0; i < 2; i++) {
        if (pthread_create(t + i, NULL, thread_count, &Sem)) {
            fprintf(stderr, "ERROR creating thread %d\n", i);
            exit(1);
        }
    }
    for (i = 0; i < 2; i++) {
        if (pthread_join(*(t + i), NULL)) {
            fprintf(stderr, "ERROR joining thread\n");
            exit(1);
        }
    }
    if (count < 2 * N)
        printf("Count is %d, but should be %d\n", count, 2 * N);
    else
        printf("Count is[%d]\n", count);
    free(t);
    pthread_exit(NULL);
}
