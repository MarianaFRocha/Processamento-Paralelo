/*Algoritmo Paralelo de Filtros de Imagens

	Copilar: 	gcc PNM.c -o pnm -lm
				./pnm <Imagem.pnm>
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <string.h>


typedef struct {
	int altura, largura, threshold;
	unsigned char ***pixel; //vetor com todos os pixels 
} Imagem;

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

/*Declaração das Funções*/ 
unsigned char*** aloca(int n, int m);
Imagem *readPNM(const char *nomeArquivo); 
void escurece(Imagem *img, int fator);
void salvaPNM(Imagem *img, char *nomeImagem);
void filtroSobel(Imagem *img, Imagem *resp);
void filtroRealcarImagem(Imagem *img, Imagem *resp);
void filtroBordasLaplace(Imagem *img, Imagem *resp);
void filtro4(Imagem *img, Imagem *resp);

/*Algoritmo Paralelo de Filtros de Imagens*/

int main(int argc, char *argv[]) {

	double inicio = MyClock();

	if (argc != 2) {
        fprintf(stderr, "usage: prog image.pnm\n");
        exit(1);
    }

    int i, j;

	Imagem *imagem = readPNM(argv[1]);
	Imagem *resposta = (Imagem*)malloc(sizeof(Imagem));

    resposta->pixel = aloca(imagem->altura+2, imagem->largura+2);
    resposta->altura = imagem->altura;
    resposta->largura = imagem->largura;
    resposta->threshold = imagem->threshold;

	

	int tamNome = strlen(argv[1]); 
	char *nomeImagem = (char*)malloc((tamNome + 17)* sizeof(char)); // _Resultado_P#.pnm são 17 caracteres

	int temp = strlen(nomeImagem);

	for (int i = 0; i<(tamNome-4) ; i++)
	{
		nomeImagem[i]=argv[1][i];
	}

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
            // operação
       		sprintf(nomeImagem, "%s%s", nomeImagem, "_Resultado_P1.pnm");
       		filtroSobel(imagem, resposta);
       		salvaPNM(resposta, nomeImagem);
       }
       else{
       		sprintf(nomeImagem, "%s%s", nomeImagem, "_Resultado_P2.pnm");
       		filtroRealcarImagem(imagem, resposta);
       		salvaPNM(resposta, nomeImagem);
       }
   } 
   else {  //processo pai 
       int pidp = fork();
       if (pidp < 0) {
            fprintf(stderr, "fork failed\n");
            exit(1);
       }
       else if(pidp == 0){
       		sprintf(nomeImagem, "%s%s", nomeImagem, "_Resultado_P3.pnm");
       		filtroBordasLaplace(imagem, resposta);
       		salvaPNM(resposta, nomeImagem);
       		
       }
       else{
       		sprintf(nomeImagem, "%s%s", nomeImagem, "_Resultado_P4.pnm");
       		filtro4(imagem, resposta);
       		salvaPNM(resposta, nomeImagem);
       		
       }
       wait(NULL); /* pai espera o término dos filhos */
       if(pidp != 0){
            double tempoPar = (MyClock()-inicio)/CLOCKS_PER_SEC;
            printf(" %.5lf,", tempoPar);
       		free(imagem);
       }
   }

	return 0;
}

// Aloca e inicializa memoria para uma matriz de dimencoes (N x M x 3) - vetor de pixels
unsigned char*** aloca(int n, int m) {
    int i, j;
    unsigned char ***M;
    M = (unsigned char***) malloc(n * sizeof(unsigned char**));
    for(i = 0; i < n; i++){
        M[i] = (unsigned char**) malloc(m * sizeof(unsigned char*));
        for(j = 0; j < m; j++){
        	M[i][j] = (unsigned char*) malloc(3 * sizeof(unsigned char)); 
        	M[i][j][0] = 0; //Vermelho
        	M[i][j][1] = 0; //Verde
        	M[i][j][2] = 0; //Azul
        }
    }
    if (!M) {
		fprintf(stderr, "Erro na alocacao da memoria\n");
		exit(1);
	}

    return M;
}

/* Lê imagem PNM  */
Imagem *readPNM(const char *nomeArquivo) {
	char buff[16];
	Imagem *img;
	FILE *fp;
	int c;
    fp = fopen(nomeArquivo, "r");

    if (fp == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    /*le linha 1 do arquivo*/
    if (!fgets(buff, sizeof(buff), fp)) {
		perror("stdin");
		exit(1);
	}

	if (buff[0] != 'P' || buff[1] != '3') {
		fprintf(stderr, "Formato da imagem invalido (deve ser 'P3')\n");
		exit(1);
	}

	img = (Imagem *) malloc(sizeof(Imagem));
	if (!img) {
		fprintf(stderr, "Erro na alocacao da memoria\n");
		exit(1);
	}

	c = getc(fp);

	/*le linha 2 do arquivo*/
	while (c == '#') {
		while (getc(fp) != '\n');
		c = getc(fp);
	}

	ungetc(c, fp); //o que essa função faz??

	/*Le linha 3 - largura e altura*/
	if (fscanf(fp, "%d %d", &img->largura, &img->altura) != 2) {
		fprintf(stderr, "Tamanho da imagem invalido\n");
		exit(1);
	}

	/*Le linha 4 - Valor Maximo*/
	if (fscanf(fp, "%d", &img->threshold) != 1) {
		fprintf(stderr, "Componente rgb invalido\n");
		exit(1);
	}

	while (fgetc(fp) != '\n');

	/*aloca a matriz de pixels*/
	img->pixel = aloca(img->altura+2, img->largura+2);

	if (!img) {
		fprintf(stderr, "Erro na alocacao da memoria\n");
		exit(1);
	}
	int r, g, b;
	for(int i = 1; i <= img->altura; i++){
        for(int j = 1; j <= img->largura; j++){
            fscanf(fp, "%d %d %d", &r, &g, &b);
            img->pixel[i][j][0] = (unsigned char)r;
            img->pixel[i][j][1] = (unsigned char)g;
            img->pixel[i][j][2] = (unsigned char)b;
            //printf("%d %d %d ", r, g, b);
        }
        //printf("\n");
    }

	return img;
}

void salvaPNM(Imagem *img, char *nomeImagem){
	FILE *arquivo;
	int c, rgb_comp_color;
    arquivo = fopen(nomeImagem, "w");
    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "#Feita por Mariana Ferreira Rocha\n");
    fprintf(arquivo, "%d %d %d\n", img->largura, img->altura, img->threshold);
    for(int i = 1; i <= img->altura; i++)
      for(int j = 1; j <= img->largura; j++) 
      	for(int k = 0; k < 3; k++)
      		fprintf(arquivo, "%d\n", (int)img->pixel[i][j][k]);
}


void filtroSobel(Imagem *img, Imagem *resp){

	int i, j, k, aux1, aux2;

	for(i=1;i<img->altura-1;i++){
	 	for(j=1;j<img->largura-1;j++){
		    for (k=0; k<3; k++) {
		        //Faz os calculos para aplicar o filtro
		       aux1=1*(int)img->pixel[i-1][j-1][k] + 2*(int)img->pixel[i-1][j][k] + 1*(int)img->pixel[i-1][j+1][k]
		            + (-1)*(int)img->pixel[i+1][j-1][k] + (-2)*(int)img->pixel[i+1][j][k] + (-1)*(int)img->pixel[i+1][j+1][k];

		       aux2=1*(int)img->pixel[i-1][j-1][k] + (-1)*(int)img->pixel[i-1][j+1][k] + 2*(int)img->pixel[i][j-1][k]
		            + (-2)*(int)img->pixel[i][j+1][k] + 1*(int)img->pixel[i+1][j-1][k] + (-1)*(int)img->pixel[i+1][j+1][k];
		           
		       resp->pixel[i][j][k]=(unsigned char)(sqrt(aux1*aux1 + aux2*aux2)); //Modifica o pixel 
		 	}
		 }
	}

}

void filtroRealcarImagem(Imagem *img, Imagem *resp){

	int i, j, k, aux;

	for(i=1;i<img->altura-1;i++){
	 	for(j=1;j<img->largura-1;j++){
		    for (k=0; k<3; k++) {
		       aux=((-1)*(int)img->pixel[i-1][j][k] + (-1)*(int)img->pixel[i][j-1][k] 
		       	+ (5)*(int)img->pixel[i][j][k] + (-1)*(int)img->pixel[i][j+1][k] + (-1)*(int)img->pixel[i+1][j][k]);

		       if(aux<0){
		       		aux=0;
		       }
		       if(aux>255){
		       		aux=255;
		       }
		       resp->pixel[i][j][k]=(unsigned char)aux;

		       
		 	}
		 }
	}
}


void filtroBordasLaplace(Imagem *img, Imagem *resp){

	int i, j, k, aux;

	for(i=1;i<img->altura-1;i++){
	 	for(j=1;j<img->largura-1;j++){
		    for (k=0; k<3; k++) {
		       aux=((-1)*(int)img->pixel[i-1][j][k] + (-1)*(int)img->pixel[i][j-1][k] 
		       	+ (4)*(int)img->pixel[i][j][k] + (-1)*(int)img->pixel[i][j+1][k] + (-1)*(int)img->pixel[i+1][j][k]);

		       if(aux<0){
		       		aux=0;
		       }
		       if(aux>255){
		       		aux=255;
		       }
		       resp->pixel[i][j][k]=(unsigned char)aux;
			       
		 	}
		 }
	}
}

//filtro de deteccao de variacoes bruscas no sentido horizontal (Passa-Alta)
void filtro4(Imagem *img, Imagem *resp){

	int i, j, k, l, aux;

	for(i=1;i<img->altura-1;i++){
	 	for(j=1;j<img->largura-1;j++){
		    for (k=0; k<3; k++) {
		       aux=((int)img->pixel[i+1][j-1][k] + (int)img->pixel[i+1][j][k] + (int)img->pixel[i+1][j+1][k] 
		       	- (int)img->pixel[i-1][j-1][k] - (int)img->pixel[i-1][j][k] - (int)img->pixel[i-1][j-1][k]);


		       if(aux<0){
		       		aux=1;
		       }
		       if(aux>255){
		       		aux=254;
		       }
		       resp->pixel[i][j][k]=(unsigned char)aux;
			       
		 	}
		 }
	}
}
