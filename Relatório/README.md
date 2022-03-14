## Grupo
- Keny Lucas Souza 

## Instruções de utilização
A implementação do alocador foi feita em C++ e um código para teste está em `main.cpp`.

### Compilação para teste

arquivoDeTeste = workloadMem0, workloadMem1 ou workloadMem2. 
Onde: 
* workloadMem0: Política = Best Fit
* workloadMem1: Política = Next Fit
* workloadMem2: Política = First Fit
```shell
g++ parte2.cpp ../aloca.cpp -o p2
./p2 arquivoDeTeste
```

##### Faça um programa que utilize o alocador que vocês fizeram para rodar os workloads em anexo #####

#### O formato dos Workloads é o seguinte: ####
`
<TAMANHO DA MEMORIA> <ID_POLITICA_ESPACO>

<N_OPERACOES>
`

__ID_POLITICA_ESPACO__ pode ser:

`
0 - FIRST FIT
1 - BEST FIT
2 - NEXT FIT
`

O arquivo é seguido de N_OPERACOES linhas contendo as alocações e liberações feitas no workload. Cada operação pode ter o seguinte formato:

`
<LETRA_OP> <IDPONTEIRO> <VALOR(OPC)>
`

Onde LETRA_OP pode ser:

* A - Alocação
* F - Liberação (“free”) do espaço alocado

__ID_Ponteiro__ é um número inteiro e VALOR é usado apenas na alocação, e representa o total de memória que será alocado nesta operação.

Exemplo de arquivo de workload:

`
10000 0

6

A 1 100

A 2 10

F 2

A 3 1000

F 1

F 3
`

Onde se cria uma memória de 10000 bytes, se aloca 3 ponteiros 1, 2 e 3 com tamanhos (100,10,1000) e se libera os três (gerenciando o espaço livre dentro da estrutura).
