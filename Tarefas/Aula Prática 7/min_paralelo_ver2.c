#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <mpi.h>

typedef long long ll;
ll numElementos = 100000000;

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

                                                                             
int main(int argc, char *argv[]) {
	srand(0);
    ll i;
    int rank, j;
    int *valor = malloc (numElementos * sizeof (int));
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for(i=0; i<numElementos; i++)
        valor[i] = random();

    int tam = numElementos/(size-1);
    double inicio = MyClock();
    if(rank==0){
    	int valorMin = valor[0];
        for (j = 1; j < size; j++) {
            MPI_Recv(&valorMin, 1, MPI_INT, j, 0, MPI_COMM_WORLD, &status);

       }
    }else{
        MPI_Send(&valorMin, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    
    
	printf("Valor minimo: %d\n", valorMin);
    printf("Tempo gasto: %d microsegundos\n", (int)(MyClock()-inicio));
    //printf("%d, ", (int)(MyClock()-inicio)); //microseconds
    //printf("%.5lf, ", (MyClock()-inicio)/CLOCKS_PER_SEC); //segundos
