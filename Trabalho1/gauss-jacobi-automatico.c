#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#include "gerarMatriz.c"
#include "timer.h"



int nthreads, n;  // numero de threads e tamanho da matriz nxn
double **a, *b, *x, *xn;

/** @brief Gera o vetor b do sistema linear, Ax = b
 * 
 *
 *  Se o argumento da função não for válido, a função não funcionará
 *
 *  @param tamanho    Tamanho que vamos gerar o vetor b
 *  @return Void.
 */
void gerarVetorB(int tamanho) {
  srand(time(NULL));
  for (int i = 0; i < tamanho; i++) {
    b[i] = (rand() % 10) + 1;
  }
}

/** @brief  Função que será executada pelas threads, a divisão foi feita de forma que cada thread
 *          execute apenas uma linha da matriz.
 * 
 *
 *  Se o argumento da função não for válido, a função não funcionará
 *
 *  @param *arg   Recebe o id da thread que está executando no momento
 *  @return Void.
 */

void *tarefa(void *arg) {
  long int id = (long int)arg;  // identificador da thread
  double parcial;
  int i, j;
  for (i = id; i < n; i += nthreads) {
    parcial = b[i];
    for (j = 0; j < n; j++) {
      if (j != i) {
        parcial -= (*(*(a + i) + j)) * (x[j]);
      }
    }
    xn[i] = parcial / (*(*(a + i) + i));
  }
  pthread_exit(NULL);
}

/** @brief  Função main do código, responsável por realizar a criação das threads e
 *          a realização do método do gauss jacobi.
 * 
 *
 *  @param argc   Inteiro que recebe a quantidade de threads na execução.
 *  @param argv   Responsável por armazenar os dois argumentos passados pela linha de comando.
 *  @return int.
 */

int main(int argc, char *argv[]) {
  printf("\"\"\"");
  double ini, fim;  // tomada de tempo
  GET_TIME(ini); // início da marcação de tempo da primeira parte do problema (criação de matrizes)b
  double epsilon = 0.00001; // erro aceito tolerável
  int i, j, flag;
  pthread_t *tid;  // identificadores das threads no sistema

  // Recebe o numero de threads e o tamanho n do sistema
  if (argc < 3) {
    fprintf(stderr, "Digite: %s <numero threads> <numero de variaveis>\n",
            argv[0]);
    return 1;
  }
  nthreads = atoi(argv[1]); // número de threads
  n = atoi(argv[2]); // quantidade de variáveis no sistema linear

  // aloca espaço para as estruturas de dados
  tid = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
  a = (double **)malloc(n * sizeof(double *));
  for (int i = 0; i < n; i++) {
    *(a + i) = (double *)malloc(sizeof(double) * n);
  }
  b = (double *)malloc(n * sizeof(double));
  x = (double *)malloc(n * sizeof(double));
  xn = (double *)malloc(n * sizeof(double));

  if (tid == NULL || a == NULL || b == NULL || x == NULL || xn == NULL) {
    fprintf(stderr, "ERRO--malloc\n");
    return 2;
  }
  gerarMatriz(n, a, nthreads); // Gerando matriz (utilizando threads na geração)
  gerarVetorB(n); // Gerando vetor do lado direito da igualdade

  for (i = 0; i < n; i++) x[i] = 0;  // inicializa o vetor x com zeros

  GET_TIME(fim); // fim da marcação de tempo da primeira parte do problema (criação de matrizes)
  printf("Tempo gasto na preparacao:  %lf\n", fim - ini);

  GET_TIME(ini); // inicio da marcação de tempo da segunda parte do problema (realização do método do gauss jacobi)
  do {
    // criar as threads
    for (long int i = 0; i < nthreads; i++) {
      if (pthread_create(tid + i, NULL, tarefa, (void *)i)) {
        fprintf(stderr, "ERRO--pthread_create\n");
        return 3;
      }
    }
    //--espera todas as threads terminarem
    for (long int i = 0; i < nthreads; i++) {
      if (pthread_join(*(tid + i), NULL)) {
        printf("--ERRO: pthread_join() \n");
        exit(-1);
      }
    }

    flag = 1; // sinalizador para saber quando parar a execução

    // verifica condicao de parada |x[i]-xn[i]|<epsilon para todo i
    for (i = 0; i < n; i++) {
      if (fabs(x[i] - xn[i]) < epsilon) {
        flag = 0;
      }
    }
    if (flag == 1) {
      for (i = 0; i < n; i++) {
        x[i] = xn[i];  // atualiza x[i]	para a proxima iteracao
      }
    }
  } while (flag == 1);
  GET_TIME(fim); // fim da marcação de tempo da segunda parte do problema (realização do método do gauss jacobi)

  printf("A solucao do SL foi finalizada com sucesso.\n");
  printf("Tempo gasto no calculo do metodo de Jacobi:  %lf\n", fim - ini);

// libera memória alocada
  free(a);
  free(b);
  free(x);
  free(xn);
}