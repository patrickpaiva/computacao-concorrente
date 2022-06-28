#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<pthread.h>
#include <time.h>
#include <stdlib.h>
#include "timer.h"

int nthreads, n; //numero de threads e tamanho da matriz nxn
// double a[10000][10000],b[10000],x[10000], xn[10000];
double *a,*b,*x, *xn;

void gerarMatrix(int tamanho){
	srand(time(NULL));
	for(int i = 0; i<tamanho; i++){
		for(int j = 0; j<tamanho; j++){
			a[i*tamanho+j] = (rand() % 10) + 1;
			if(i==j){
				a[i*tamanho+j] = (rand() % 10 + 1)*tamanho*10;
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

void *tarefa(void *arg){
	long int id = (long int) arg; //identificador da thread
	double parcial;
	int i, j;
	for(i=id;i<n;i+=nthreads){
		parcial=b[i];
		for(j=0;j<n;j++){
			if(j!=i)
				parcial-=(a[i*n+j])*(x[j]);
		}
		xn[i]=parcial/(a[i*n+i]);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	double ini, fim; //tomada de tempo
	double epsilon=0.00001;
	int i,j,flag;
	pthread_t *tid; //identificadores das threads no sistema
	
	//Recebe o numero de threads e o tamanho n do sistema
	if(argc < 3) {
       fprintf(stderr, "Digite: %s <numero threads> <numero de variaveis>\n", argv[0]);
       return 1; 
  }
	nthreads = atoi(argv[1]);
	n = atoi(argv[2]);
	// printf("\nInsira o numero de variaveis do sistema: ");
	// scanf("%d",&n);
	// getchar();

	// aloca espaço para as estruturas de dados
	tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
	a = (double *) malloc(n * n * sizeof(double));
	b = (double *) malloc(n * sizeof(double));
	x = (double *) malloc(n * sizeof(double));
	xn = (double *) malloc(n * sizeof(double));

	if(tid==NULL || a == NULL || b == NULL || x == NULL || xn == NULL) {
		fprintf(stderr, "ERRO--malloc\n");
		return 2;
	}
	// printf("\nInsira os coeficientes do sistema em linha: ");
	gerarMatrix(n);
	gerarVetorB(n);
	// printf("Verifica a matriz: \n");
	// for(int i = 0; i < n; i++){
	// 	for(int j = 0; j< n; j++){
	// 		printf("%lf ", a[i*n+j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("Verifica o b: \n");
	// for(int i = 0; i< n; i++){
	// 	printf("%lf ", b[i]);
	// }
	// printf("\n");
	// for(i=0;i<n;i++)
	// {
	// 	for(j=0;j<n;j++)
	// 	{
	// 		scanf("%lf",&a[i][j]);
	// 	}
	// }
	// printf("\nInsira o vetor b: ");
	// for(i=0;i<n;i++)
	// 	scanf("%lf",&b[i]);
	for(i=0;i<n;i++)
		x[i]=0; //inicializa o vetor x com zeros


	// for(i=0;i<n;i++)
	// 	printf(" x[%d] ",i);
	// printf("\n");
	GET_TIME(ini);
	do
	{
		// for(i=0;i<n;i++) // neste for entra a concorrencia, cada thread pega um xn
		// {
		// 	sum=b[i];
		// 	for(j=0;j<n;j++)
		// 		if(j!=i)
		// 			sum-=a[i][j]*x[j];
		// 		xn[i]=sum/a[i][i];
		// }

		//criar as threads
		for(long int i=0; i<nthreads; i++) {
				if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
					fprintf(stderr, "ERRO--pthread_create\n");
					return 3;
				}
		}
	//--espera todas as threads terminarem
		for (long int i=0; i<nthreads; i++) {
			if (pthread_join(*(tid+i), NULL)) {
					printf("--ERRO: pthread_join() \n"); exit(-1); 
			} 
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
  printf("Tempo gasto:  %lf\n", fim-ini);
	// printf("A solucao do SL eh: \n");
	// for(i=0;i<n;i++)
	// 	printf("%8.5f ",xn[i]);
	free(a);
	free(b);
	free(x);
	free(xn);
}