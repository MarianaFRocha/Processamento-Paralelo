//gcc -pthread -o pthread  pthread.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>



#define MAX  50000000
#define FUNCAO(I) ceil((sqrt(I)*sqrt(I)+pow(I, 100)-log(I)+log(I)))
//round((sqrt(I)*sqrt(I)+pow(I, 100)-log(I)+log(I)))

int NUM_THREADS;
double vetor[MAX];

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}


void *mythread(void *arg) {
    
    int t = (long)arg;
    int i; 
    int ini = t*MAX/NUM_THREADS;
    int fim = t*MAX/NUM_THREADS + MAX/NUM_THREADS; //(t+1)*MAX/NUM_THREADS
    printf("Thread %d: vetor[%d ... %d]\n", t, ini, fim-1);
    for (i = ini; i < fim; i++) {
      vetor[i] = FUNCAO(i);
    }
    printf("Thread %d: terminou\n", t);
}

                                                                             
int main(int argc, char *argv[]) {
    double inicio = MyClock();
    if (argc != 2) {
      fprintf(stderr, "usage: ./a.out <threads>\n");
      exit(1);
    }

    NUM_THREADS = atoi(argv[1]);
   
    pthread_t *threads = (pthread_t *)malloc(NUM_THREADS*sizeof(pthread_t));

    int i;
    int rc;
    for (i = 0; i < NUM_THREADS; i++) {
        rc = pthread_create(&threads[i], NULL, mythread, (void *)i);
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

    printf("Tempo gasto: %.5lf\n", (MyClock()-inicio)/CLOCKS_PER_SEC);

    
    
    pthread_exit(NULL);

    return 0;
}
