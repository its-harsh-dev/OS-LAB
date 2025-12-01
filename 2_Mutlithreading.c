#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
void* thread1(void* arg)
{
    int num = *((int *)arg);
    for(int i = 0;i <= num;i+=2)
    {
        printf("Even Number : %d\n",i);
    }
}
void* thread2(void* arg)
{
    int num = *((int*)arg);
    for(int i = 1;i <= num;i+=2)
    {
        printf("Odd Number:  %d\n",i);
    }
}
int main()
{
    int number;
    printf("Enter number : ");
    scanf("%d",&number);
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,thread1,&number);
    pthread_create(&tid2,NULL,thread2,&number);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}