#include <pthread.h>
#include <stdio.h>

int reader_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t service = PTHREAD_MUTEX_INITIALIZER;

void *reader(void *_)
{
    /* 竞争得到service的服务。
     */
    pthread_detach(pthread_self());
    for (;;) {
        pthread_mutex_lock(&service);
        pthread_mutex_lock(&mutex);
        reader_count++;
        if (reader_count == 1)
            pthread_mutex_lock(&resource);
        pthread_mutex_unlock(&service);
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
        pthread_mutex_lock(&service);
        pthread_mutex_lock(&resource);
        pthread_mutex_unlock(&service);

        fprintf(stderr, "writing...\n");
        pthread_mutex_unlock(&resource);
    }

    return NULL;
}

int main(void)
{
    pthread_t id;
    int i;

    for (i = 0; i < 2; i++) {
        pthread_create(&id, NULL, writer, NULL);
        pthread_create(&id, NULL, reader, NULL);
    }
    pthread_exit(NULL);
}
