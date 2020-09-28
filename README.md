# Jantar_dos_filosofos_C
Implementação do desafio clássico Jantar dos Filosofos em C com multiprocessos.

## Introdução
Este projeto foi dado como trabalho para entrega pelo professor Cesar Tegani Tofanini, na matéria de Programação distribuída, paralela e concorrente na Universidade Padre Anchieta de Jundiaí - SP. E tem como o objetivo implantar o desafio do Jantar dos filosofos utilizando semaphores na linguagem C e multiprocessos.

## Objetivo
Implantar o desafio "Jantar dos Filosofos" em C, utilizando semaphores com multiprocessos.

## Metodologia
- Cinco filósofos sentam-se à mesa circular.
- Passam a vida pensando ou comendo.
- Para comer usam dois garfos: um de cada lado.
- Cada garfo é compartilhado por dois filósofos.
- O tempo que o filosofo passa comendo ou pensando é aleatório.
- Cada filosofo é um processo.
- Foi implementado um nível de fome para os filosofos na tentativa de evitar/diminuir possíveis deadlocks e starvation dos programas, este checa a fome do filosofo, se fome < 0 depois de ter pego o garfo a sua esquerda, tentará infinitamente pegar o garfo a sua direita, se fome >= 0, e não conseguir pegar o garfo à direita, largará o garfo da esquerda e voltará a filosofar, se conseguir comer, o nível de fome soma em 1.

## Utilização
Para iniciar os filosofos, é necessário abrir 05 programas com os parâmetros "FILOSOFO1", "FILOSOFO2", "FILOSOFO3", "FILOSOFO4", "FILOSOFO5".

#### Obs.: Erro de filosofos duplicados não tratados.
