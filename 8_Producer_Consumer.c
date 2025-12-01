#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int in = 0,out = 0;
sem_t empty;
sem_t full;
sem_t mutex;
void* producer(void* arg)   
{
    int id = *((int *)arg);
    int item = 0;
    while(1)
    {
        item++;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("Producer %d produced %d at position %d\n",id,item,in);
        in = (in+1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&full);
        usleep(150000);
    }
    return NULL;
}
void *consumer(void* arg)
{
    int id = *((int * )arg);
    int item;
    while(1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        printf("Consumer %d consumed %d from position %d\n",id,item,out);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
        usleep(200000);
    }
    return NULL;
}
int main()
{
    pthread_t prod[2],cons[2];
    int p_ids[2] = {1,2};
    int c_ids[2] = {1,2};
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);
    pthread_create(&prod[0],NULL,producer,&p_ids[0]);
    pthread_create(&prod[1],NULL,producer,&p_ids[1]);
    pthread_create(&cons[0],NULL,consumer,&c_ids[0]);
    pthread_create(&cons[1],NULL,consumer,&c_ids[1]);
    while(1) sleep(1);
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}