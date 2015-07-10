#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_SLEEP_DURATION 10

char message[128] = "Hello world";
sem_t sem;
pthread_mutex_t m;

void *thread1(void *arg)
{
    int i;
    int r; 
    int exit = 0;
    printf ("Running %s\n", __FUNCTION__);

    while (!exit) {
        pthread_mutex_lock(&m);
        printf ("Thread 1: "); fflush(stdout);
        scanf("%s\n", message);
        printf ("\n");

        if (strncmp(message, "end", 3) == 0)
            exit = 1;

        pthread_mutex_unlock(&m);
        sleep (1);
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
        pthread_mutex_lock(&m);
        printf ("thread2:%s\n", message);

        if (strncmp(message, "end", 3) == 0)
            exit = 1;
        pthread_mutex_unlock(&m);
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

    res = pthread_mutex_init(&m, NULL);
    if (res != 0){
        perror ("Mutex init failed");
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
