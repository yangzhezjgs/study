#include <pthread.h>
#include <stdio.h>

int reader_count = 0;
int writer_count = 0;

pthread_mutex_t read_block = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_try = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t resource = PTHREAD_MUTEX_INITIALIZER;

void *reader(void *_)
{
    pthread_detach(pthread_self());

    for (;;) {
        /* 当只有读者时，突然出现一个写者：
         *      1. 没有read_block，可能会导致多个读者和一个写者竞争read_try。
         *      2. 有read_block，每次只有一个读者和一个写者竞争read_try，其余读者竞争read_block。
         */
        /* 看定义吧，如果只需要当有写者想写时，不允许读者读，那么去掉read_block也可以。
         * 如果需要尽可能的写者优先，比如上面的情况，那么使用read_block。
         */
        pthread_mutex_lock(&read_block);
        pthread_mutex_lock(&read_try);
        pthread_mutex_lock(&rmutex);
        reader_count++;
        if (reader_count == 1)
            pthread_mutex_lock(&resource);
        pthread_mutex_unlock(&rmutex);
        pthread_mutex_unlock(&read_try);
        pthread_mutex_unlock(&read_block);

        fprintf(stderr, "reading...\n");

        pthread_mutex_lock(&rmutex);
        reader_count--;
        if (reader_count == 0)
            pthread_mutex_unlock(&resource);
        pthread_mutex_unlock(&rmutex);
    }
    return NULL;
}

void *writer(void *_)
{
    pthread_detach(pthread_self());

    for (;;) {
        pthread_mutex_lock(&wmutex);
        writer_count++;
        if (writer_count == 1)
            pthread_mutex_lock(&read_try);
        pthread_mutex_unlock(&wmutex);

        pthread_mutex_lock(&resource);
        fprintf(stderr, "writing...\n");
        pthread_mutex_unlock(&resource);

        pthread_mutex_lock(&wmutex);
        writer_count--;
        if (writer_count == 0)
            pthread_mutex_unlock(&read_try);
        pthread_mutex_unlock(&wmutex);
    }
    return NULL;
}

int main(void)
{
    pthread_t id;
    int i;

    for (i = 0; i < 10; i++)
        pthread_create(&id, NULL, reader, NULL);
    pthread_create(&id, NULL, writer, NULL);
    pthread_exit(NULL);
}
