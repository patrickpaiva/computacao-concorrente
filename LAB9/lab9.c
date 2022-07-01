/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 9 */
/* Codigo: Uso de variáveis de condição e suas operações básicas para sincronização por condição */
/* Versão que utiliza semáforos */

/***** Condicao logica da aplicacao: um programa concorrente onde a ordem de execucao
das threads eh controlada no programa, usando variaveis de condicao. O primeiro print deve
ser o "Seja Bem-vindo!" e o ultimo "Volte Sempre!", os demais devem aparecer entre esses
dois em qualquer ordem. ****/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define NTHREADS  3

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
//pthread_cond_t x_cond; // Fila para as threads intermediarias
//pthread_cond_t x_cond2; // Fila para o Volte Sempre
sem_t x_cond;
sem_t x_cond2;


/* Thread 1 */
void *A (void *t) {
  sem_wait(&x_cond2);

  printf("Volte sempre!\n");

  pthread_exit(NULL);
}
/* Thread 2 */
void *B (void *t) {
  sem_wait(&x_cond);
  printf("Aceita um copo d agua?\n");
  x++;
  if(x==4){
    sem_post(&x_cond2);
  }
  sem_post(&x_cond);
  pthread_exit(NULL);
}
/* Thread 3 */
void *C (void *t) {
  sem_wait(&x_cond);
  printf("Sente-se por favor.\n");
  x++;
  if(x==4){
    sem_post(&x_cond2);
  }
  sem_post(&x_cond);
  pthread_exit(NULL);
}
/* Thread 4 */
void *D (void *t) {
  sem_wait(&x_cond);
  printf("Fique a vontade.\n");
  x++;
  if(x==4){
    sem_post(&x_cond2);
  }
  sem_post(&x_cond);
  pthread_exit(NULL);
}
/* Threads 5 */
void *E (void *t) {
  printf("Seja bem-vindo!\n");
  x++;
  sem_post(&x_cond);
  pthread_exit(NULL);
}


/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  int *t1, *t2, *t3, *t4, *t5;
  pthread_t threads[NTHREADS];
  //aloca espaco para os identificadores das threads
  t1=malloc(sizeof(int)); 
  t2=malloc(sizeof(int)); 
  t3=malloc(sizeof(int)); 
  t4=malloc(sizeof(int)); 
  t5=malloc(sizeof(int)); 
  *t1=1, *t2=2, *t3=3; *t4=4, *t5=5;

  /* Inicializa os semaforos */
  sem_init(&x_cond, 0, 0);
  sem_init(&x_cond2, 0, 0);

  /* Cria as threads */
  pthread_create(&threads[4], NULL, E, (void *)t5);
  pthread_create(&threads[1], NULL, B, (void *)t2);
  pthread_create(&threads[2], NULL, C, (void *)t3);
  pthread_create(&threads[3], NULL, D, (void *)t4);
  pthread_create(&threads[0], NULL, A, (void *)t1);

  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("FIM.\n");

}
