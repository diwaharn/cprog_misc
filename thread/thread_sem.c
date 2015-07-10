#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


#define MAX_SLEEP_DURATION 10

char message[128] = "Hello world";
sem_t sem;

void *thread1(void *arg)
{
    int i;
    int r; 
    int exit = 0;
    printf ("Running %s\n", __FUNCTION__);

    while (!exit) {
        printf ("Thread 1: "); fflush(stdout);
        scanf("%s", message);
        printf ("\n");

        if (strncmp(message, "end", 3) == 0)
            exit = 1;

        sem_post(&sem);
    }
    
    strcpy (message, "thread1 :Bye !");

    pthread_exit ("Thank you thread1 exit");
    return;

}

void *thread2(void *arg)
{
    int i;
    int r; 
    int exit = 0;
    printf ("Running %s\n", __FUNCTION__);

    while (!exit) {
        sem_wait(&sem);
        printf ("thread2:%s\n", message);

        if (strncmp(message, "end", 3) == 0)
            exit = 1;
    }

    pthread_exit ("Thank you thread2 exit");
    return;
}

int main()
{
    int res;

    pthread_t t1;
    pthread_t t2;

    void *thread_result;

    res = sem_init(&sem, 0, 0);
    if (res != 0){
        perror ("Sem init failed");
        exit (-1);
    }

    res = pthread_create(&t1, NULL, thread1, (void*) message);
    if (res !=0){
        perror("Thread creation failed");
        exit(-1);
    }

    sleep (2);

    res = pthread_create(&t2, NULL, thread2, (void*) message);
    if (res !=0){
        perror("Thread creation failed");
        exit(-1);
    }

    printf ("Waiting for thread to finish\n");

    res = pthread_join(t1, &thread_result);
    if (res != 0){
        perror ("thread1 join failed");
        exit (-1);
    }
    printf ("pthread_join success : %s\n", (char*)thread_result);

    res = pthread_join(t2, &thread_result);
    if (res != 0){
        perror ("thread2 join failed");
        exit (-1);
    }
    printf ("pthread_join success: %s\n", (char*)thread_result);

    exit (1);
}
