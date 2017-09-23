#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main()
{
	int rank, size;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	printf("Rank %d from %d\n", rank, size);
	system("hostname");

	MPI_Finalize();
	return 0;
}
