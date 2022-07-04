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

void gerarVetorB(int tamanho) {
  srand(time(NULL));
  for (int i = 0; i < tamanho; i++) {
    b[i] = (rand() % 10) + 1;
  }
}

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

int main(int argc, char *argv[]) {
  printf("\"\"\"");
  double ini, fim;  // tomada de tempo
  GET_TIME(ini);
  double epsilon = 0.00001;
  int i, j, flag;
  pthread_t *tid;  // identificadores das threads no sistema

  // Recebe o numero de threads e o tamanho n do sistema
  if (argc < 3) {
    fprintf(stderr, "Digite: %s <numero threads> <numero de variaveis>\n",
            argv[0]);
    return 1;
  }
  nthreads = atoi(argv[1]);
  n = atoi(argv[2]);

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
  gerarMatriz(n, a, nthreads);
  gerarVetorB(n);

  for (i = 0; i < n; i++) x[i] = 0;  // inicializa o vetor x com zeros

  GET_TIME(fim);
  printf("Tempo gasto na preparacao:  %lf\n", fim - ini);

  GET_TIME(ini);
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

    flag = 1;

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
  GET_TIME(fim);

  printf("A solucao do SL foi finalizada com sucesso.\n");
  printf("Tempo gasto no calculo do metodo de Jacobi:  %lf\n", fim - ini);

  // inicio do script python para checagem de corretude
  printf("\n\"\"\"\n");

  printf("import jacobiPython\n");
  printf("import numpy as np\n");
  printf("from numpy.linalg import *\n");

  printf("A = np.array([");
  for (int i = 0; i < n; i++) {
    printf("[");
    for (int j = 0; j < n; j++) {
      if (n - j == 1) {
        printf("%lf", (*(*(a + i) + j)));
      } else {
        printf("%lf,", (*(*(a + i) + j)));
      }
    }
    if (n - i == 1) {
      printf("]");
    } else {
      printf("],");
    }
  }
  printf("])\n");

  printf("b = np.array([");
  for (int i = 0; i < n; i++) {
    if (n - i == 1) {
      printf("%lf", b[i]);
    } else {
      printf("%lf,", b[i]);
    }
  }
  printf("])\n");

  printf("resp = np.array([");
  for (int i = 0; i < n; i++) {
    if (n - i == 1) {
      printf("%lf", xn[i]);
    } else {
      printf("%lf,", xn[i]);
    }
  }
  printf("])\n");

  printf("respPy, _ = jacobiPython.jacobi(A,b)\n");

  printf("jacobiPython.compareSolutions(resp,respPy)\n");

  free(a);
  free(b);
  free(x);
  free(xn);
}