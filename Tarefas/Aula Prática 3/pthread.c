
//gcc -pthread -o pthread  pthread.c -lm
//./pthread <NUM_THREADS> MATRIZ_A.txt MATRIZ_B.txt

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>


//#define MAX  50000000
//#define FUNCAO(I) ceil((sqrt(I)*sqrt(I)+pow(I, 100)-log(I)+log(I)))
//round((sqrt(I)*sqrt(I)+pow(I, 100)-log(I)+log(I)))

int NUM_THREADS, TAM_MATRIZ;
int **matA, **matB, **matC;

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

void imprimiMatriz(int **mat){

  printf("Matriz:\n");
    for(int i=0; i<TAM_MATRIZ; i++){
        for(int j=0; j<TAM_MATRIZ; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }

    return ;
}

void *mythread(void *arg) {

    int t = (long)arg;
    int i, j, k, soma, fim; 
    int ini = t*(TAM_MATRIZ/NUM_THREADS);

    if(t<(NUM_THREADS-1)){
        fim = (t+1)*(TAM_MATRIZ/NUM_THREADS);
    }
    else{
        fim = TAM_MATRIZ;
    }

   // printf("Thread %d: vetor[%d ... %d]\n", t, ini, fim-1);

    for (i = ini; i < fim; i++) {
        for(j=0; j<TAM_MATRIZ; j++)
        {
            soma=0;
            for(k=0; k<TAM_MATRIZ; k++)
            {
                    soma = soma+matA[i][k]*matB[k][j];

            }
            matC[i][j]=soma;

        }   
    }

    //imprimiMatriz(matC);

  //  printf("Thread %d: terminou\n", t);
}

                                                                             
int main(int argc, char *argv[]) {

    double inicio = MyClock();

    int tmp, i, j, nB;

    if (argc != 4) {
      fprintf(stderr, "usage: ./a.out <NUM_THREADS> MATRIZ_A.txt MATRIZ_B.txt\n");
      exit(1);
    }

    NUM_THREADS = atoi(argv[1]);

   // printf("\nNUM_THREADS: %d\n", NUM_THREADS);
   
    pthread_t *threads = (pthread_t *)malloc(NUM_THREADS*sizeof(pthread_t));

     /* Abre os arquivos com os dados da matriz A*/
    FILE *matrizA = fopen(argv[2], "r");
    if (matrizA == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo da matriz A - %s\n", argv[1]);
        exit(1);
    }
    /* Abre os arquivos com os dados da matriz B */
    FILE *matrizB = fopen(argv[3], "r");
    if (matrizB == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo da matriz B\n");
        exit(1);
    }

    tmp = fscanf(matrizA, "%d", &TAM_MATRIZ);
    matA = malloc (TAM_MATRIZ * sizeof (double *));
    for(i=0; i<TAM_MATRIZ; i++)
        matA[i] = malloc(TAM_MATRIZ * sizeof(double));
    
    for(i=0; i<TAM_MATRIZ; i++)
        for(j=0; j<TAM_MATRIZ; j++){
            tmp = fscanf(matrizA, "%d", &matA[i][j]);
        }

    //imprimiMatriz(matA);

    tmp = fscanf(matrizB, "%d", &nB);
    if(TAM_MATRIZ != nB){
        fprintf(stderr, "nA != nB");
        exit(1);
    }
    matB = malloc (TAM_MATRIZ * sizeof (double *));
    for(i=0; i<TAM_MATRIZ; i++)
        matB[i] = malloc(TAM_MATRIZ * sizeof(double));
    
    for(i=0; i<TAM_MATRIZ; i++)
        for(j=0; j<TAM_MATRIZ; j++){
            tmp = fscanf(matrizB, "%d", &matB[i][j]);
        }


   // imprimiMatriz(matB);


    matC = malloc (TAM_MATRIZ * sizeof (double *));
    for(i=0; i<TAM_MATRIZ; i++)
        matC[i] = malloc(TAM_MATRIZ * sizeof(double));

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

    printf("%.5lf, ", (MyClock()-inicio)/CLOCKS_PER_SEC);

    
    
    pthread_exit(NULL);

    return 0;
}
