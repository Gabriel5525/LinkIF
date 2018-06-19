#ifndef DISCIPLINA_H
#define DISCIPLINA_H
#include "Lista.h"
#include <string>


using namespace std;

class Disciplina
{
    public:
        Disciplina();
        int id;
        string nome;
        int totalFac;
        int totalDif;
        Lista idAlunosFac;
        Lista idAlunosDif;

        virtual ~Disciplina();

    protected:

    private:
};

#endif // DISCIPLINA_H
