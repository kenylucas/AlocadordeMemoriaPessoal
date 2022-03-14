#include <iostream>
#include <string>
#include <fstream>
#include <utility> // std::pair
#include "../aloca.h"
using namespace std;

int main(int argc, char const *argv[])
{
    string fileName = argv[1];
    std::ofstream myFile;
    myFile.open("exit"+fileName+".csv");
    //numero de elementos lista vazio, média tamanho blocos, total espaço livre, total alocação sem sucesso
    myFile << "Id, Situacao, qntElementos, Média, espaçoVazio \n";
    FILE *arq = fopen(argv[1], "r");
    if (!arq)
    {
        printf("\nFalha na abertura do arquivo \"%s\".\n", argv[1]);
        return EXIT_FAILURE;
    }

    int tam, id, n, i;
    fscanf(arq, "%d %d\n%d\n", &tam, &id, &n);
    meualoc *alocador = new meualoc(tam, id);

    char **pids = (char **)malloc(sizeof(char *) * n);
    for (i = 0; i < n; i++)
        pids[i] = NULL;

    char op;
    for (i = 0; i < n; i++)
    {
        fscanf(arq, "%c %d", &op, &id);
        string valor = alocador->imprimeDadosArquivo();

        if (op == 'A') // alocar memória e salvar id do processo no arrays 'pids'
        {
            fscanf(arq, " %d", &tam);
            pids[id] = alocador->aloca(tam);
            if (pids[id])
            {
                myFile << id << ",alocado," << valor << "\n";
                // printf("%d: alocado %d\n", id, tam);
            }
            else
            {
                myFile << id << ",não alocado," << valor  << "\n";
                // printf("%d: não alocado %d\n", id, tam);
            }
        }
        else // liberar memoria do pid = id
        {
            tam = alocador->libera(pids[id]);
            if (tam)
            {
                myFile << id << ",liberado," << valor << "\n";
                // printf("%d: liberado %d\n", id, tam);
            }
            else
            {
                myFile << id << ",nada liberado," << valor << "\n";
                // printf("%d: nada liberado\n", id);
            }
        }
        fscanf(arq, "%*c");
    }
    alocador->imprimeDados();
    myFile.close();

    return 0;
}