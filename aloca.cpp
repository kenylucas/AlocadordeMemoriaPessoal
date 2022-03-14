#include <cstdlib>
#include "aloca.h"

meualoc::meualoc(int tamanhoMemoria, int politicaMem)
{
    memoria = (char *)malloc(tamanhoMemoria);
    tamanho = tamanhoMemoria;
    politica = politicaMem;
    livres = new Lista(tamanho, 0); //lista de livres
    posicao = livres->prim();
}

char *meualoc::aloca(unsigned short int tamanho)
{
    Bloco *bloco;
    tamanho += 4; //cabeçalho de 4 bytes

    // policitas
    if (politica == BESTFIT)
    {
        Bloco *melhor = NULL;
        bloco = livres->prim();
        while (bloco != NULL) //percorrer a lista toda
        {
            if (bloco->tamanho >= tamanho)
            {       
                if (melhor == NULL || melhor->tamanho > bloco->tamanho)
                {
                    melhor = bloco;
                }
            }
            bloco = bloco->obterProx(); //proximo bloco
        }
        if (melhor == NULL)
        { //não achoy
            return NULL;
        }
        else
        { //achou o melhor
            int pos = melhor->inicio;
            if (melhor->tamanho == tamanho)
            {                        //se for igual, remover o bloco da lista de livres
                livres->remove(pos); //remover da lista apenas o Bloco "aux"
            }
            else
            { //se for maior, reduzir o tamanho do bloco "aux" na lista de livres
                melhor->inicio += tamanho;
                melhor->tamanho -= tamanho;
            }
            //Bitwise
            tamanho -= 4; //remover tamanho do cabeçalho, pois já será escrito na memória
            memoria[pos++] = (MAGICNUMBER >> 8) & 0xFF;
            memoria[pos++] = MAGICNUMBER & 0xFF;
            memoria[pos++] = (tamanho >> 8) & 0xFF;
            memoria[pos++] = tamanho & 0xFF;
            return &memoria[pos]; //retornar ponteiro para memoria alocada 4 = 2 / 2
        }
    }
    else if (politica == NEXTFIT)
    {
        bloco = posicao;
        while (bloco != NULL && bloco->tamanho < tamanho) //tamanho insuficiente
        {
            bloco = bloco->obterProx(); //proximo bloco
        }
        if (bloco == NULL)
        {
            bloco = livres->prim();
            while (bloco != NULL && bloco->tamanho < tamanho) //verifica tamanho insuficiente
            {
                bloco = bloco->obterProx(); //proximo bloco
            }
            if (bloco == NULL)
            {
                return NULL;
            }
        }
        if (bloco)
        { // tamanho suficiente
            int pos = bloco->inicio;
            if (bloco->tamanho == tamanho)
            {                                  //se for igual, remover o bloco da lista de livres
                livres->remove(bloco->inicio); //remover da lista apenas o Bloco "aux"
                posicao = bloco->obterProx() ? bloco->obterProx() : livres->prim();
            }
            else
            { // se for maior, reduzir o tamanho do bloco "aux" na lista de livres
                bloco->inicio = bloco->inicio + tamanho;
                bloco->tamanho -= tamanho;
                posicao = bloco;
            }
            //Bitwise
            tamanho -= 4; //remover tamanho do cabeçalho, pois já será escrito na memória
            memoria[pos++] = (MAGICNUMBER >> 8) & 0xFF;
            memoria[pos++] = MAGICNUMBER & 0xFF;
            memoria[pos++] = (tamanho >> 8) & 0xFF;
            memoria[pos++] = tamanho & 0xFF;
            return &memoria[pos]; //retornar ponteiro para memoria alocada
        }
        return NULL;
    }
    else
    {
        bloco = livres->prim();
        while (bloco != NULL && bloco->tamanho < tamanho) //tamanho insuficiente
        {
            bloco = bloco->obterProx(); //proximo bloco
        }
        if (bloco == NULL)
        {
            return NULL;
        }
        else
        { //tamanho suficiente
            int pos = bloco->inicio;
            if (bloco->tamanho == tamanho)
            {                                  //se for igual, remover o bloco da lista de livres
                livres->remove(bloco->inicio); //remover da lista apenas o Bloco "aux"
            }
            else
            { //se for maior, reduzir o tamanho do bloco "aux" na lista de livres
                bloco->inicio = bloco->inicio + tamanho;
                bloco->tamanho -= tamanho;
            }
            //Bitwise
            tamanho -= 4; //remover tamanho do cabeçalho, pois já será escrito na memória
            memoria[pos++] = (MAGICNUMBER >> 8) & 0xFF;
            memoria[pos++] = MAGICNUMBER & 0xFF;
            memoria[pos++] = (tamanho >> 8) & 0xFF;
            memoria[pos++] = tamanho & 0xFF;
            return &memoria[pos]; //retornar ponteiro para memoria alocada
        }
    }
}

char *meualoc::verifica(char *ponteiro, int posicao)
{
    char *cabecalho = ponteiro - 4;
    if (cabecalho < memoria || ponteiro > memoria + tamanho)
        return NULL; //fora da memoria

    unsigned short magic = ((cabecalho[0] & 0xFF) << 8) + (cabecalho[1] & 0xFF);
    unsigned short tam = ((cabecalho[2] & 0xFF) << 8) + (cabecalho[3] & 0xFF);

    if (magic == MAGICNUMBER && tam >= posicao)
        return ponteiro;
    return NULL;
}

int meualoc::libera(char *ponteiro)
{
    char *cabecalho = ponteiro - 4;
    if (!ponteiro || cabecalho < memoria || ponteiro > memoria + tamanho)
        return 0; //fora da memoria

    unsigned short magic = ((cabecalho[0] & 0xFF) << 8) + (cabecalho[1] & 0xFF);
    if (magic == MAGICNUMBER)
    {
        unsigned short tam = ((cabecalho[2] & 0xFF) << 8) + (cabecalho[3] & 0xFF) + 4; //+ 4 do cabecalho
        livres->inserir_ordenado(cabecalho - memoria,tam);
        for (int i = 0; i < 4; i++)
        {
            cabecalho[i] = 0;
        }
        return tam;
    }
    return 0;
}

void meualoc::imprimeDados()
{
    Bloco *aux;
    int cont = 0, maior, medio = 0;
    aux = livres->prim();
    maior = aux->tamanho;
    while (aux != NULL) //percorrer a lista toda
    {
        cont += 1;
        medio += aux->tamanho;
        if (aux->tamanho > maior)
        {
            maior = aux->tamanho;
        }
        aux = aux->obterProx();
    }
    medio = medio / cont;
    cout << "Quantidade Elementos - Lista Vazio: " << cont << ". Maior Bloco - Lista Vazio: " << maior << ". Média dos Blocos - Lista Vazio: " << medio << "." << endl;
}

string meualoc::imprimeDadosArquivo()
{
    Bloco *aux;
    int cont = 0, maior, medio = 0;
    aux = livres->prim();
    maior = aux->tamanho;
    while (aux != NULL) //percorrer a lista toda
    {
        cont += 1;
        medio += aux->tamanho;
        if (aux->tamanho > maior)
        {
            maior = aux->tamanho;
        }
        aux = aux->obterProx();
    }
    int totalEspacoLivre = medio;
    medio = medio / cont;
    string valor = to_string(cont) + "," + to_string(medio) + "," + to_string(totalEspacoLivre);
    //cout << "elementosLitaVazio: " << cont << ", mediaTamanhoBlocos: " << medio << ", totalEspacoLivre: " << totalEspacoLivre << endl;
    return valor;
}
