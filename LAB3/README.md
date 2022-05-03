# LAB 3

Este programa recebe um vetor de números reais e verifica qual o maior número presente e o menor. Ele possui um versão sequencial e um concorrente e abaixo temos uma breve comparação das duas performances.

## Resultados

| Dimensão do Vetor | Sequencial | 1 Thread | 2 Threads | 4 Threads |
|---|---|---|---|---|
| 10^5 |0.000213|0.000422|0.000317|0.000382|
| 10^7 |0.021549|0.024387|0.012757|0.006728|
| 10^8 |0.216887|0.242655|0.123068|0.062191|

### Comparação

No primeiro exemplo houve perda de rendimento da versão sequencial para a versão concorrente face a baixa dimensão do vetor de entrada. Comparando usando o valor para 4 threads, tivemos uma perda de rendimento de 0.000213/0.000382 = 0.558 aproximadamente.

Já na versão com 10^7 elementos, houve ganho de 3,20 e na de 10^8 o ganho chegou a 3,49 aproximadamente.

