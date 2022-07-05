# TRABALHO DE IMPLEMENTAÇÃO

## Implementação Concorrente do Método Gauss-Jacobi

Esta é uma implementação feita em C do método de Gauss-Jacobi para resolução de sistemas lineares aplicando concorrência através da utilização da biblioteca pthread.  

O programa foi desenvolvido para a disciplina de Computação Concorrente da professora Silvana Rossetto pelos alunos Julia Turazzi, Hugo Nascimento e Patrick Paiva.  

Neste repositório constam as versões sequenciais e automáticas. Nas versões sequenciais o usuário pode inserir os coeficientes da matriz A e os valores do vetor b que compoem o sistema linear Ax = b. A única exigência é que a matriz seja diagonalmente dominante, do contrário o programa corre o risco de entrar em loop infinito.

O sistema apenas retorna o vetor solução nas versões digitáveis. As versões que geram a matriz A e o vetor b de forma automática estão presentes apenas para estudo dos ganhos em tempo da aplicação da lógica concorrente.


## Compilando e rodando:

Compilando a versão sequencial digitável:
```
gcc gauss-jacobi-seq-digitavel.c -Wall -o gauss-jacobi-seq-digitavel -lpthread
```
Execute e aguarde as orientações no próximo terminal.

Compilando a versão concorrente automática:
```
gcc gauss-jacobi-automatico.c -Wall -o gauss-jacobi-automatico -lpthread
```
Rode na forma:
./gauss-jacobi-automatico.exe <numero threads> <numero de variaveis>
```
.\gauss-jacobi-automatico.exe 6 60000
```

## Versão Automática Com Script

Com o objetivo de verificar a corretude do algoritmo, criamos uma versão que gera um script em Python, o qual compara os vetores solução gerados pelo nosso programa concorrente e um algoritmo não concorrente implementado em python. Caso verifique-se uma diferença maior que 0.00001, em qualquer um dos índices, o script retorna uma mensagem de erro, caso os vetores solução sejam iguais, o mesmo retorna uma mensagem de sucesso.  

Compile normalmente:
```
gcc gauss-jacobi-automatico-script.c -Wall -o gauss-jacobi-automatico-script -lpthread

```

E execute na forma:
```
.\gauss-jacobi-automatico-script.exe 6 1000  > saida.py
```

Depois basta rodar o código Python em saida.py e receber o resultado da comparação na tela.

Obs.: Em alguns casos o código gerado pega codigicação UTF-16. Basta converter para UTF-8 e rodar o código python no terminal.

