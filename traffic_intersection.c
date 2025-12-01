#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define GREEN_TIME 3
#define NUM_CARS 10

sem_t ns_green;
sem_t ew_green;
pthread_mutex_t mutex;

void* traffic_light(void* arg)
{
    while (1)
    {
        printf("Traffic Light : North-South GREEN | East-West RED\n");
        sem_post(&ns_green);   // NS car(s) allowed
        sleep(GREEN_TIME);
        sem_trywait(&ns_green);  // Turn NS red safely

        printf("Traffic Light : East-West GREEN | North-South RED\n");
        sem_post(&ew_green);   // EW car(s) allowed
        sleep(GREEN_TIME);
        sem_trywait(&ew_green);  // Turn EW red safely
    }
    return NULL;
}

void* car(void* arg)
{
    int id = *((int*)arg);
    int direction = rand() % 4;

    while (1)
    {
        sleep(rand() % 4 + 1);

        pthread_mutex_lock(&mutex);
        switch (direction)
        {
            case 0: printf("Car %d from NORTH arrived at the red light\n", id); break;
            case 1: printf("Car %d from SOUTH arrived at the red light\n", id); break;
            case 2: printf("Car %d from EAST arrived at the red light\n", id); break;
            case 3: printf("Car %d from WEST arrived at the red light\n", id); break;
        }
        pthread_mutex_unlock(&mutex);

        if (direction == 0 || direction == 1)
        {
            sem_wait(&ns_green);
            sem_post(&ns_green);
        }
        else
        {
            sem_wait(&ew_green);
            sem_post(&ew_green);
        }

        pthread_mutex_lock(&mutex);
        printf("Car %d is passing from ", id);
        if (direction == 0) printf("NORTH → SOUTH\n");
        if (direction == 1) printf("SOUTH → NORTH\n");
        if (direction == 2) printf("EAST → WEST\n");
        if (direction == 3) printf("WEST → EAST\n");
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

int main()
{
    srand(time(NULL));

    pthread_t light_thread;
    pthread_t car_threads[NUM_CARS];
    int carID[NUM_CARS];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&ns_green, 0, 0);
    sem_init(&ew_green, 0, 0);

    pthread_create(&light_thread, NULL, traffic_light, NULL);

    int i = 0;
    while (i < NUM_CARS)
    {
        carID[i] = i + 1;
        pthread_create(&car_threads[i], NULL, car, &carID[i]);
        i++;
    }

    pthread_join(light_thread, NULL);

    i = 0;
    while (i < NUM_CARS)
    {
        pthread_join(car_threads[i], NULL);
        i++;
    }

    sem_destroy(&ns_green);
    sem_destroy(&ew_green);
    pthread_mutex_destroy(&mutex);

    return 0;
}
