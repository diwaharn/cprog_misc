#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid; 
    char *msg;

    int n;

    printf ("fork program starting\n");

    pid = fork();

    switch (pid)
    {
        case -1:
            fprintf (stderr, "fork failed");
            exit(1);
        case 0:
            msg = "This is the child"; 
            n = 5;
            break;
        default:
            msg = "This is parent";
            n = 3;
    }

    for (; n > 0; n--) {
        puts (msg);
        sleep (1);
    }

    exit (0);
}
