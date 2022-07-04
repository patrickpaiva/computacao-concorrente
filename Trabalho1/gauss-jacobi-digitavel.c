#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<pthread.h>
#include <time.h>
#include <stdlib.h>
#include "timer.h"

int nthreads, n; //numero de threads e tamanho da matriz nxn
double **a,*b,*x, *xn;

void *tarefa(void *arg){
	long int id = (long int) arg; //identificador da thread
	double parcial;
	int i, j;
	for(i=id;i<n;i+=nthreads){
		parcial=b[i];
		for(j=0;j<n;j++){
			if(j!=i){
				parcial-=(*(*(a + i)+j))*(x[j]);
			}
		}
		xn[i]=parcial/(*(*(a + i)+i));
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	double ini, fim; //tomada de tempo
	double epsilon=0.00001;
	int i,j,flag;
	pthread_t *tid; //identificadores das threads no sistema
	
	printf("\nInsira o numero de variaveis do sistema: ");
	scanf("%d",&n);
	//Recebe o numero de threads e o tamanho n do sistema
	if(argc < 2) {
       fprintf(stderr, "Digite: %s <numero threads>\n", argv[0]);
       return 1; 
  }
	nthreads = atoi(argv[1]);

	// aloca espaço para as estruturas de dados
	tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
	a = (double **) malloc(n * sizeof(double*));
	for(int i = 0; i < n; i++){
    *(a + i) =(double *) malloc(sizeof(double) * n);
  }
	b = (double *) malloc(n * sizeof(double));
	x = (double *) malloc(n * sizeof(double));
	xn = (double *) malloc(n * sizeof(double));

	if(tid==NULL || a == NULL || b == NULL || x == NULL || xn == NULL) {
		fprintf(stderr, "ERRO--malloc\n");
		return 2;
	}

	printf("\nInsira os coeficientes do sistema em linha: ");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%lf",(*(a + i)+j));
		}
	}

	printf("\nInsira o vetor b: ");
	for(i=0;i<n;i++)
		scanf("%lf",&b[i]);

	printf("Matriz digitada: \n");
	for(int i = 0; i < n; i++){
		for(int j = 0; j< n; j++){
			printf("%lf ", *(*(a + i)+j));
		}
		printf("\n");
	}
	printf("Vetor b digitado: \n");
	for(int i = 0; i< n; i++){
		printf("%lf ", b[i]);
	}
	printf("\n");
	
	for(i=0;i<n;i++)
		x[i]=0; //inicializa o vetor x com zeros

	// rotulos das contas linha a linha
	for(i=0;i<n;i++)
		printf(" x[%d] ",i);
	printf("\n");

	GET_TIME(ini);
	do{
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

		// print dos calculos linha a linha
		for(i=0;i<n;i++)
			printf("%8.5f ",xn[i]);
		printf("\n");
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
	printf("A solucao do SL eh: \n");
	for(i=0;i<n;i++)
		printf("%8.5f ",xn[i]);
	
	free(a);
	free(b);
	free(x);
	free(xn);
}