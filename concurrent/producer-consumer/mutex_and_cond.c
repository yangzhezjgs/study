#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int *buf;
    int size;
    int head;
    int tail;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
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
    pthread_mutex_init(&buf->mutex, NULL);
    pthread_cond_init(&buf->not_full, NULL);
    pthread_cond_init(&buf->not_empty, NULL);
}

void *producer(void *p)
{
    buf_t *buf = p;

    pthread_detach(pthread_self());
    for (;;) {
        pthread_mutex_lock(&buf->mutex);
        while (is_full(buf))
            pthread_cond_wait(&buf->not_full, &buf->mutex);
        buf->buf[buf->tail] = 1;
        buf->tail = (buf->tail + 1) % buf->size;
        printf("head: %d tail: %d\n", buf->head, buf->tail);
        if (len(buf) == 1)
            pthread_cond_signal(&buf->not_empty);
        pthread_mutex_unlock(&buf->mutex);
    }
    return NULL;
}

void *consumer(void *p)
{
    buf_t *buf = p;

    pthread_detach(pthread_self());
    for (;;) {
        pthread_mutex_lock(&buf->mutex);
        while (is_empty(buf))
            pthread_cond_wait(&buf->not_empty, &buf->mutex);
        buf->buf[buf->head] = 0;
        buf->head = (buf->head + 1) % buf->size;
        printf("head: %d tail: %d\n", buf->head, buf->tail);
        if (len(buf) == buf->size - 2)
            pthread_cond_signal(&buf->not_full);
        pthread_mutex_unlock(&buf->mutex);
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
