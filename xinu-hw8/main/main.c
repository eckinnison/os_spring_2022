/**
 * COSC 3250 - PThreads Summation Demo
 * This program uses multiple threads to parallelize (badly) the
 *  summation of an array of integers.
 * This program should compile and run on Linux.
 * To run this demonstration on Embedded Xinu, replace the #include
 *  lines with #include<xinu.h>, and change any printf() calls to kprintf().
 * @author Dennis Brylow
 */

#include <xinu.h>

#define MAX 10000
#define THRD_COUNT 4

/* This struct lets us pass three items to each thread */
typedef struct
{
    int *array;
    int length;
    long int *answer;
    pthread_mutex_t *lock;
} myarg_t;


/* Each thread will sum up its part of the array */
void *mythread(void *arg)
{
    /* Cast the generic args to be our myarg_t struct */
    myarg_t *args = (myarg_t *) arg;

    int i = 0, local = 0;

    //printf("Adding %d to %d\n", args->array[0], args->array[args->length - 1]);
    for (i = 0; i < args->length; i++)
    {
        pthread_mutex_lock(args->lock);
        *(args->answer) += args->array[i];
	// If you really want to see a race condition, comment out the line
	// above this comment, and replace it with this equivalent segment
	// that widens the window for a data race:
	//        local = *(args->answer);
	//        resched();
	//        local += args->array[i];
	//        *(args->answer) = local;
        pthread_mutex_unlock(args->lock);
    }
    return NULL;
}

int main()
{
    int *array = NULL;          /* Array of numbers to add up        */
    long int answer = 0;        /* Answers from each thread          */
    pthread_t threads[THRD_COUNT];      /* PThread objects                   */
    myarg_t args[THRD_COUNT];   /* Argument struct, one per thread   */
    int i = 0, rc = 0;
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    array = (int *)malloc(MAX * sizeof(int));
    if (NULL == array)
        return -1;

    /* Initialize data from 1 to MAX  */
    for (i = 0; i < MAX; i++)
    {
        array[i] = i + 1;
    }

    /* Initialize Per-thread argument structs */
    for (i = 0; i < THRD_COUNT; i++)
    {
        /* Each thread gets its own portion of the array */
        args[i].array = array + i * (MAX / THRD_COUNT);
        args[i].length = MAX / THRD_COUNT;
        /* Each thread gets its own answer spot */
        args[i].answer = &answer;
        args[i].lock = &lock;
    }

    /* Create all of the worker threads */
    for (i = 0; i < THRD_COUNT; i++)
    {
        rc = pthread_create(threads + i, NULL, mythread, args + i);
        // printf("Spawned thread %d, rc = %d\n", i, rc);
    }

    /* Use join() to wait for each thread to complete its work */
    for (i = 0; i < THRD_COUNT; i++)
    {
        pthread_join(threads[i], NULL);
    }

    kprintf("Final answer is %d\r\n", answer);

    return 0;
}
