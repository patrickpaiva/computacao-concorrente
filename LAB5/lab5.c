/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 5 */
/* Codigo: Uso de variáveis de condição e suas operações básicas para sincronização por condição */

/***** Condicao logica da aplicacao: um programa concorrente onde a ordem de execucao
das threads eh controlada no programa, usando variaveis de condicao. O primeiro print deve
ser o "Seja Bem-vindo!" e o ultimo "Volte Sempre!", os demais devem aparecer entre esses
dois em qualquer ordem. ****/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS  3

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond; // Fila para as threads intermediarias
pthread_cond_t x_cond2; // Fila para o Volte Sempre


/* Thread 1 */
void *A (void *t) {
  pthread_mutex_lock(&x_mutex);
  while (x<4) {
    pthread_cond_wait(&x_cond2, &x_mutex);
  }
  printf("Volte sempre!\n");
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}
/* Thread 2 */
void *B (void *t) {
  pthread_mutex_lock(&x_mutex);
  if (x==0) {
    pthread_cond_wait(&x_cond, &x_mutex);
  }
  printf("Aceita um copo d agua?\n");
  x++;
  if(x==4){
    pthread_cond_signal(&x_cond2);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}
/* Thread 3 */
void *C (void *t) {
  pthread_mutex_lock(&x_mutex);
  if (x==0) {
    pthread_cond_wait(&x_cond, &x_mutex);
  }
  printf("Sente-se por favor.\n");
  x++;
  if(x==4){
    pthread_cond_signal(&x_cond2);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}
/* Thread 4 */
void *D (void *t) {
  pthread_mutex_lock(&x_mutex);
  if (x==0) {
    pthread_cond_wait(&x_cond, &x_mutex);
  }
  printf("Fique a vontade.\n");
  x++;
  if(x==4){
    pthread_cond_signal(&x_cond2);
  }
  pthread_mutex_unlock(&x_mutex);

  pthread_exit(NULL);
}
/* Threads 5 */
void *E (void *t) {
  pthread_mutex_lock(&x_mutex);
  printf("Seja bem-vindo!\n");
  x++;
  pthread_cond_broadcast(&x_cond);
  pthread_mutex_unlock(&x_mutex);

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

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);
  pthread_cond_init (&x_cond2, NULL);

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

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
  pthread_cond_destroy(&x_cond2);
}
