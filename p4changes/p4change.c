#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Change 207829 on 2015/07/07 by sclawson@7.3.4.R01-sclawson-utah ' PRF 207436 Comments:    Transi'
*/

int debug = 1;

typedef struct {
    int change;
    int year;
    int month;
    int day;
    char by[64];
    char ver[16];
    char view[64];
    int pr;
}ChangesRecord;

typedef struct node {
    struct node *next;
    ChangesRecord rec;
} Node;

typedef struct queue {
    Node *head;
    Node *tail;
    int count;
}Queue;

char rec[128];

Queue q732;
Queue q733;
Queue q7xx;
Queue q734r02;
Queue q734r01;
Queue q811;
Queue qDefault;

int insert_queue(Queue *q, ChangesRecord *rec)
{
    Node *n;
    ChangesRecord *r;

    if (q == NULL || rec == NULL) {
        return 0;
    }

    n = (Node*) malloc(sizeof(Node));
    if (n == NULL){
        fprintf(stderr, "Insert Failed  - malloc \n");
        return 0;
    }

    r = (ChangesRecord*) malloc(sizeof(ChangesRecord));
    if (r == NULL) {
        fprintf(stderr, "Insert Failed  - malloc rec \n");
        return 0;
    }

    n->next = NULL;
    memcpy (&n->rec, rec, sizeof(ChangesRecord));
    if (q->head == NULL) {
        q->head = n;
        q->tail = n;
    }
    else {
        q->tail->next = n;
        q->tail = n;
    }
    q->count++;
}

void queue_print(Queue *q)
{
    Node *n;
    n = q->head;
    printf ("Queue Values : ");
    while (n) {
            printf ("Proceed: %d:%d/%d/%d:by %s: view (%s): ver %s:%d\n", 
                    n->rec.change, 
                    n->rec.year, n->rec.month, n->rec.day, 
                    n->rec.by, 
                    n->rec.view, 
                    n->rec.ver, 
                    n->rec.pr);
            n = n->next;
    }
}

int queue_find_pr(Queue *q, int pr)
{
    Node *n;
    n = q->head;
    while (n) {
        if (n->rec.pr == pr){
            return 1;
        }
            n = n->next;
    }
    return 0;
}

/* read record */
int ReadRecord()
{
    FILE *fp;
    int ret = 0;
    char str[64];
    char buf[256];
    ChangesRecord rec;
    Queue *q = &qDefault;

    fp = fopen ("p4.changes", "r");
    if (fp == NULL) {
        fprintf(stderr, "File not found\n");
        return -1;
    }

    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (debug) {
            printf ("Processing: %s", buf);
        }
            //ret = sscanf (rec, "Change %d on %d/%d/%d by %[^@]s@%s ' PRF %d Comments: %*s",
            ret = sscanf (buf, "Change %d on %d/%d/%d by %s %*c PRF %d Comments: %*s",
                    &rec.change, 
                    &rec.year, 
                    &rec.month, 
                    &rec.day, 
                    str,
                    &rec.pr
                    );
                sscanf(str, "%[^@]s", rec.by);
                sscanf(str+strlen(rec.by)+1, "%s", rec.view);
                sscanf(rec.view, "%[^-]s", rec.ver);

        if (strcmp("7.3.2.R01", rec.ver) == 0)
        {
            if (debug) {
                printf ("Queue 732 : %d:%d/%d/%d:by %s: view (%s): ver %s:%d\n", 
                        rec.change, 
                        rec.year, rec.month, rec.day, 
                        rec.by, 
                        rec.view, 
                        rec.ver, 
                        rec.pr);
            }
            q = &q732;
        }
        else if (strcmp("7.3.3.R01", rec.ver) == 0){
            q = &q733;
        }
        else if (strcmp("7.X.X.R01", rec.ver) == 0){
            q = &q7xx;
        }
        else if (strcmp("7.3.4.R01", rec.ver) == 0){
            q = &q734r01;
        }
        else if (strcmp("7.3.4.R02", rec.ver) == 0){
            q = &q734r02;
        }
        else if (strcmp("8.1.1.R01", rec.ver) == 0){
            q = &q811;
        }
        insert_queue (q, &rec);
        if (rec.year == 2015 && rec.month < 5)
            break;
    }

    if (debug) queue_print (&q732);

    fclose(fp);
}

int CheckRelease(Queue *q)
{
    Node *n;
    printf ("PR     : 732R01 : 733R01 : 734R01 : 734R02 : 811R01\n");

    n = q->head;
    while (n){
        printf ("%06d : %6d : %6d : %6d : %6d : %6d \n",
                n->rec.pr, 
                queue_find_pr(&q732, n->rec.pr),
                queue_find_pr(&q733, n->rec.pr),
                queue_find_pr(&q734r01, n->rec.pr),
                queue_find_pr(&q734r02, n->rec.pr),
                queue_find_pr(&q811, n->rec.pr));
        n = n->next;
    }
}

int main()
{
    if (ReadRecord() < 0){
        return -1;
    }

    //CheckRelease(&q732);
    queue_print (&q732);
    queue_print (&q733);
    return 1;
} 

