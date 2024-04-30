#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 100
#define NUM_THREADS 4

int main() {
    int array[ARRAY_SIZE];

    // Initialize array elements
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1; // Values from 1 to ARRAY_SIZE
    }

    // Parallel region starts here
    #pragma omp parallel num_threads(NUM_THREADS)
    {
        int tid = omp_get_thread_num();
        int local_sum = 0;

        // Each thread calculates its local sum
        #pragma omp for
        for (int i = 0; i < ARRAY_SIZE; i++) {
            local_sum += array[i];
        }

        // Each thread prints its local sum
        printf("Thread %d calculated the sum: %d\n", tid, local_sum);
    } // Parallel region ends here

    return 0;
}
