#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>


double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}


int main( int argc, char *argv[ ] ){

	if(argc !=2){
		printf("Erro");
	}

	int tam = atoi(argv[1]);
	int i,j,k,soma;
	int mat1[tam][tam], mat2[tam][tam], mat3[tam][tam];

	for(i=0; i<tam; i++)
 	{
    		for(j=0; j<tam; j++)
 		{
    		mat1[i][j] = 1;
			mat2[i][j] = 1;
			mat3[i][j] = 0;

 		}	
 	}

	
	double inicio1 = MyClock();

	for(i=0; i<tam; i++)
 	{
    	for(j=0; j<tam; j++)
 		{
 			soma=0;
    		for(k=0; k<tam; k++)
 			{
    				soma = soma+mat1[i][k]*mat2[k][j];

 			}
 			mat3[i][j]=soma;

 		}	
 	}

	printf("%.5lf, ",(MyClock()-inicio1)/CLOCKS_PER_SEC);
	

}


