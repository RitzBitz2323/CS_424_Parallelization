#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10 // Assuming a 10x10 grid for simplicity

// Function to initialize a portion of the grid with living cells
void initializeGrid(int* subgrid, int localRows, int localColumns, int rank) {
    for (int i = 0; i < localRows; i++) {
        for (int j = 0; j < localColumns; j++) {
            subgrid[i * localColumns + j] = (i + j + rank) % 2; // Modify this according to your logic
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Calculate the number of rows each process will handle
    int rowsPerProcess = N / size;
    int remainingRows = N % size;

    // Calculate the number of rows for the current process
    int localRows = (rank < remainingRows) ? rowsPerProcess + 1 : rowsPerProcess;
    int localColumns = N;

    // Allocate memory for the sub-grid
    int* subgrid = (int*)malloc(localRows * localColumns * sizeof(int));

    // Initialize the sub-grid
    initializeGrid(subgrid, localRows, localColumns, rank);

    // Print the initial sub-grid for each process
    printf("Rank %d initial sub-grid:\n", rank);
    for (int i = 0; i < localRows; i++) {
        for (int j = 0; j < localColumns; j++) {
            printf("%d ", subgrid[i * localColumns + j]);
        }
        printf("\n");
    }
    printf("\n");

    // Clean up
    free(subgrid);
    MPI_Finalize();

    return 0;
}
