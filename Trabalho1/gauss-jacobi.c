#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<pthread.h>

int nthreads, n; //numero de threads e tamanho da matriz nxn
double a[10][10],b[10],x[10], xn[10];

void *tarefa(void *arg){
	long int id = (long int) arg; //identificador da thread
	double parcial;
	int i, j;
	for(i=id;i<n;i+=nthreads){
		parcial=b[i];
		for(j=0;j<n;j++){
			if(j!=i)
				parcial-=a[i][j]*x[j];
			xn[i]=parcial/a[i][i];
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	double epsilon=0.00001;
	int i,j,flag;
	pthread_t *tid; //identificadores das threads no sistema
	
	if(argc < 2) {
       fprintf(stderr, "Digite: %s <numero threads>\n", argv[0]);
       return 1; 
  }
	nthreads = atoi(argv[1]);

	tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
	if(tid==NULL) {
		fprintf(stderr, "ERRO--malloc\n");
		return 2;
	}

	printf("\nInsira o numero de variaveis do sistema: ");
	scanf("%d",&n);
	printf("\nInsira os coeficientes do sistema em linha: ");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%lf",&a[i][j]);
		}
	}
	printf("\nInsira o vetor b: ");
	for(i=0;i<n;i++)
		scanf("%lf",&b[i]);
	for(i=0;i<n;i++)
		x[i]=0; //inicializa o vetor x com zeros


	for(i=0;i<n;i++)
		printf(" x[%d] ",i);
	printf("\n");

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

	printf("A solucao do SL eh: \n");
	for(i=0;i<n;i++)
		printf("%8.5f ",xn[i]);
}