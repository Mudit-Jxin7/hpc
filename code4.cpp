#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char **argv)
{
    // start the MPI code
    MPI_Init(NULL, NULL);
    int num_procs;
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        // read the array
        int n;
        printf("Enter number of elements : ");
        scanf("%d", &n);
        int arr[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 10 + 1;
        }
        printf("Array is -\n [ ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("]\n");
        int elem_to_send = n / num_procs;
        int tag = 0;
        for (int i = 1; i < num_procs; i++)
        { // send the size
            if (i != num_procs - 1)
            {
                elem_to_send = n / num_procs;
                MPI_Send(&elem_to_send, 1, MPI_INT, i, i + num_procs, MPI_COMM_WORLD);
                MPI_Send(&arr[i * (elem_to_send)], elem_to_send, MPI_INT, i, i + num_procs + 1,
                         MPI_COMM_WORLD);
                continue;
            }
            // elements would be changed
            elem_to_send = n / num_procs + n % num_procs;
            MPI_Send(&elem_to_send, 1, MPI_INT, i, i + num_procs, MPI_COMM_WORLD);
            MPI_Send(&arr[(num_procs - 1) * (n / num_procs)], elem_to_send, MPI_INT, i, i + num_procs + 1,
                     MPI_COMM_WORLD);
            // send the array
        }
        int ans = 0;
        for (int i = 0; i < n / num_procs; i++)
            ans += arr[i];
        // recv the data into the local var s_rec
        int s_rec;
        for (int i = 1; i < num_procs; i++)
        {
            s_rec = 0;
            MPI_Recv(&s_rec, 1, MPI_INT, i, i + num_procs + 2, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            ans += s_rec;
        }
        printf("Total sum of array is %d\n", ans);
    }
    else
    {
        // receive the size of elements
        int size;
        MPI_Recv(&size, 1, MPI_INT, 0, rank + num_procs, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        int arr[size];
        MPI_Recv(arr, size, MPI_INT, 0, rank + num_procs + 1, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);
        int local = 0;
        for (int i = 0; i < size; i++)
            local = local + arr[i];
        printf("\nProcess %d sending sum %d back to main...\n", rank, local);
        MPI_Send(&local, 1, MPI_INT, 0, rank + num_procs + 2, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}

// mpic++ -o code4 code4.cpp -lmpi