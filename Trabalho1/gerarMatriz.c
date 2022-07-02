#include<stdlib.h>
#include <time.h>
#include<pthread.h>

double **aux;
int tam, nthreads;

void *tarefaMatriz(void *arg){
	long int id = (long int) arg; //identificador da thread
  srand(time(NULL));
	for(int i = id; i<tam; i+=nthreads){
		for(int j = 0; j<tam; j++){
			*(*(aux + i)+j) = (rand() % 10) + 1;
			if(i==j){
				*(*(aux + i)+j) = (rand() % 10 + 1)*tam*10;
			}
		}
	}
  pthread_exit(NULL);
}

int execucao(){
  pthread_t *threadsId;
  threadsId = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(threadsId==NULL) {
		fprintf(stderr, "ERRO--malloc\n");
		return 2;
	}
  for(long int i=0; i<nthreads; i++) {
      if(pthread_create(threadsId+i, NULL, tarefaMatriz, (void*) i)){
        fprintf(stderr, "ERRO--pthread_create\n");
        return 3;
      }
  }

  for (long int i=0; i<nthreads; i++) {
    if (pthread_join(*(threadsId+i), NULL)) {
        printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }

  return 0;

}

void gerarMatriz(int tamanho, double **a, int numeroThreads){
  aux = a;
  tam = tamanho;
  nthreads = numeroThreads;
	execucao();
}



