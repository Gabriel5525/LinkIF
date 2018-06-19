#ifndef LISTA_H
#define LISTA_H
#include "Celula.h"
#include <string>

using namespace std;


class Lista
{
    public:
        Lista();
        Celula* primeiro;
        bool vazia();
        void inserirAoFinal(Celula* c);
        Celula* pesquisar(int v);
        int pesquisarIndice(int v);
        string pesquisarIndiceString(int v);
        void imprimir();
        static void lerArq();

        virtual ~Lista();

    protected:

    private:
};

#endif // LISTA_H
