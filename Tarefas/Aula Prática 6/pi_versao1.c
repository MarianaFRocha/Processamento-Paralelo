//Versão 1: Nessa versão você deve paralelizar o código pi.c usando o menor número de caracteres para criar uma versão paralela usando OpenMP.
//Versão 2: Nessa versão você deve otimizar o código de forma a obter bons desempenhos em OpenMP.

#include <stdio.h>
#include <math.h>
#include <omp.h>

int main(){
    long num_steps = 100000;
    long double step;
    long i;
    long double x, pi, sum = 0.0;
    step = 1.0/(double) num_steps;

    #pragma omp parallel for private(i,x) shared(step) reduction(+:sum)	
	    for (i=0;i< num_steps; i++) {
		x = (i+0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	    }
    pi = step * sum;
    printf("Pi = %.20Lg\n", pi);
    //3.141592653589793238462643383279502884197
    return 0;
}
