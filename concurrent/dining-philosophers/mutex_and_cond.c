#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define N 5
#define LEFT(i) (((i) - 1) % N)
#define RIGHT(i) (((i) + 1) % N)

enum {
    THINKING,
    HUNGRY,
    EATING
} state[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t need_fork[N];

/* 能直接获取2把叉子才行 */
void *philosopher(void *p)
{
    int i = (int)(uintptr_t)p;

    pthread_detach(pthread_self());
    for (;;) {
        fprintf(stderr, "%d: thinking...\n", i);

        pthread_mutex_lock(&mutex);
        state[i] = HUNGRY;
        while (state[LEFT(i)] == EATING || state[RIGHT(i)] == EATING)
            pthread_cond_wait(&need_fork[i], &mutex);
        state[i] = EATING;
        pthread_mutex_unlock(&mutex);

        fprintf(stderr, "%d: eating...\n", i);

        pthread_mutex_lock(&mutex);
        state[i] = THINKING;
        if (state[RIGHT(i)] == HUNGRY && state[RIGHT(i + 1)] != EATING)
            pthread_cond_signal(&need_fork[RIGHT(i)]);
        else if (state[LEFT(i)] == HUNGRY && state[LEFT(i - 1)] != EATING)
            pthread_cond_signal(&need_fork[LEFT(i)]);
        pthread_mutex_unlock(&mutex);

    }

    return NULL;
}

int main(void)
{
    uintptr_t i;

    for (i = 0; i < N; i++) {
        pthread_cond_init(&need_fork[i], NULL);
        state[i] = THINKING;
    }

    pthread_t id;
    for (i = 0; i < N; i++)
        pthread_create(&id, NULL, philosopher, (void *)i);
    pthread_exit(NULL);
}
