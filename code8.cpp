#include <stdio.h>
#include <omp.h>

int main()
{
    int tid;

// Parallel region starts here
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num(); // Get the thread ID

// Sections work sharing
#pragma omp sections
        {
// First section
#pragma omp section
            {
                printf("Thread %d is executing section 1\n", tid);
                // Perform tasks for section 1
            }

// Second section
#pragma omp section
            {
                printf("Thread %d is executing section 2\n", tid);
                // Perform tasks for section 2
            }

// Third section
#pragma omp section
            {
                printf("Thread %d is executing section 3\n", tid);
                // Perform tasks for section 3
            }
        } // End of sections
    }     // Parallel region ends here

    return 0;
}
