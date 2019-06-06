//gcc -pthread -o  teste  mariana.c -lm



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>



int valorMin;
long long numElementos = 100000000;
int *valor;
int NUM_THREADS;
pthread_mutex_t mutex;

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}


void* min(void *arg) {

    int t = (long)arg;
    long long i; 
    long long ini = t*numElementos/NUM_THREADS;
    long long fim;

    if(t<(NUM_THREADS-1)){
        fim= ini + numElementos/NUM_THREADS;
    }else{
        fim = numElementos;
    }

    //printf("\nThread %d: vetor[%d ... %d]", t, ini, fim-1);

    for (i = ini; i < fim; i++) {
        
        if(valor[i] < valorMin){
        	pthread_mutex_lock(&mutex);
        	if(valor[i] < valorMin)
            	valorMin = valor[i];
            pthread_mutex_unlock(&mutex);	
        }
        
    }
    //printf("menor: %d\n", valorMin);

}
    

                                                                             
int main(int argc, char *argv[]) {
	int i;
    srand(0);
    
    if (argc != 2) {
      fprintf(stderr, "usage: ./a.out <threads>\n");
      exit(1);
    }

    valor = malloc (numElementos * sizeof (int));

    //printf("\nvetor: ");
    for(i=0; i<numElementos; i++){
        valor[i] = random();
        //printf("%d ", valor[i]);
    }

    valorMin = valor[0];

    NUM_THREADS = atoi(argv[1]);
   
    pthread_t *threads = (pthread_t *)malloc(NUM_THREADS*sizeof(pthread_t));

    pthread_mutex_init(&mutex, NULL);
	double inicio = MyClock();

    int rc;
    for (i = 0; i < NUM_THREADS; i++) {
        rc = pthread_create(&threads[i], NULL, min, (void *)i);
        if (rc) {
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(1);
        }
    }
    
    for (i = 0; i < NUM_THREADS; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc) {
            printf("ERROR: return code from pthread_join() is %d\n", rc);
            exit(1);
        }
    }

   // printf(" %d ", valorMin); //resultado
    printf(" %.5lf,", (MyClock()-inicio)/CLOCKS_PER_SEC);

    pthread_exit(NULL);

    return 0;
}



