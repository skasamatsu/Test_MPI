#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int num_spawn = 1;
  int* err_spawn = (int*)calloc(sizeof(int), num_spawn);
  MPI_Status status;

  int ret=-1;

  MPI_Comm child;
  MPI_Init(&argc, &argv);

  MPI_Comm_spawn("worker", MPI_ARGV_NULL, num_spawn, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &child, err_spawn);

  MPI_Recv(&ret, 1, MPI_INT, 0, 0, child, &status);
  printf("Master received value: %d\n", ret);

  MPI_Finalize();

  free(err_spawn);
  return 0;
}