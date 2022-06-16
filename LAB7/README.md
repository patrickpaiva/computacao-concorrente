# LAB 7

Disciplina: Computacao Concorrente(UFRJ) - 2022.1
Prof.: Silvana Rossetto

Este é um primeiro exemplo de programa que implementa computação concorrente usando Java.  

O programa recebe uma lista de números inteiros e calcula quantos pares existem nela.

## Rodando no terminal
Compile primeiro:
```
javac EncontrarPares.java
```
Rode em seguida na forma:
```
java EncontrarPares [Tamanho da Lista] [Numero de Threads]
```
## Exemplos de execução com 10 números e 2 threads:

Lista de Números  
[12, 0, 8, 69, 9, 42, 12, 28, 40, 50]  
Thread 1 iniciou!  
Thread 2 iniciou!  
Thread 1 terminou!  
Thread 2 terminou!  
Quantidade de Pares = 8  

## Exemplos de execução com 20 números e 2 threads:  

Lista de Numeros  
[22, 68, 9, 17, 49, 9, 83, 40, 63, 3, 17, 15, 18, 85, 44, 18, 56, 1, 17, 49]  
Thread 1 iniciou!  
Thread 2 iniciou!  
Thread 1 terminou!  
Thread 2 terminou!  
Quantidade de Pares = 7  

## Exemplos de execução com 10 números e 4 threads:

Lista de Numeros  
[42, 93, 64, 60, 44, 9, 52, 74, 20, 19]  
Thread 1 iniciou!  
Thread 4 iniciou!  
Thread 2 iniciou!  
Thread 3 iniciou!  
Thread 4 terminou!  
Thread 2 terminou!  
Thread 1 terminou!  
Thread 3 terminou!  
Quantidade de Pares = 7  

## Exemplos de execução com 20 números e 4 threads:

Lista de Numeros  
[4, 10, 31, 25, 62, 99, 77, 68, 87, 42, 34, 39, 95, 21, 68, 97, 70, 22, 26, 88]  
Thread 1 iniciou!  
Thread 2 iniciou!  
Thread 3 iniciou!  
Thread 4 iniciou!  
Thread 4 terminou!  
Thread 3 terminou!  
Thread 2 terminou!  
Thread 1 terminou!  
Quantidade de Pares = 11  

