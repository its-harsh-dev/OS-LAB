#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex, wrt;
int readcount = 0;

void* reader(void* arg)
{
    int id = *((int*)arg);

    sem_wait(&mutex);
    readcount++;
    if(readcount == 1)
        sem_wait(&wrt);      // first reader blocks writers
    sem_post(&mutex);

    printf("Reader %d is reading\n", id);
    sleep(1);
    printf("Reader %d finished reading\n", id);

    sem_wait(&mutex);
    readcount--;
    if(readcount == 0)
        sem_post(&wrt);      // last reader unblocks writers
    sem_post(&mutex);

    return NULL;
}

void* writer(void* arg)
{
    int id = *((int*)arg);

    sem_wait(&wrt);          // writer needs exclusive access

    printf("Writer %d is writing\n", id);
    sleep(1);
    printf("Writer %d finished writing\n", id);

    sem_post(&wrt);
    return NULL;
}

int main()
{
    int nReaders, nWriters;
    printf("Enter no. of readers : ");
    scanf("%d", &nReaders);

    printf("Enter no. of writers : ");
    scanf("%d", &nWriters);

    pthread_t r[nReaders], w[nWriters];
    int rID[nReaders], wID[nWriters];

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    int i = 0;

    // Create reader threads
    i = 0;
    while(i < nReaders)
    {
        rID[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &rID[i]);
        i++;
    }

    // Create writer threads
    i = 0;
    while(i < nWriters)
    {
        wID[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &wID[i]);
        i++;
    }

    // Join reader threads
    i = 0;
    while(i < nReaders)
    {
        pthread_join(r[i], NULL);
        i++;
    }

    // Join writer threads
    i = 0;
    while(i < nWriters)
    {
        pthread_join(w[i], NULL);
        i++;
    }

    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
