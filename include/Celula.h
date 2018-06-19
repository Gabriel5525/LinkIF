#ifndef CELULA_H
#define CELULA_H
#include <string>

using namespace std;

class Celula
{
    public:
        Celula();
        int id;
        Celula* prox;
        string nome;
        virtual ~Celula();

    protected:

    private:
};

#endif // CELULA_H
