#include <iostream>
#include <pthread.h>

#define ARRAY_SIZE 10

// Global variables
int array[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
long long partial_sum[2]; // Stores the partial sum for each thread
int thread_count = 2;     // Number of threads

// Thread function to compute partial sum
void *PartialSum(void *rank)
{
    long my_rank = (long)rank;
    int elements_per_thread = ARRAY_SIZE / thread_count;
    int start = my_rank * elements_per_thread;
    int end = start + elements_per_thread;
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
