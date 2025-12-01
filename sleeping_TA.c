#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define NUM_CHAIRS 5
#define NUM_STUDENTS 10
#define HELP_TIME 3

sem_t ta_sem;
sem_t student_sem;
pthread_mutex_t mutex;
int waiting_students = 0;

void* TA(void* arg)
{
    while (1)
    {
        sem_wait(&ta_sem);

        pthread_mutex_lock(&mutex);
        waiting_students--;
        printf("TA: Calls a student. Waiting Students: %d\n", waiting_students);
        pthread_mutex_unlock(&mutex);

        sem_post(&student_sem);

        printf("TA is helping a student...\n");
        sleep(HELP_TIME);
        printf("TA finished helping the student.\n");
    }
    return NULL;
}

void* student(void* arg)
{
    int id = *((int*)arg);

    while (1)
    {
        sleep(rand() % 5 + 1);

        pthread_mutex_lock(&mutex);

        if (waiting_students < NUM_CHAIRS)
        {
            waiting_students++;
            printf("Student %d is waiting. Waiting Now: %d\n", id, waiting_students);
            pthread_mutex_unlock(&mutex);

            sem_post(&ta_sem);
            sem_wait(&student_sem);

            printf("Student %d is getting help.\n", id);
        }
        else
        {
            pthread_mutex_unlock(&mutex);
            printf("Student %d found no seats. Leaves...\n", id);
        }
    }

    return NULL;
}

int main()
{
    srand(time(NULL));

    pthread_t TA_thread;
    pthread_t student_thread[NUM_STUDENTS];

    sem_init(&ta_sem, 0, 0);
    sem_init(&student_sem, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    int studentID[NUM_STUDENTS];

    pthread_create(&TA_thread, NULL, TA, NULL);

    int i = 0;
    while (i < NUM_STUDENTS)
    {
        studentID[i] = i + 1;  // Assign IDs
        pthread_create(&student_thread[i], NULL, student, &studentID[i]);
        i++;
    }

    pthread_join(TA_thread, NULL);

    i = 0; // reset i before joining
    while (i < NUM_STUDENTS)
    {
        pthread_join(student_thread[i], NULL);
        i++;
    }

    sem_destroy(&ta_sem);
    sem_destroy(&student_sem);
    pthread_mutex_destroy(&mutex);

    return 0;
}
