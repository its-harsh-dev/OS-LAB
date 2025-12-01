#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_USERS 10

int buffer[BUFFER_SIZE];
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
int in = 0, out = 0;

void* user(void* arg)
{
    int id = *((int*)arg);

    while (1)
    {
        sleep(rand() % 4 + 1);

        sem_wait(&empty);
        pthread_mutex_lock(&mutex);

        int job = rand() % 1000;
        buffer[in] = job;
        printf("User %d submitted job %d at position %d\n", id, job, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* printer(void* arg)
{
    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int job = buffer[out];
        printf("Printer started job %d from position %d\n", job, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t users[NUM_USERS];
    pthread_t printer_thread;
    int userID[NUM_USERS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&printer_thread, NULL, printer, NULL);

    int i = 0;
    while (i < NUM_USERS)
    {
        userID[i] = i + 1;
        pthread_create(&users[i], NULL, user, &userID[i]);
        i++;
    }

    pthread_join(printer_thread, NULL);

    i = 0;
    while (i < NUM_USERS)
    {
        pthread_join(users[i], NULL);
        i++;
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
