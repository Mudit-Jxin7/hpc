#include <iostream>
#include <pthread.h>
#include <vector>

#define ARRAY_SIZE 1000000 // Change the array size as needed
#define NUM_THREADS 4      // Change the number of threads as needed

// Global variables
int array[ARRAY_SIZE];
std::vector<long long> partial_sum(NUM_THREADS); // Stores the partial sum for each thread
int thread_count = NUM_THREADS;                  // Number of threads

// Thread function to compute partial sum
void *PartialSum(void *arg)
{
    long my_rank = (long)arg;
    int elements_per_thread = ARRAY_SIZE / thread_count;
    int start = my_rank * elements_per_thread;
    int end = (my_rank == thread_count - 1) ? ARRAY_SIZE : start + elements_per_thread;
    long long my_sum = 0;

    for (int i = start; i < end; i++)
    {
        my_sum += array[i];
    }

    partial_sum[my_rank] = my_sum;

    return NULL;
}

int main()
{
    pthread_t *thread_handles;
    long thread;

    // Initialize the array
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        array[i] = i + 1;
    }

    // Allocate memory for thread handles
    thread_handles = new pthread_t[thread_count];

    // Create threads
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, PartialSum, (void *)thread);
    }

    // Join threads
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    // Calculate total sum
    long long total_sum = 0;
    for (int i = 0; i < thread_count; i++)
    {
        total_sum += partial_sum[i];
    }

    std::cout << "Total sum: " << total_sum << std::endl;

    // Free memory
    delete[] thread_handles;

    return 0;
}
