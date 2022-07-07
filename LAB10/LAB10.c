/* Disciplina: Computacao Concorrente - 2022.1 */
/* Prof.: Silvana Rossetto */
/* Descricao: implementa  o problema dos leitores/escritores usando semáforos
*/
/* LAB10 - Alterando a implementação para priorizar os escritores */

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>

#define L 2 //numero de threads leitoras
#define E 4 //numero de threads escritoras

//variaveis do problema
int l=0; //contador de threads lendo
int e=0; //contador de threads escrevendo
sem_t em_e, em_l, leit, escr;


//thread leitora
void * leitor (void * arg) {
  int *id = (int *) arg;
  while(1) {
    printf("Leitora %d quer ler.\n", *id);
    sem_wait(&leit);
    sem_wait(&em_l); l++;
    if(l==1){
        sem_wait(&escr);
    } 
    sem_post(&em_l);
    sem_post(&leit);
    printf("Leitora %d esta lendo\n", *id);
    sleep(1);
    printf("Leitora %d terminou de ler.\n", *id);
    sem_wait(&em_l); l--;
    if(l==0) sem_post(&escr);
    sem_post(&em_l);
  } 
  free(arg);
  pthread_exit(NULL);
}

//thread leitora
void * escritor (void * arg) {
  int *id = (int *) arg;
  while(1) {
    printf("Escritora %d quer escrever\n", *id);
    sem_wait(&em_e); e++;
    if(e==1){
        sem_wait(&leit);
    } 
    sem_post(&em_e);
    sem_wait(&escr);
    printf("Escritora %d esta escrevendo\n", *id);
    sem_post(&escr);
    printf("Escritora %d terminou de escrever\n", *id);
    sem_wait(&em_e); e--;
    if(e==0) sem_post(&leit);
    sem_post(&em_e);
    sleep(1);
  } 
  free(arg);
  pthread_exit(NULL);
}

//funcao principal
int main(void) {
  //identificadores das threads
  pthread_t tid[L+E];
  int id[L+E];

  /* Inicializa os semaforos */
  sem_init(&leit, 0, 1);
  sem_init(&escr, 0, 1);
  sem_init(&em_l, 0, 1);
  sem_init(&em_e, 0, 1);

  //cria as threads leitoras
  for(int i=0; i<L; i++) {
    id[i] = i+1;
    if(pthread_create(&tid[i], NULL, leitor, (void *) &id[i])) exit(-1);
  }
  
  //cria as threads escritoras
  for(int i=0; i<E; i++) {
    id[i+L] = i+1;
    if(pthread_create(&tid[i+L], NULL, escritor, (void *) &id[i+L])) exit(-1);
  }

  // aguardas as threads terminarem
  for (int i = 0; i < (L+E); i++) {
    pthread_join(tid[i], NULL);
  }
  printf ("FIM.\n"); 

  pthread_exit(NULL);
  return 0;
}