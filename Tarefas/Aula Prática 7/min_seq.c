#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

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
    int *valor = malloc (numElementos * sizeof (int));

    for(i=0; i<numElementos; i++)
        valor[i] = random();

    double inicio = MyClock();
	int valorMin = valor[0];
    for (i = 1; i < numElementos; i++) {
        if(valor[i] < valorMin)
            valorMin = valor[i];
    }
    
    
	// printf("Valor minimo: %d\n", valorMin);
    // printf("Tempo gasto: %d microsegundos\n", (int)(MyClock()-inicio));
    //printf("%d, ", (int)(MyClock()-inicio)); //microseconds
    printf("%.5lf, ", (MyClock()-inicio)/CLOCKS_PER_SEC); //segundos

	return 0;
}
