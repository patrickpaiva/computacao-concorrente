#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <time.h>
#include "timer.h"


double **a,*b,*x, *xn;

void gerarMatriz(int tamanho, double **a){
	srand(time(NULL));
	for(int i = 0; i<tamanho; i++){
		for(int j = 0; j<tamanho; j++){
			*(*(a + i)+j) = (rand() % 10) + 1;
			if(i==j){
				*(*(a + i)+j) = (rand() % 10 + 1)*tamanho*10;
			}
		}
	}
}

void gerarVetorB(int tamanho){
	srand(time(NULL));
	for(int i = 0; i<tamanho; i++){
		b[i] = (rand() % 10) + 1;
	}
}

int main(int argc, char *argv[])
{
	double ini, fim; //tomada de tempo
	GET_TIME(ini);
	double epsilon=0.00001,parcial;
	int i,j,n,flag;

	if(argc < 2) {
       fprintf(stderr, "Digite: %s <numero de variaveis>\n", argv[0]);
       return 1; 
  }
	n = atoi(argv[1]);

	//aloca espaço para as estruturas de dados
	a = (double **) malloc(n * sizeof(double*));
	for(int i = 0; i < n; i++){
    *(a + i) =(double *) malloc(sizeof(double) * n);
  }
	b = (double *) malloc(n * sizeof(double));
	x = (double *) malloc(n * sizeof(double));
	xn = (double *) malloc(n * sizeof(double));

	if(a == NULL || b == NULL || x == NULL || xn == NULL) {
		fprintf(stderr, "ERRO--malloc\n");
		return 2;
	}

	gerarMatriz(n, a);
	gerarVetorB(n);
	// printf("Verifica a matriz: \n");
	// for(int i = 0; i < n; i++){
	// 	for(int j = 0; j< n; j++){
	// 		printf("%lf ", *(*(a + i)+j));
	// 	}
	// 	printf("\n");
	// }
	// printf("Verifica o b: \n");
	// for(int i = 0; i< n; i++){
	// 	printf("%lf ", b[i]);
	// }
	// printf("\n");

	for(i=0;i<n;i++)
		x[i]=0; //inicializa o vetor x com zeros

	// for(i=0;i<n;i++)
	// 	printf(" x[%d] ",i);
	// printf("\n");
	GET_TIME(fim);
  printf("Tempo gasto na preparacao:  %lf\n", fim-ini);

	GET_TIME(ini);	
	do
	{
		for(i=0;i<n;i++)
		{
			parcial=b[i];
			for(j=0;j<n;j++){
				if(j!=i)
					parcial-=(*(*(a + i)+j))*x[j];
			}
			xn[i]=parcial/(*(*(a + i)+i));
		}
		// for(i=0;i<n;i++)
		// 	printf("%8.5f ",xn[i]);
		// printf("\n");
		flag=1; 
		//verifica condicao de parada |x[i]-xn[i]|<epsilon para todo i
		for(i=0;i<n;i++){
			if(fabs(x[i]-xn[i])<epsilon){
				flag=0;
			}
		}

		if(flag==1){
			for(i=0;i<n;i++){
				x[i]=xn[i]; //atualiza x[i]	para a proxima iteracao
			}
		}
	}while(flag==1);
	GET_TIME(fim);
	printf("A solucao do SL foi finalizada com sucesso.\n");
  printf("Tempo gasto no calculo do metodo de Jacobi:  %lf\n", fim-ini);
	// for(i=0;i<n;i++)
	// 	printf("%8.5f ",xn[i]);
	
	return 1;
}