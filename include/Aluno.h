#ifndef ALUNO_H
#define ALUNO_H
#include <string>
#include "Lista.h"


using namespace std;

class Aluno
{
    public:
        Aluno();
        int id;
        string nome;
        int ano;
        string curso;
        string email;
        string facilidade[10];
        int quantFac;
        int quantDif;
        int quantIndic;
        int quantRecebeu;
        string discRecebeu[3];
        string dificuldade[10];
        Lista indicadoPara;

        virtual ~Aluno();

    protected:

    private:
};

#endif // ALUNO_H
