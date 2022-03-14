#include <iostream>

using namespace std;

// classe Bloco
class Bloco{
private:
public:
	int inicio;
	int tamanho;
	Bloco* prox;
	Bloco(int tamanho,int inicio){
		this->inicio = inicio;
		this->tamanho = tamanho;
		this->prox = NULL;
	}

	int obterValor(){
		return tamanho;
	}

	Bloco* obterProx(){
		return prox;
	}

	void setProx(Bloco* p){
		prox = p;
	}
};

// classe Lista
class Lista
{
private:
	Bloco* cabeca;
	Bloco* cauda;

public:

	Lista(int tamanho,int inicio)
	{
		cabeca = new Bloco(tamanho,inicio);
	}

	virtual ~Lista()
	{
		delete cabeca;
	}

    Bloco *prim() {
        return cabeca;
    }

	void mostrar()
	{
		cout << "\nImprimindo todos os elementos...\n";
		Bloco* c = cabeca;

		if(vazia())
			cout << "A lista NAO possui elementos!!\n";
		else
		{
			while(c)
			{
				cout << c->obterValor() << endl;
				c = c->obterProx();
			}
			cout << endl;
		}
	}

	bool vazia()
	{
		return (cabeca == NULL);
	}

    void inserir_ordenado(int inicio, int tamanho) 
    {
		Bloco* novo_Bloco = new Bloco(tamanho,inicio);

        Bloco* atual = cabeca;
		if(!atual || atual->inicio >= inicio)
		{
			novo_Bloco->setProx(atual);
			cabeca = novo_Bloco;
		}
		else
		{
            while (atual->prox && atual->prox->inicio < inicio)
                atual = atual->prox;
            novo_Bloco->setProx(atual->prox);
            atual->prox = novo_Bloco;
		}

		//aglutinar
		atual = prim();
		if(!atual)
		{
			return;
		}
		Bloco *prox = atual->obterProx();

		while(atual != NULL && prox != NULL)
		{
			if(atual->inicio + atual->tamanho == prox->inicio)//aglutina
			{
				atual->tamanho = atual->tamanho + prox->tamanho; 
				atual->setProx(prox->obterProx());
				//delete prox;

				prox = atual->obterProx();
				continue;
			}
			atual = atual->obterProx(); // proximo bloco
			prox = atual->obterProx();
		}
    }

	int tamanho()
	{
		if(vazia())
			return 0;

		Bloco* c = cabeca;
		int tam = 0;
		
		do
		{
			c = c->obterProx();
			tam++;
		}
		while(c);
		
		return tam;
	}

	bool existe(int tamanho)
	{
		Bloco* c = cabeca;
		
		while(c)
		{
			if(c->obterValor() == tamanho)
				return true;
			c = c->obterProx();
		}
		return false;
	}

    //inicio é o valor da posicao inicial do bloco no vetorzao de memoria
	void remove(int inicio)
	{
        Bloco* aux = cabeca, *ant;
        ant = aux;
		while (aux != NULL && aux->inicio != inicio){
            ant = aux;
            aux = aux->obterProx();
        }
        if (aux) {
            if (aux == cabeca) {
                cabeca = aux->obterProx();
            } else { // resto
                ant->setProx(aux->obterProx());
            }
            delete aux;
        }
	}
};