#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
#define ARRAY_SIZE 100

int main()
{
    int i, tid;
    int array[ARRAY_SIZE];

    // Initialize the array
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = i;
    }

// Parallel region starts here
#pragma omp parallel private(i, tid)
    {
        tid = omp_get_thread_num(); // Get the thread ID

// Work sharing loop
#pragma omp for
        for (i = 0; i < ARRAY_SIZE; i++)
        {
            printf("Thread %d is processing element %d\n", tid, i);
            // Do some work with array[i]
            array[i] *= 2; // For example, double the value
        }
    } // Parallel region ends here

    // Print out the modified array
    printf("Modified array:\n");
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}

// g++ -o loop_work_sharing -fopenmp loop_work_sharing.c
