//Recebe um vetor de numeros e reais e retorna um vetor calculando a raiz dos números que forem primos
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include "../LAB3/timer.h"

long long int dim; //dimensao do vetor de entrada
int nthreads; //numero de threads
double *vetor; //vetor de entrada com dimensao dim
double *vetorSaidaSeq; //vetor de saida da funcao sequencial com dimensao dim
double *vetorSaidaConc; //vetor de saida da funcao concocrente com dimensao dim
int i_global = 0;
pthread_mutex_t mutex; //variavel de lock para exclusao mutua

int ehPrimo(long long int n) {    // retorna 1 se for primo e 0 se não for.
  if (n == 2) return 1;
  if(n <= 1 || n % 2 == 0) return 0;
  for(int i=3; i< sqrt(n)+1; i+=2){
    if(n % i == 0) return 0;
  }
  return 1;
}

void *tarefa(void * arg) {
  int i_local;
  pthread_mutex_lock(&mutex);
  i_local = i_global; i_global++; // Sessão Crítica
  pthread_mutex_unlock(&mutex);
  while(i_local < dim) {
    if(ehPrimo(vetor[i_local])){
       vetorSaidaConc[i_local] = sqrt(vetor[i_local]);
    }
    else {
      vetorSaidaConc[i_local] = vetor[i_local];
    }
    pthread_mutex_lock(&mutex);
    i_local = i_global; i_global++; // Sessão Crítica
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
   double ini, fim; //tomada de tempo
   pthread_t *tid; //identificadores das threads no sistema

   //recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
   if(argc < 3) {
       fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
       return 1; 
   }
   dim = atoll(argv[1]);
   nthreads = atoi(argv[2]);

   //aloca os vetores de entrada e saída
   vetor = (double*) malloc(sizeof(double)*dim);
   vetorSaidaSeq = (double*) malloc(sizeof(double)*dim);
   vetorSaidaConc = (double*) malloc(sizeof(double)*dim);
   if(vetor == NULL || vetorSaidaSeq == NULL || vetorSaidaConc == NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }

   //preenche o vetor de entrada
   for(int i=0; i<dim; i++)
      vetor[i] = i;

   //Implementação Sequencial
   GET_TIME(ini);
   for(int i=0; i<dim; i++){
     if(ehPrimo(vetor[i])){
       vetorSaidaSeq[i] = sqrt(vetor[i]);
     }
     else {
       vetorSaidaSeq[i] = vetor[i];
     }
   }
   GET_TIME(fim);
   printf("Tempo sequencial:  %lf\n", fim-ini);

   //Implementação Concorrente
   GET_TIME(ini);
   //--inicilaiza o mutex (lock de exclusao mutua)
   pthread_mutex_init(&mutex, NULL);

   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
   if(tid==NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //criar as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, NULL)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   //aguardar o termino das threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), NULL)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   pthread_mutex_destroy(&mutex);

   GET_TIME(fim);
   printf("Tempo concorrente:  %lf\n", fim-ini);
  
   //libera as areas de memoria alocadas
   free(vetor);
   free(vetorSaidaSeq);
   free(vetorSaidaConc);
   free(tid);

   return 0;
}
