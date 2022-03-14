## Grupo
- Keny Lucas Souza
- Diego Queiroz

## Instruções de utilização
A implementação do alocador foi feita em C++ e um código para teste está em `main.cpp`.

### Compilação para teste
```shell
g++ alocaMain.cpp aloca.cpp -o aloca 
./aloca
```


# Alocador de Memória Pessoal# 
## Arquivos fonte: aloca.cpp e aloca.h ##

Neste trabalho, vocês farão o seu próprio alocador de memória, com um gerente de memória livre. Não é excitante?

Ele será bem simples: No início pedirá um valor N, e alocará N bytes com malloc mesmo. A partir daí, quem usar o alocador poderá pedir memória desta previamente alocada. Desta forma, cabe a ele gerenciar o espaço livre nesta memória, cuidar da segurança (tamanho/número mágico) e a política para escolher onde fazer cada alocação.

#### O alocador deve ter as seguintes funções implementadas: #### 

* Construtor*, que recebe o tamanho da memória a ser alocada e uma constante que diz qual a política de alocação (ver código)
* Aloca, que recebe um tamanho e retorna um ponteiro para a posição de memória deste tamanho que passe a ser utilizada.
* Verifica, que recebe um ponteiro e um offset, e verifica se a posição ponteiro+offset já foi previamente alocada, retornando um ponteiro para a posição desta região alocada se sim, 0 ou NULL se não.
* Libera, similar à free, libera a memória “alocada” em um ponteiro. Repare que ela não recebe o tamanho da região alocada.
Destrutor*, que libera as memórias alocadas.

*Construtor/Destrutor de C++ mesmo.

Para facilitar a vida de vocês, estou liberando no colabweb um arquivo .h já com os protótipos do alocado, para facilitar vossas vidas. Sigam ele à risca, pois utilizarei estes protótipos para testar seus métodos.

As alocações podem ser de até 65534 bytes, que é o maior unsigned short int.

__DICA IMPORTANTE:__ Nunca, NUNCA, faça cast diretamente de um vetor de char para outros tipos maiores e vice versa, que tem grande chance de dar erro de alinhamento. Utilize operações bitwise para guardar o short em um vetor de char.

__DICA IMPORTANTE 2:__ Não mexa no protótipo das funções do .h fornecido, no máximo inclua novas
