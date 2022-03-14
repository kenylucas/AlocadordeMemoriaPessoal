#include "aloca.h"
#define MEMORIA 10000
#define POLITICA 2 //next fit

int main(int argc, char const *argv[])
{
    meualoc* alocador = new meualoc(MEMORIA, POLITICA);

    char *memoria1 = alocador->aloca(20);
    char *memoria2 = alocador->aloca(30);
    char *memoria3 = alocador->aloca(40);
    alocador->libera(memoria2);
    char *memoria4 = alocador->aloca(10);

    alocador->imprimeDados();//imprime dados da lista de vazios
}


