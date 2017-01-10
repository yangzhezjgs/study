#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

#define N 5

sem_t forks[N];
sem_t room;

void *philosopher(void *p)
{
    int i = (int)(uintptr_t)p;

    pthread_detach(pthread_self());
    for (;;) {
        fprintf(stderr, "%d: thinking...\n", i);
        /* 一次进入4个，所以必然有一个可以eat。
         * 这里使用room限制进入数量，也可以使用特定资源获取顺序。
         * 比如先拿index小的，再拿index大的，当前4个拿起index小的时，第5个会等待第一个，也就限制了4个人进入，其中第4个可以eat。
         */
        sem_wait(&room);
        sem_wait(&forks[i]);
        sem_wait(&forks[(i + 1) % N]);
        fprintf(stderr, "%d: eating...\n", i);
        sem_post(&forks[(i + 1) % N]);
        sem_post(&forks[i]);
        sem_post(&room);
    }

}

int main(void)
{
    uintptr_t i;

    for (i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);
    sem_init(&room, 0, N - 1);

    pthread_t id;
    for (i = 0; i < N; i++)
        pthread_create(&id, NULL, philosopher, (void *)i);
    pthread_exit(NULL);
}
