import numpy as np
from numpy.linalg import *

def jacobi(A, b):

  epsilon = 0.00000001
  n = A.shape[0]
  x_ant = np.zeros(n)
  x_prox = np.zeros(n)
  tolerancia = epsilon * 2
  normaResiduo = epsilon * 2
  iteracoes = 0
  
  while(normaResiduo > epsilon):
    iteracoes += 1
    x_ant = x_prox
    x_prox = np.zeros(n)
    for i in range(0,n):
      parcial = 0.0
      for j in range(0,n):
        if i != j:
          parcial += A[i,j]*x_ant[j]
      x_prox[i] = (b[i] - parcial)/A[i,i]
    normaResiduo = abs(norm(b - A@x_prox))
    tolerancia = abs(norm(x_ant - x_prox)/norm(x_prox))
    if tolerancia < epsilon:
      break
  return x_prox, iteracoes

def compareSolutions(A, B):
  epsilon = 0.00001
  n = A.shape[0]
  for i in range(n):
    if(A[i] - B[i] > epsilon):
      print("Solucao Inconsistente")
      return
  print("Solucao validada")
  
  return
