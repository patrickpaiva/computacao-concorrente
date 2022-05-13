# LAB 4

Este programa recebe um vetor de números reais e gera um novo vetor com os mesmos elementos, sendo que os que são primos são substituidos pela sua raiz quadrada. Ele possui um versão sequencial e um concorrente e abaixo temos uma breve comparação das duas performances.

Exemplo:

Vetor de entrada: [1,2,3,4,5,6,7,8,9,10]
Vetor de Saída: [1,1.41,1.73,4,2.24,6,2.65,8,9,10]

## Resultados (tempo de execução)

| Dimensão do Vetor | Sequencial | 1 Thread | 2 Threads | 4 Threads |
|---|---|---|---|---|
| 10^5 |0.007547|0.008074|0.006750|0.013182|
| 10^7 |4.608667|4.651720|2.398700|1.642296|
| 10^8 |128.038279|128.922327|68.159858|34.523543|

### Comparação

No vetor com dimensão 10^5 houve perda de rendimento comparado a versão que rodou com 4 threads face o tamanho pequeno do vetor. A perda em relação a 4 threads foi de 0.007547/0.013182 = 0,57 aproximadamente. Comparando com as versões de 1 e 2 threads praticamente não houve ganho nem perda.

Já na versão com 10^7 elementos houve ganho de 2,80 para a versão de 4 threads, 1,92 na com 2 threads e 0,99 na com apenas 1 thread.

No exemplo com 10^8 dimensão o ganho chegou a 3,70 aproximadamente em comparação a versão que utilizou 4 threads, 1,87 na versão de 2 threads e 1 na versão com apenas 1 thread.

