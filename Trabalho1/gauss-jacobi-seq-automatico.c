#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "timer.h"

double **a, *b, *x, *xn;

/** @brief Gera a matriz A do sistema linear Ax = b, de forma sequencial.
 * 
 *
 *  Se o argumento da função não for válido, a função não funcionará
 *
 *  @param tamanho    Tamanho que vamos gerar o vetor A
 *  @param **a        Matriz a com alocação dinâmica de memória
 *  @return Void.
 */

void gerarMatriz(int tamanho, double **a) {
  srand(time(NULL));
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      *(*(a + i) + j) = (rand() % 10) + 1;
      if (i == j) {
        *(*(a + i) + j) = (rand() % 10 + 1) * tamanho * 10;
      }
    }
  }
}

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

/** @brief  Função main do código, responsável por realizar
 *          o método do gauss jacobi de forma sequencial.
 * 
 *
 *  @param argc   Inteiro que recebe a quantidade de threads na execução.
 *  @param argv   Responsável por armazenar os dois argumentos passados pela linha de comando.
 *  @return int.
 */

int main(int argc, char *argv[]) {
  double ini, fim;  // tomada de tempo
  GET_TIME(ini);// início da marcação de tempo da primeira parte do problema (criação de matrizes)
  double epsilon = 0.00001, parcial; // erro tolerável
  int i, j, n, flag;

  if (argc < 2) {
    fprintf(stderr, "Digite: %s <numero de variaveis>\n", argv[0]);
    return 1;
  }
  n = atoi(argv[1]);

  // aloca espaço para as estruturas de dados
  a = (double **)malloc(n * sizeof(double *));
  for (int i = 0; i < n; i++) {
    *(a + i) = (double *)malloc(sizeof(double) * n);
  }
  b = (double *)malloc(n * sizeof(double));
  x = (double *)malloc(n * sizeof(double));
  xn = (double *)malloc(n * sizeof(double));

  if (a == NULL || b == NULL || x == NULL || xn == NULL) {
    fprintf(stderr, "ERRO--malloc\n");
    return 2;
  }

  gerarMatriz(n, a);
  gerarVetorB(n);

  for (i = 0; i < n; i++) x[i] = 0;  // inicializa o vetor x com zeros

  GET_TIME(fim); // fim da marcação de tempo da primeira parte do problema (criação de matrizes)
  printf("Tempo gasto na preparacao:  %lf\n", fim - ini);

  GET_TIME(ini);  // inicio da marcação de tempo da segunda parte do problema (realização do método do gauss jacobi)
  do {
    for (i = 0; i < n; i++) {
      parcial = b[i];
      for (j = 0; j < n; j++) {
        if (j != i) parcial -= (*(*(a + i) + j)) * x[j];
      }
      xn[i] = parcial / (*(*(a + i) + i));
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
  GET_TIME(fim); // fim da marcação de tempo da segunda parte do problema (realização do método do gauss jacobi)

  printf("A solucao do SL foi finalizada com sucesso.\n");
  printf("Tempo gasto no calculo do metodo de Jacobi:  %lf\n", fim - ini);

  // libera memória alocada
  free(a);
  free(b);
  free(x);
  free(xn);

  return 1;
}