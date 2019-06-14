#include <mpi.h>
#include <stdio.h>

double f(double x){
	return x*x + 1.0;
}

double Trap(double local_a, double local_b, int local_n, double h){
	double integral, x;
	int i;
	integral = (f(local_a) + f(local_b))*0.5;
	x = local_a;
	for(i=1; i<=local_n-1; i++){
		x += h;
		integral += f(x);
	}
	integral *= h;
	return integral;
}

int main(int argc, char** argv){
	double integral, a=0.0, b=1.0, h, x;
	int n=1000000, i;
	double local_a, local_b, total;
	int local_n, rank, size;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	h = (b-a)/n;
	local_n = n/size;
	local_a = a + rank*local_n*h;
	local_b = local_a + local_n*h;
	integral = Trap(local_a, local_b, local_n, h);
	
	printf("Processo %d: [%.5lf, %.5lf] = %.5lf\n", rank, local_a, local_b, integral);

	if(rank==0){
		total = integral;
		for(i=1; i<size; i++){
			MPI_Recv(&integral, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, &status);
			total += integral;
		}
		printf("Com n=%d trapezios, a estimativa da\n", n);
		printf("integral de %.2f a %.2f e: %.20f\n", a, b, total);
		printf("O valor exato desta integral é 4/3 = %.20f\n", 4.0/3.0);
	} else{
		MPI_Send(&integral, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}