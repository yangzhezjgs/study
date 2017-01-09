#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *buf;
    int size;
    int head;
    int tail;
    sem_t mutex;
    sem_t slots;
    sem_t items;
} buf_t;

static inline bool is_full(buf_t *buf)
{
    return buf->head == (buf->tail + 1) % buf->size;
}

static inline bool is_empty(buf_t *buf)
{
    return buf->head == buf->tail;
}

static inline int len(buf_t *buf)
{
    // return buf->tail >= buf->head ? buf->tail - buf->head : buf->tail + buf->size - buf->head;
    return (buf->tail - buf->head + buf->size) % buf->size;
}

void buf_init(buf_t *buf, int n)
{
    buf->buf = malloc(sizeof(int) * n);
    buf->size = n;
    buf->head = buf->tail = 0;
    sem_init(&buf->mutex, 0, 1);
    sem_init(&buf->slots, 0, n);
    sem_init(&buf->items, 0, 0);
}

void *producer(void *p)
{
    buf_t *buf = p;

    pthread_detach(pthread_self());
    for (;;) {
        sem_wait(&buf->slots);
        sem_wait(&buf->mutex);
        buf->buf[buf->tail] = 1;
        buf->tail = (buf->tail + 1) % buf->size;
        printf("head: %d tail: %d\n", buf->head, buf->tail);
        sem_post(&buf->mutex);
        sem_post(&buf->items);
    }
    return NULL;
}

void *consumer(void *p)
{
    buf_t *buf = p;

    pthread_detach(pthread_self());
    for (;;) {
        sem_wait(&buf->items);
        sem_wait(&buf->mutex);
        buf->buf[buf->head] = 0;
        buf->head = (buf->head + 1) % buf->size;
        printf("head: %d tail: %d\n", buf->head, buf->tail);
        sem_post(&buf->mutex);
        sem_post(&buf->slots);
    }
    return NULL;
}

#define N 20

int main(void)
{
    int i;
    buf_t buf;
    pthread_t producer_tid;
    pthread_t consumer_tid;

    buf_init(&buf, N);
    for (i = 0; i < 2; i++) {
        pthread_create(&producer_tid, NULL, producer, &buf);
        pthread_create(&consumer_tid, NULL, consumer, &buf);
    }
    pthread_exit(NULL);
}
