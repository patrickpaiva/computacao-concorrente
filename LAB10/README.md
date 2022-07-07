# LAB 10

Disciplina: Computacao Concorrente(UFRJ) - 2022.1  
Prof.: Silvana Rossetto

Este é um programa concorrente do tradicional problema de leitores/escritores. Na versão original existe uma estrutura de dados compartilhada, sendo que leitores podem ler ao mesmo tempo que outros leitores, no entanto, escritores somente podem escrever quando não houver nenhum leitor lendo ou outro escritor escrevendo.

Nesse cenário ocorre que leitores ganham preferência e por vezes ocorre de escritores aguardarem muito para conseguir agir. Nesta adaptação o objetivo foi transferir a preferência para os escritores. Sempre que houver escritores na fila para escreverem, eles têm preferência e por isso os leitores ficam aguardando até que não haja nenhum escritor aguardando.

Neste LAB10 foram usados apenas semáforos da biblioteca semaphore.

## Exemplos de execução com 4 leitores e 4 escritores:

```
Leitora 1 quer ler.
Leitora 1 esta lendo
Leitora 2 quer ler.
Leitora 2 esta lendo
Escritora 1 quer escrever
Escritora 2 quer escrever
Escritora 3 quer escrever
Escritora 4 quer escrever
Leitora 3 quer ler.
Leitora 4 quer ler.
Leitora 1 terminou de ler.
Leitora 1 quer ler.
Leitora 2 terminou de ler.
Leitora 2 quer ler.
Escritora 1 esta escrevendo
Escritora 1 terminou de escrever
Escritora 2 esta escrevendo
Escritora 2 terminou de escrever
Escritora 3 esta escrevendo
Escritora 3 terminou de escrever
Escritora 4 esta escrevendo
Escritora 4 terminou de escrever
Leitora 3 esta lendo
Leitora 4 esta lendo
Leitora 1 esta lendo
Leitora 2 esta lendo
Escritora 1 quer escrever
Leitora 1 terminou de ler.
Leitora 1 quer ler.
Leitora 4 terminou de ler.
Leitora 4 quer ler.
Escritora 4 quer escrever
Escritora 2 quer escrever
Escritora 3 quer escrever
Leitora 2 terminou de ler.
Leitora 2 quer ler.
Leitora 3 terminou de ler.
Leitora 3 quer ler.
Escritora 1 esta escrevendo
Escritora 1 terminou de escrever
Escritora 4 esta escrevendo
Escritora 4 terminou de escrever
Escritora 2 esta escrevendo
Escritora 2 terminou de escrever
Escritora 3 esta escrevendo
Escritora 3 terminou de escrever
Leitora 1 esta lendo
```
## Exemplos de execução com 4 leitores e 2 escritores:

```
Leitora 1 quer ler.
Leitora 1 esta lendo
Leitora 2 quer ler.
Leitora 2 esta lendo
Escritora 1 quer escrever
Escritora 2 quer escrever
Leitora 3 quer ler.
Leitora 4 quer ler.
Leitora 1 terminou de ler.
Leitora 1 quer ler.
Leitora 2 terminou de ler.
Leitora 2 quer ler.
Escritora 1 esta escrevendo
Escritora 1 terminou de escrever
Escritora 2 esta escrevendo
Escritora 2 terminou de escrever
Leitora 3 esta lendo
Leitora 4 esta lendo
Leitora 1 esta lendo
Leitora 2 esta lendo
Leitora 4 terminou de ler.
Leitora 4 quer ler.
Leitora 4 esta lendo
Leitora 3 terminou de ler.
Leitora 3 quer ler.
Leitora 3 esta lendo
Leitora 1 terminou de ler.
Leitora 1 quer ler.
Leitora 1 esta lendo
Escritora 2 quer escrever
Escritora 1 quer escrever
Leitora 2 terminou de ler.
Leitora 2 quer ler.
Leitora 4 terminou de ler.
Leitora 4 quer ler.
Leitora 3 terminou de ler.
Leitora 3 quer ler.
Leitora 1 terminou de ler.
Leitora 1 quer ler.
Escritora 2 esta escrevendo
Escritora 2 terminou de escrever
Escritora 1 esta escrevendo
Escritora 1 terminou de escrever
Leitora 2 esta lendo
Leitora 4 esta lendo
```

## Exemplos de execução com 2 leitores e 4 escritores:

```
Leitora 1 quer ler.
Leitora 1 esta lendo
Leitora 2 quer ler.
Leitora 2 esta lendo
Escritora 3 quer escrever
Escritora 4 quer escrever
Escritora 1 quer escrever
Escritora 2 quer escrever
Leitora 1 terminou de ler.
Leitora 1 quer ler.
Leitora 2 terminou de ler.
Leitora 2 quer ler.
Escritora 3 esta escrevendo
Escritora 3 terminou de escrever
Escritora 4 esta escrevendo
Escritora 4 terminou de escrever
Escritora 1 esta escrevendo
Escritora 1 terminou de escrever
Escritora 2 esta escrevendo
Escritora 2 terminou de escrever
Leitora 1 esta lendo
Leitora 2 esta lendo
Escritora 2 quer escrever
Escritora 1 quer escrever
Leitora 1 terminou de ler.
Leitora 1 quer ler.
Escritora 3 quer escrever
Escritora 4 quer escrever
Leitora 2 terminou de ler.
Leitora 2 quer ler.
Escritora 2 esta escrevendo
Escritora 2 terminou de escrever
Escritora 1 esta escrevendo
Escritora 1 terminou de escrever
Escritora 3 esta escrevendo
Escritora 3 terminou de escrever
Escritora 4 esta escrevendo
Escritora 4 terminou de escrever
Leitora 1 esta lendo
Leitora 2 esta lendo
```

