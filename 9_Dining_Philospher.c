#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define N 5
pthread_mutex_t chopstick[N];
void* philospher(void* num)
{
    int id = *((int *)arg);
    while(1)
    {
        //thinking
        printf("Philospher%d is thinking\n",id+1);
        sleep(1);
        //hungry
        printf("Philospher%d is hungry\n",id+1);
        //pick up the left chopstick
        pthread_mutex_lock(&chopstick[id]);
        //pick up the right chopstick
        pthread_mutex_lock(&chopstick[(id+1)%N]);
        //eating
        printf("Philospher %d is eating\n",id+1);
        sleep(2);
        //put down right chopstick
        pthread_mutex_unlock(&chopstick[(id+1)%N]);
        //put down left chopstick
        pthread_mutex_unlock(&chopstick[id]);
        printf("Philospher %d finished eating and starts thinking again\n",id+1);
        sleep(1);
    }
}
int main()
{
    pthread_t thread_id[N];
    int philospher_num[N];
    //Initialize mutexes
    for(int i = 0;i < N;i++)
        pthread_mutex_init(&chopstick[i],NULL);
    for(int i = 0;i < N;i++)
    {
        philospher_num[i] = i;
        pthread_create(&thread_id[i],NULL,philospher,&philospher_num[i]);
    }
    for(int i = 0;i < N;i++)
        pthread_join(thread_id[i],NULL);
    for(int i = 0;i < N;i++)
        pthread_mutex_destroy(&chopstick[i]);
    return 0;
}