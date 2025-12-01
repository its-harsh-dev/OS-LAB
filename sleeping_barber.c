#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define HAIRCUT_TIME 3
#define CHAIRS 5
#define MAX_CUSTOMERS 20

sem_t waiting_customers;
sem_t barberReady;
pthread_mutex_t mutex;
int waiting = 0;

void* barber(void* arg)
{
    while (1)
    {
        sem_wait(&waiting_customers);  // wait for a customer

        pthread_mutex_lock(&mutex);
        waiting--;
        printf("Barber calls a customer. Waiting now = %d\n", waiting);
        pthread_mutex_unlock(&mutex);

        sem_post(&barberReady);       // signal customer

        printf("Barber cutting hair...\n");
        sleep(HAIRCUT_TIME);
        printf("Barber has finished cutting hair.\n");
    }
    return NULL;
}

void* customer(void* arg)
{
    int id = *((int*)arg);

    pthread_mutex_lock(&mutex);
    if (waiting < CHAIRS)
    {
        waiting++;
        printf("Customer %d is waiting. Waiting = %d\n", id, waiting);
        pthread_mutex_unlock(&mutex);

        sem_post(&waiting_customers);  // notify barber
        sem_wait(&barberReady);        // wait for barber

        printf("Customer %d is getting a haircut.\n", id);
    }
    else
    {
        pthread_mutex_unlock(&mutex);
        printf("Customer %d leaves (no empty chairs).\n", id);
    }

    return NULL;
}

int main()
{
    sem_init(&barberReady, 0, 0);
    sem_init(&waiting_customers, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t barber_id;
    pthread_create(&barber_id, NULL, barber, NULL);

    for (int i = 1; i <= MAX_CUSTOMERS; i++)
    {
        sleep(rand() % 2);

        pthread_t cid;
        int* id = malloc(sizeof(int));
        *id = i;

        pthread_create(&cid, NULL, customer, id);
        pthread_detach(cid);
    }

    // keep the program running
    pthread_join(barber_id, NULL);

    sem_destroy(&waiting_customers);
    sem_destroy(&barberReady);
    pthread_mutex_destroy(&mutex);
    return 0;
}
