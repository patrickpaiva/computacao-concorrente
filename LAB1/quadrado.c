#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define NTHREADS  2 //total de threads a serem criadas
#define TAMVETOR  10000 // tamanho do vetor
int *vet; //vetor inicial
int *vetFim; // vetor final

//funcao executada pelas threads
void *square (void *arg) {
  int idThread = * (int*) arg;
  for(int i = idThread; i < TAMVETOR; i+=NTHREADS) {
    vetFim[i] = vet[i]*vet[i];
  }
  pthread_exit(NULL);
}

int main(){
  pthread_t tid_sistema[NTHREADS]; //identificadores das threads no sistema
  int thread; //variavel auxiliar
  int tid_local[NTHREADS]; //identificadores locais das threads

  // inicializando estruturas de dados
  vet = (int *) malloc(sizeof(int) * TAMVETOR);
   if (vet == NULL) {printf("ERRO--malloc\n"); return 2;}
  vetFim = (int *) malloc(sizeof(int) * TAMVETOR);
   if (vetFim == NULL) {printf("ERRO--malloc\n"); return 2;}

  //popular vetor inicial
  for(int i=0; i<TAMVETOR; i++) {
    vet[i] = rand() % 10;
  }

  // cria as threads
  for(int thread=0; thread<NTHREADS; thread++) {
    tid_local[thread] = thread;
    if (pthread_create(&tid_sistema[thread], NULL, square, (void*) &tid_local[thread])) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  //--espera todas as threads terminarem
  for (thread=0; thread<NTHREADS; thread++) {
    if (pthread_join(tid_sistema[thread], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }

  // print do vetor inicial
  printf("Vetor inicial: \n");
  for(int i=0; i<TAMVETOR; i++) {
    printf("%d ", vet[i]);
  }
  // print do vetor final
  printf("\nVetor final: \n");
  for(int i=0; i<TAMVETOR; i++) {
    printf("%d ", vetFim[i]);
  }

  return 0;
}