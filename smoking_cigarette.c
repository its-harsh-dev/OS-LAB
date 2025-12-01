#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t agentsem;
sem_t tobbaccosem;
sem_t papersem;
sem_t matchsem;

void* agent(void* arg)
{
    while(1)
    {
        sem_wait(&agentsem);
        int choice = rand() % 3;

        switch(choice)
        {
            case 0:
                printf("Agent puts PAPER and MATCHES on the table\n");
                sem_post(&tobbaccosem);   // Smoker with tobacco
                break;

            case 1:
                printf("Agent puts TOBACCO and MATCHES on the table\n");
                sem_post(&papersem);      // Smoker with paper
                break;

            case 2:
                printf("Agent puts TOBACCO and PAPER on the table\n");
                sem_post(&matchsem);      // Smoker with matches
                break;
        }

        sleep(1);
    }
    return NULL;
}

void* smokerTobacco(void* arg)
{
    while(1)
    {
        sem_wait(&tobbaccosem);
        printf("Smoker WITH TOBACCO picks up the items\n");
        printf("Smoker WITH TOBACCO makes a cigarette\n");
        sleep(1);
        printf("Smoker WITH TOBACCO is smoking...\n\n");
        sleep(2);
        sem_post(&agentsem);
    }
    return NULL;
}

void* smokerPaper(void* arg)
{
    while(1)
    {
        sem_wait(&papersem);
        printf("Smoker WITH PAPER picks up the items\n");
        printf("Smoker WITH PAPER makes a cigarette\n");
        sleep(1);
        printf("Smoker WITH PAPER is smoking...\n\n");
        sleep(2);
        sem_post(&agentsem);
    }
    return NULL;
}

void* smokerMatches(void* arg)
{
    while(1)
    {
        sem_wait(&matchsem);
        printf("Smoker WITH MATCHES picks up the items\n");
        printf("Smoker WITH MATCHES makes a cigarette\n");
        sleep(1);
        printf("Smoker WITH MATCHES is smoking...\n\n");
        sleep(2);
        sem_post(&agentsem);
    }
    return NULL;
}

int main()
{
    srand(time(NULL));

    sem_init(&agentsem, 0, 1);
    sem_init(&tobbaccosem, 0, 0);
    sem_init(&papersem, 0, 0);
    sem_init(&matchsem, 0, 0);

    pthread_t agentThread, t1, t2, t3;

    pthread_create(&agentThread, NULL, agent, NULL);
    pthread_create(&t1, NULL, smokerTobacco, NULL);
    pthread_create(&t2, NULL, smokerPaper, NULL);
    pthread_create(&t3, NULL, smokerMatches, NULL);

    pthread_join(agentThread, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&agentsem);
    sem_destroy(&tobbaccosem);
    sem_destroy(&papersem);
    sem_destroy(&matchsem);

    return 0;
}
