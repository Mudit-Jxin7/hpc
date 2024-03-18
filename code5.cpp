#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Hello world from process %s, rank %d out of %d processes\n\n", processor_name,
           world_rank, world_size);

    if (world_size > 1)
    {
        if (world_rank == 0)
        {
            char *message = "Hello!";
            MPI_Send(message, 6, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        }
        else if (world_rank == 1)
        {
            char message[6];
            MPI_Recv(message, 6, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Message received!\n");
            printf("Message is : %s\n", message);
        }
    }
    else
    {
        printf("This program requires at least 2 processes to run.\n");
    }

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}

// mpiexec -n 2 ./code5