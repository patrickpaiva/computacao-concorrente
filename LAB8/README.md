# LAB 8

Disciplina: Computacao Concorrente(UFRJ) - 2022.1  
Prof.: Silvana Rossetto

Este é um programa que implementa o padrão de leitores e escritores para acessar uma variável compartilhada. 

O programa possui três threads. A thread Leitor apenas lê a variável compartilhada e nos diz se é par ou ímpar.  
A thread Escritor acessa a variável compartilhada e a incrementa em 1. Já a thread LeitorEEscritor acessa a variável, imprime a mesma na tela e depois atualiza seu valor pelo id da thread corrente.  

O lab acompanha um script em python que checa se a lógica de leitores e escritores está correta.

## Rodando no terminal
Compile primeiro:
```
javac LAB8.java
```
Rode em seguida na forma:
```
java LeitorEscritor
```
Caso queira, salve o output e execute o script python
```
java LeitorEscritor > saida.py
python saida.py
```
## Exemplo de execução (output):

```
import verificaLE
le = verificaLE.LE()
le.leitorLendo(1)
le.leitorLendo(3)
le.leitorLendo(2)
le.leitorLendo(1)
le.escritorBloqueado(3)
le.escritorBloqueado(2)
le.escritorBloqueado(1)
le.leitorLendo(2)
le.leitorLendo(4)
le.leitorLendo(3)
# A variavel vale 0
# A variavel vale 0
# A variavel vale 0
le.leitorSaindo(3)
le.escritorBloqueado(3)
le.leitorSaindo(1)
le.escritorBloqueado(1)
le.leitorSaindo(2)
le.escritorBloqueado(2)
# A variavel eh par.
# A variavel eh par.
# A variavel eh par.
le.leitorSaindo(2)
le.leitorSaindo(3)
le.leitorSaindo(1)
# A variavel eh par.
le.leitorSaindo(4)
le.escritorEscrevendo(3)
le.escritorSaindo(3)
le.escritorEscrevendo(2)
le.escritorBloqueado(2)
le.escritorBloqueado(1)
le.escritorBloqueado(3)
le.escritorBloqueado(1)
le.leitorBloqueado(1)
le.escritorSaindo(2)
le.escritorEscrevendo(2)
le.leitorBloqueado(1)
le.escritorBloqueado(1)
le.escritorBloqueado(3)
le.escritorBloqueado(1)
le.escritorSaindo(2)
le.leitorLendo(1)
le.escritorBloqueado(1)
le.escritorBloqueado(3)
le.escritorBloqueado(1)
le.leitorLendo(2)
# A variavel eh par.
le.leitorSaindo(1)
# A variavel eh par.
le.leitorSaindo(2)
le.escritorEscrevendo(1)
le.leitorBloqueado(3)
le.escritorSaindo(1)
le.escritorEscrevendo(3)
le.leitorBloqueado(3)
le.escritorBloqueado(1)
le.escritorBloqueado(2)
le.leitorBloqueado(1)
le.escritorBloqueado(3)
le.escritorSaindo(3)
le.leitorLendo(3)
le.escritorBloqueado(3)
le.leitorLendo(1)
le.escritorBloqueado(2)
le.escritorBloqueado(1)
le.leitorLendo(2)
# A variavel vale 3
le.leitorSaindo(2)
le.escritorBloqueado(2)
le.leitorLendo(4)
le.leitorLendo(1)
# A variavel vale 3
le.leitorSaindo(1)
le.escritorBloqueado(1)
# A variavel eh impar.
le.leitorSaindo(1)
# A variavel eh impar.
le.leitorSaindo(3)
# A variavel eh impar.
le.leitorSaindo(4)
le.escritorEscrevendo(3)
le.leitorBloqueado(2)
le.escritorSaindo(3)
le.escritorEscrevendo(2)
le.leitorBloqueado(2)
le.escritorBloqueado(1)
le.escritorBloqueado(2)
le.escritorBloqueado(1)
le.leitorBloqueado(1)
le.escritorSaindo(2)
le.leitorLendo(2)
le.leitorLendo(1)
le.escritorBloqueado(1)
le.escritorBloqueado(2)
le.escritorBloqueado(1)
# A variavel eh impar.
le.leitorSaindo(1)
# A variavel eh impar.
le.leitorSaindo(2)
le.escritorEscrevendo(1)
le.leitorBloqueado(3)
le.escritorSaindo(1)
le.escritorEscrevendo(2)
le.leitorBloqueado(3)
le.escritorBloqueado(1)
le.leitorBloqueado(1)
le.leitorBloqueado(3)
le.escritorSaindo(2)
le.leitorLendo(3)
# A variavel vale 2
le.leitorLendo(3)
le.leitorLendo(1)
le.escritorBloqueado(1)
le.leitorSaindo(3)
le.escritorBloqueado(3)
le.escritorBloqueado(2)
le.escritorBloqueado(1)
# A variavel eh par.
le.leitorSaindo(1)
# A variavel eh par.
le.leitorSaindo(3)
le.escritorEscrevendo(1)
le.escritorBloqueado(3)
le.leitorBloqueado(2)
le.leitorBloqueado(4)
le.escritorSaindo(1)
le.escritorEscrevendo(3)
le.leitorBloqueado(4)
le.leitorBloqueado(2)
le.escritorBloqueado(3)
le.escritorBloqueado(1)
le.escritorBloqueado(2)
le.leitorBloqueado(1)
le.escritorSaindo(3)
le.leitorLendo(4)
le.leitorLendo(1)
le.escritorBloqueado(2)
le.escritorBloqueado(1)
le.escritorBloqueado(3)
le.leitorLendo(2)
le.leitorLendo(2)
# A variavel vale 3
le.leitorSaindo(2)
le.escritorBloqueado(2)
le.leitorLendo(1)
# A variavel vale 3
le.leitorSaindo(1)
le.escritorBloqueado(1)
# A variavel eh impar.
le.leitorSaindo(1)
# A variavel eh impar.
le.leitorSaindo(2)
# A variavel eh impar.  
```
