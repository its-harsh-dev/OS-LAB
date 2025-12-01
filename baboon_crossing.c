#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define NUM_BABOONS 10

sem_t east_wait;
sem_t west_wait;
pthread_mutex_t mutex;

int east_on_rope = 0;
int west_on_rope = 0;

void* east_west_baboons(void* arg)
{
    int id = *((int*)arg);

    while(1)
    {
        sem_wait(&east_wait);        // Try to enter east direction
        pthread_mutex_lock(&mutex);

        east_on_rope++;
        if(east_on_rope == 1)
            sem_wait(&west_wait);     // Block west direction

        pthread_mutex_unlock(&mutex);

        printf("Baboon %d is crossing the rope from EAST → WEST\n", id);
        sleep(2);
        printf("Baboon %d finished EW crossing.\n", id);

        pthread_mutex_lock(&mutex);

        east_on_rope--;
        if(east_on_rope == 0)
            sem_post(&west_wait);     // Allow west direction

        pthread_mutex_unlock(&mutex);
        sem_post(&east_wait);
    }
}

void* west_east_baboons(void* arg)
{
    int id = *((int*)arg);

    while(1)
    {
        sem_wait(&west_wait);
        pthread_mutex_lock(&mutex);

        west_on_rope++;
        if(west_on_rope == 1)
            sem_wait(&east_wait);

        pthread_mutex_unlock(&mutex);

        printf("Baboon %d is crossing the rope from WEST → EAST\n", id);
        sleep(2);
        printf("Baboon %d finished WE crossing.\n", id);

        pthread_mutex_lock(&mutex);

        west_on_rope--;
        if(west_on_rope == 0)
            sem_post(&east_wait);

        pthread_mutex_unlock(&mutex);
        sem_post(&west_wait);
    }
}

int main()
{
    srand(time(NULL));

    sem_init(&east_wait, 0, 1);
    sem_init(&west_wait, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    pthread_t baboon_thread[NUM_BABOONS];
    int baboonID[NUM_BABOONS];

    for(int i = 0; i < NUM_BABOONS; i++)
    {
        baboonID[i] = i + 1;

        if(rand() % 2 == 0)
            pthread_create(&baboon_thread[i], NULL, east_west_baboons, &baboonID[i]);
        else
            pthread_create(&baboon_thread[i], NULL, west_east_baboons, &baboonID[i]);
    }

    for(int i = 0; i < NUM_BABOONS; i++)
        pthread_join(baboon_thread[i], NULL);

    sem_destroy(&east_wait);
    sem_destroy(&west_wait);
    pthread_mutex_destroy(&mutex);

    return 0;
}
