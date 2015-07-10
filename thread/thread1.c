#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_SLEEP_DURATION 10

char message[128] = "Hello world";

void *thread1(void *arg)
{
    int i;
    int r; 
    printf ("Running %s\n", __FUNCTION__);

    for (i = 0; i < 5; i++) {
        r = rand()%MAX_SLEEP_DURATION;
        printf ("%s:Iteration %d sleep:%d\n", __FUNCTION__, i, r);
        sleep (r);
    }
    strcpy (message, "thread1 :Bye !");

    pthread_exit ("Thank you thread1 exit");
    return;

}

void *thread2(void *arg)
{
    int i;
    int r; 
    printf ("Running %s\n", __FUNCTION__);

    for (i = 0; i < 3; i++) {
        r = rand()%MAX_SLEEP_DURATION;
        printf ("%s:Iteration %d sleep:%d\n", __FUNCTION__, i, r);
        sleep (r);
    }
    strcpy (message, "thread2 :Bye !");

    pthread_exit ("Thank you thread2 exit");
    return;
}

int main()
{
    int res;

    pthread_t t1;
    pthread_t t2;

    void *thread_result;

    res = pthread_create(&t1, NULL, thread1, (void*) message);
    if (res !=0){
        perror("Thread creation failed");
        exit(-1);
    }

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
