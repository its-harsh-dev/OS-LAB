#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_CARS 20

sem_t bridge;
pthread_mutex_t mutex;

int north_on_bridge = 0;
int south_on_bridge = 0;

void* north_car(void* arg)
{
    int id = *((int*)arg);

    while (1)
    {
        sleep(rand() % 4 + 1);

        pthread_mutex_lock(&mutex);

        if (south_on_bridge == 0)
        {
            if (north_on_bridge == 0)
                sem_wait(&bridge);

            north_on_bridge++;
            printf("North car %d entering. North count = %d\n", id, north_on_bridge);
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            continue;
        }

        sleep(1); // crossing

        pthread_mutex_lock(&mutex);
        north_on_bridge--;
        printf("North car %d exiting. North left = %d\n", id, north_on_bridge);

        if (north_on_bridge == 0)
            sem_post(&bridge);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* south_car(void* arg)
{
    int id = *((int*)arg);

    while (1)
    {
        sleep(rand() % 4 + 1);

        pthread_mutex_lock(&mutex);

        if (north_on_bridge == 0)
        {
            if (south_on_bridge == 0)
                sem_wait(&bridge);

            south_on_bridge++;
            printf("South car %d entering. South count = %d\n", id, south_on_bridge);
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            continue;
        }

        sleep(1); // crossing

        pthread_mutex_lock(&mutex);
        south_on_bridge--;
        printf("South car %d exiting. South left = %d\n", id, south_on_bridge);

        if (south_on_bridge == 0)
            sem_post(&bridge);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main()
{
    srand(time(NULL));

    pthread_t cars[NUM_CARS];
    int carsID[NUM_CARS];

    sem_init(&bridge, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    int i = 0;
    while (i < NUM_CARS)
    {
        carsID[i] = i + 1;
        if (rand() % 2 == 0)
            pthread_create(&cars[i], NULL, north_car, &carsID[i]);
        else
            pthread_create(&cars[i], NULL, south_car, &carsID[i]);
        i++;
    }

    i = 0;
    while (i < NUM_CARS)
    {
        pthread_join(cars[i], NULL);
        i++;
    }

    sem_destroy(&bridge);
    pthread_mutex_destroy(&mutex);

    return 0;
}
