# LAB 4

Este programa recebe um vetor de números reais e gera um novo vetor com os mesmos elementos, sendo que os que são primos são substituidos pela sua raiz quadrada. Ele possui um versão sequencial e um concorrente e abaixo temos uma breve comparação das duas performances.

Exemplo:

Vetor de entrada: [1,2,3,4,5,6,7,8,9,10]
Vetor de Saída: [1,1.41,1.73,4,2.24,6,2.65,8,9,10]

## Resultados (tempo de execução)

| Dimensão do Vetor | Sequencial | 1 Thread | 2 Threads | 4 Threads |
|---|---|---|---|---|
| 10^5 |0.027572|0.027959|0.015391|0.021756|
| 10^6 |0.842988|0.852787|0.442120|0.284785|
| 10^7 |27.821625|27.801329|14.980661|7.637784|

### Comparação

No vetor com dimensão 10^5 houve pequeno ganho de rendimento, sendo a melhor versão a que rodou com 2 threads face o tamanho do vetor. O ganho em relação a 2 threads foi de 0.027572/0.015391 = 1,79 aproximadamente.

Já na versão com 10^6 elementos, houve ganho de 2,96 para a versão de 4 threads e na de 10^7 o ganho chegou a 3,64 aproximadamente também em comparação a versão que utilizou 4 threads.

