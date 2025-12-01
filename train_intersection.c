#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define NUM_TRAINS 20

char* dirName[] = {"North", "South", "East", "West"};

sem_t crossing;

void* train(void* arg)
{
    int id = *((int*)arg);
    int direction = rand() % 4;

    printf("Train %d arrived from %s direction\n", id, dirName[direction]);

    sem_wait(&crossing);

    printf("Train %d from %s is CROSSING the track...\n", id, dirName[direction]);
    sleep(2);
    printf("Train %d from %s has EXITED the track.\n", id, dirName[direction]);

    sem_post(&crossing);

    return NULL;
}

int main()
{
    srand(time(NULL));

    pthread_t train_thread[NUM_TRAINS];
    int trainsID[NUM_TRAINS];

    sem_init(&crossing, 0, 1);   

    for(int i = 0; i < NUM_TRAINS; i++)
    {
        trainsID[i] = i + 1;
        pthread_create(&train_thread[i], NULL, train, &trainsID[i]);
        usleep(200000);  
    }

    for(int i = 0; i < NUM_TRAINS; i++)
        pthread_join(train_thread[i], NULL);

    sem_destroy(&crossing);

    return 0;
}
