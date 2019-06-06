#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

int nA, nB, n;

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}


void imprimiMatriz(int **mat, int tam){

  printf("Matriz:\n");
    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }

    return ;
}


int** multiplicacaoMatriz(int tam, int **mat1, int **mat2){

  //Multiplicação de Matriz kij

  int i,j,k,a;

  // /* Imprimi a matriz A*/
  //imprimiMatriz(mat1, tam);

  //  /* Imprimi a matriz B*/
  //imprimiMatriz(mat2, tam);

  int **mat3;
    mat3 = malloc (tam * sizeof (double *));
    for(int i=0; i<tam; i++)
        mat3[i] = malloc(tam * sizeof(double));


  for(k=0; k<tam; k++)
  {
        for(i=0; i<tam; i++)
    {
      a=mat1[i][k];
          for(j=0; j<tam; j++)
      {
            mat3[i][j] = mat3[i][j]+a*mat2[k][j];

      }

    } 
  }

  return mat3;

}


int** potenciaMatriz(int tam,int pot, int **mat1){

  int i,j,k,l,soma;

  // /* Imprimi a matriz A*/
  //imprimiMatriz(mat1, tam);

  int **mat3;
    mat3 = malloc (tam * sizeof (double *));
    for(int i=0; i<tam; i++)
        mat3[i] = malloc(tam * sizeof(double));

    for(int i=0; i<tam; i++){
        for(int j=0; j<tam; j++){
           mat3[i][j] = mat1[i][j];
        }
    }


  for (int l = 1; l < pot; l++)
  {
    mat3 = multiplicacaoMatriz(tam, mat3, mat1);

  }

  return mat3;
}

int main(int argc, char *argv[]) {
	
	double inicio = MyClock();

    int **A, **B;
    int tmp;
    if (argc != 4) {
        fprintf(stderr, "usage: prog <A> <B> n\n");
        exit(1);
    }
    /* Abre os arquivos com os dados da matriz A*/
    FILE *matrizA = fopen(argv[1], "r");
    if (matrizA == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo da matriz A - %s\n", argv[1]);
        exit(1);
    }
    /* Abre os arquivos com os dados da matriz B */
    FILE *matrizB = fopen(argv[2], "r");
    if (matrizB == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo da matriz B\n");
        exit(1);
    }
    
    n = atoi(argv[3]);
    
    /* Faz a leitura da matriz A */
    tmp = fscanf(matrizA, "%d", &nA);
    A = malloc (nA * sizeof (double *));
    for(int i=0; i<nA; i++)
        A[i] = malloc(nA * sizeof(double));
    
    for(int i=0; i<nA; i++)
        for(int j=0; j<nA; j++){
            tmp = fscanf(matrizA, "%d", &A[i][j]);
        }

    /* Imprimi a matriz A*/
    //imprimiMatriz(A, nA);
        
    /* Faz a leitura da matriz B */
    tmp = fscanf(matrizB, "%d", &nB);
    if(nA != nB){
        fprintf(stderr, "nA != nB");
        exit(1);
    }
    B = malloc (nB * sizeof (double *));
    for(int i=0; i<nB; i++)
        B[i] = malloc(nB * sizeof(double));
    
    for(int i=0; i<nB; i++)
        for(int j=0; j<nB; j++){
            tmp = fscanf(matrizB, "%d", &B[i][j]);
    }


    int **C;
    C = malloc (nB * sizeof (double *));
    for(int i=0; i<nB; i++)
        C[i] = malloc(nB * sizeof(double));


    int pid = fork();

   if (pid < 0) { /* ocorreu erro na execução do Fork */
        fprintf(stderr, "fork failed\n");
        exit(1);
   }
   else if (pid == 0) { /* processo filho */
       int pidf = fork();
       if (pidf < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
       }
       else if(pidf == 0){

            /* Multiplicação A*B */
		    C=multiplicacaoMatriz(nA, A, B);
		   // imprimiMatriz(C, nA);

       }
       else{
          
         /* Multiplicação B*A */
			   C = multiplicacaoMatriz(nA, B, A);
			  // imprimiMatriz(C, nA);
         
       }

   } 
  else { /* processo pai */
       int pidp = fork();
       if (pidp < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
       }
       else if(pidp == 0){
               
            /* Potencia A^n */
		    C=potenciaMatriz(nA, n, A);
		    //imprimiMatriz(C, nA);
       }
       else{

            /* Potencia B^n */
		    C=potenciaMatriz(nA, n, B);
		    //imprimiMatriz(C, nA);

       }
       wait(NULL); /* pai espera o término dos filhos */
       if(pidp != 0){
            printf("%.5lf, ",(MyClock()-inicio)/CLOCKS_PER_SEC);
       }
   }

	fclose(matrizA);
  fclose(matrizB); 

    return 0;

}