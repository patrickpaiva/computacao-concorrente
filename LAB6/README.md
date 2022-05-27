# LAB 6

Este é um programa concorrente do tradicional problema de leitores/escritores. Na versão original existe uma estrutura de dados compartilhada, sendo que leitores podem ler ao mesmo tempo que outros leitores, no entanto, escritores somente podem escrever quando não houver nenhum leitor lendo ou outro escritor escrevendo.

Nesse cenário ocorre que leitores ganham preferência e por vezes ocorre de escritores aguardarem muito para conseguir agir. Nesta adaptação o objetivo foi transferir a preferência para os escritores. Sempre que houver escritores na fila para escreverem, eles têm preferência e por isso os leitores ficam aguardando até que não haja nenhum escritor aguardando.


## Exemplos de execução com 4 leitores e 2 escritores:

L[1] quer ler  
Leitora 1 esta lendo  
L[2] quer ler  
Leitora 2 esta lendo  
E[1] quer escrever  
E[1] bloqueou  
L[4] quer ler  
L[4] bloqueou  
L[3] quer ler  
L[3] bloqueou  
E[2] quer escrever  
E[2] bloqueou  
L[1] terminou de ler  
L[2] terminou de ler  
E[1] desbloqueou  
Escritora 1 esta escrevendo  
E[1] terminou de escrever  
E[2] desbloqueou  
Escritora 2 esta escrevendo  
E[2] terminou de escrever  
L[4] desbloqueou  
Leitora 4 esta lendo  
L[3] desbloqueou  
Leitora 3 esta lendo  
L[4] terminou de ler  
L[3] terminou de ler  
L[1] quer ler  
Leitora 1 esta lendo  
L[1] terminou de ler  
L[2] quer ler  
Leitora 2 esta lendo  
E[2] quer escrever  
E[2] bloqueou  
E[1] quer escrever  
E[1] bloqueou  
L[2] terminou de ler  
E[2] desbloqueou  
Escritora 2 esta escrevendo  
E[2] terminou de escrever  
E[1] desbloqueou  
Escritora 1 esta escrevendo  
E[1] terminou de escrever  
L[4] quer ler  
Leitora 4 esta lendo  
L[3] quer ler  
Leitora 3 esta lendo  
L[4] terminou de ler  
L[3] terminou de ler  
L[1] quer ler  
Leitora 1 esta lendo  
L[1] terminou de ler  
E[2] quer escrever  
Escritora 2 esta escrevendo  
E[1] quer escrever  
E[1] bloqueou  
L[2] quer ler  
L[2] bloqueou  
E[2] terminou de escrever  
E[1] desbloqueou  
Escritora 1 esta escrevendo  
E[1] terminou de escrever  
L[2] desbloqueou  
Leitora 2 esta lendo  
L[2] terminou de ler  
L[3] quer ler  
Leitora 3 esta lendo  
L[4] quer ler  
Leitora 4 esta lendo  
L[3] terminou de ler  
L[4] terminou de ler  
