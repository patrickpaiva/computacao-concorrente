//Soma todos os elementos de um vetor de inteiro
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

long long int dim; //dimensao do vetor de entrada
int nthreads; //numero de threads
double *vetor; //vetor de entrada com dimensao dim

typedef struct{
  double maiorConcLocal;
  double menorConcLocal;
} tMaiorMenor;

//fluxo das threads
void * tarefa(void * arg) {
   long int id = (long int) arg; //identificador da thread
   tMaiorMenor *structLocal; //struct local do maior e menor
   structLocal = (double*) malloc(sizeof(tMaiorMenor));
   if(structLocal==NULL) {exit(1);}
   long int tamBloco = dim/nthreads;  //tamanho do bloco de cada thread 
   long int ini = id * tamBloco; //elemento inicial do bloco da thread
   long int fim; //elemento final(nao processado) do bloco da thread
   if(id == nthreads-1) fim = dim;
   else fim = ini + tamBloco; //trata o resto se houver
   //verifica quem sao o maior e menor nesse trecho
   structLocal->menorConcLocal = vetor[0]; // inicializa ambos com o valor do primeiro elemento do vetor
   structLocal->maiorConcLocal = vetor[0];
   for(long int i = ini; i<fim; i++) {
     if(vetor[i] > structLocal->maiorConcLocal){
      structLocal->maiorConcLocal = vetor[i];
     }
     if(vetor[i] < structLocal->menorConcLocal) {
      structLocal->menorConcLocal = vetor[i];
     }
   }
   //retorna o resultado da soma local
   pthread_exit((void *) structLocal); 
}

//fluxo principal
int main(int argc, char *argv[]) {
   double menorSeq;
   double maiorSeq;
   double menorConc;
   double maiorConc;
   double ini, fim; //tomada de tempo
   pthread_t *tid; //identificadores das threads no sistema
   tMaiorMenor *retorno; //valor de retorno das threads

   //recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
   if(argc < 3) {
       fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
       return 1; 
   }
   dim = atoll(argv[1]);
   nthreads = atoi(argv[2]);

   //aloca o vetor de entrada
   vetor = (double*) malloc(sizeof(double)*dim);
   if(vetor == NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //preenche o vetor de entrada
   for(long int i=0; i<dim; i++)
      vetor[i] = 1000.1/(i+1);
   
   /*//printa o vetor
   for(long int i=0; i<dim; i++)
      printf("%lf ", vetor[i]);
   */

   //verifica maior e menor sequencial
   GET_TIME(ini);
   menorSeq = vetor[0];
   maiorSeq = vetor[0];
   for(long int i=0; i<dim; i++) {
    if(vetor[i] > maiorSeq) maiorSeq = vetor[i];
    if(vetor[i] < menorSeq) menorSeq = vetor[i];
   }
   GET_TIME(fim);
   printf("Tempo sequencial:  %lf\n", fim-ini);

   //verifica maior e menor sequencial
   GET_TIME(ini);
   menorConc = vetor[0];
   maiorConc = vetor[0];
   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
   if(tid==NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //criar as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   //aguardar o termino das threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), (void**) &retorno)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
      //testa maior e menor
      if(maiorConc < retorno->maiorConcLocal){
        maiorConc = retorno->maiorConcLocal;
      }
      if(menorConc > retorno->menorConcLocal){
        menorConc = retorno->menorConcLocal;
      }
   }
   GET_TIME(fim);
   printf("Tempo concorrente:  %lf\n", fim-ini);

   //exibir os resultados
   printf("Solucao Sequencial:\n");
   printf("O maior valor eh %lf e o menor eh %lf\n", maiorSeq, menorSeq);
   printf("\n");
   printf("Solucao Concorrente:\n");
   printf("O maior valor eh %lf e o menor eh %lf\n", maiorConc, menorConc);

   //libera as areas de memoria alocadas
   free(vetor);
   free(tid);

   return 0;
}