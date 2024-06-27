
/*
 * For POSIX threads, see https://computing.llnl.gov/tutorials/pthreads/
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#define UNUSED(x) (void)(x)  // silence warnings for unused arguments

#define NUM_THREADS 100

// start code from exercise sheet

const int n = 5000;
int total_count;

void total(void)
{
    for (int count = 0; count < n; ++count)
        if (count % 2)
            --total_count;
        else
            ++total_count;
}

// end code of exercise sheet

void * total2(void * arg)
{
    UNUSED(arg);

    for (int count = 0; count < n; ++count)
        if (count % 2)
            --total_count;
        else
            ++total_count;
    
    pthread_exit(NULL);
}

sem_t total_count_s;

void * total3(void * arg)
{
    UNUSED(arg);

    for (int count = 0; count < n; ++count)
        if (count % 2)
        {
            if( sem_wait(&total_count_s) ) { printf("semaphore wait failed."); abort(); };
        }
        else
        {
            if( sem_post(&total_count_s) ) { printf("semaphore post failed."); abort(); };
        }
    
    pthread_exit(NULL);
}

int main(void)
{
    // single thread
    printf("Computing total with a single thread:\n");
    total_count = 0;
    total();
    printf("%d\n\n", total_count);

    // multiple threads    
    printf("Computing total with %d threads in parallel:\n", NUM_THREADS);
    total_count = 0;
    pthread_t threads[NUM_THREADS];
    for (long i = 0; i < NUM_THREADS; ++i)
    {
        int rc = pthread_create(&threads[i], NULL, total2, (void *)i);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            abort();
        }
    }
    for (long i = 0; i < NUM_THREADS; ++i) pthread_join(threads[i], NULL);  // wait for threads to finish
    printf("%d\n\n", total_count);

    // multiple threads with semaphore
    if( sem_init(&total_count_s, 0, 0) ) { printf("semaphore creation failed."); abort(); }
    printf("Computing total with %d threads in parallel, with semaphore:\n", NUM_THREADS);
    for (long i = 0; i < NUM_THREADS; ++i)
    {
        int rc = pthread_create(&threads[i], NULL, total3, (void *)i);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            abort();
        }
    }
    for (long i = 0; i < NUM_THREADS; ++i) pthread_join(threads[i], NULL);  // wait for threads to finish
    // retrieving the value of the semaphore is not supported by macOS
    if ( sem_getvalue(&total_count_s, &total_count) ) { printf("semaphore getvalue failed."); abort(); }
    printf("%d\n\n", total_count);
    if( sem_destroy(&total_count_s) ) { printf("semaphore destruction failed."); abort(); };

    pthread_exit(NULL);
}
