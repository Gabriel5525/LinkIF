#include "Lista.h"
#include <iostream>
#include <string>

using namespace std;

Lista::Lista()
{
    primeiro=NULL;
}

bool Lista::vazia()
{
    return (primeiro == NULL);
}


void Lista::inserirAoFinal(Celula* c)
{
    if(vazia())
    {
        primeiro = c;
    }
    else
    {
        Celula* aux = primeiro;
        while(aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = c;

    }
}

void Lista::imprimir()
{
    int contInf=0,contAdm=0,contEle=0;
    Celula* aux = primeiro;
    while(aux != NULL)
    {
        cout<<aux->id<<endl;
        aux = aux->prox;
    }
}
Celula* Lista::pesquisar(int v)
{
    if(vazia())
        return NULL;
    else
    {
        Celula* aux = primeiro;
        while(aux != NULL && aux->id != v)
        {
            aux = aux->prox;
        }
        return aux;
    }
}

int Lista::pesquisarIndice(int v)
    {
        if(vazia())
            return NULL;
        else
        {
            Celula* aux = primeiro;
            int cont=0;
            while(aux != NULL && cont != v)
            {
                aux = aux->prox;
                cont++;
            }
            return aux->id;
        }
    }

string Lista::pesquisarIndiceString(int v)
    {
        if(vazia())
            return NULL;
        else
        {
            Celula* aux = primeiro;
            int cont=0;
            while(aux != NULL && cont != v)
            {
                aux = aux->prox;
                cont++;
            }
            return aux->nome;
        }
    }


Lista::~Lista()
{
    //dtor
}
