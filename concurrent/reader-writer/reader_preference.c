#include <pthread.h>
#include <stdio.h>

int reader_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource = PTHREAD_MUTEX_INITIALIZER;

void *reader(void *_)
{
    /* 当多个读者时，可能会导致写者饥饿。
     * 不过在多个写者时，会和读者一起竞争resource，不能尽可能保证读者优先。
     * 看定义吧，写者优先定义为当有读者在读时，其余读者不需要等待，而当读者和写者一起竞争resource时，无需提供高优先级。
     */
    pthread_detach(pthread_self());
    for (;;) {
        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1)
            pthread_mutex_lock(&resource);
        pthread_mutex_unlock(&mutex);

        fprintf(stderr, "reading...\n");

        pthread_mutex_lock(&mutex);
        reader_count--;
        if (reader_count == 0)
            pthread_mutex_unlock(&resource);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *writer(void *_)
{
    pthread_detach(pthread_self());
    for (;;) {
        pthread_mutex_lock(&resource);
        fprintf(stderr, "writing...\n");
        pthread_mutex_unlock(&resource);
    }

    return NULL;
}

int main(void)
{
    pthread_t id;
    int i;

    for (i = 0; i < 10; i++)
        pthread_create(&id, NULL, writer, NULL);
    pthread_create(&id, NULL, reader, NULL);
    pthread_exit(NULL);
}
