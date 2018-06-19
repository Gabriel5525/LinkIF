#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iomanip>
#include <cstddef>
#include <time.h>
#include <algorithm>
#include "Aluno.h"
#include "Lista.h"
#include "Celula.h"
#include "Disciplina.h"
#include <vector>

using namespace std;



void insereListaDisciplina(Disciplina vetorDisc[], Aluno novo,int cont, int tam, int id)
{

    if(id==1)
    {

        for(int i=0; i<cont; i++)
        {
            for(int j=0; j<tam; j++)
            {
                if(novo.facilidade[i]==vetorDisc[j].nome)
                {
                    Celula* c= new Celula();
                    c->id=novo.id;
                    c->nome=novo.nome;
                    vetorDisc[j].idAlunosFac.inserirAoFinal(c);

                    break;
                }
            }
        }
    }
    else
    {
        for(int i=0; i<cont; i++)
        {
            for(int j=0; j<tam; j++)
            {
                if(novo.dificuldade[i]==vetorDisc[j].nome)
                {
                    Celula* c= new Celula();
                    c->id=novo.id;
                    c->nome=novo.nome;
                    vetorDisc[j].idAlunosDif.inserirAoFinal(c);

                    break;
                }
            }
        }
    }
}

bool verificaDisiciplina(Disciplina vetorDisc[], string nome, int tam, int id)
{

    for(int i=0; i<tam; i++)
    {
        if(nome==vetorDisc[i].nome)
        {

            if(id==1)//facilidade
            {
                vetorDisc[i].totalFac++;
            }
            else//dificuldade
            {
                vetorDisc[i].totalDif++;
            }
            return false;
        }
    }

    Disciplina* nova = new Disciplina();

    if(id==1)//facilidade
    {
        nova->totalFac=1;
    }
    else//dificuldade
    {
        nova->totalDif=1;
    }
    vetorDisc[tam]=*nova;

    return true;
}

void leFacilidades(Disciplina vetorDisc[],Aluno vetorAlunos[], int &contDisc)
{
    string linha, materia;
    int contAlunos=0;
    ifstream reader;

    reader.open("facilidades2.txt");

    while(!reader.eof())
    {
        int contLinha=0, contFaci=0, aux=0;
        materia="";
        getline(reader,linha,'\n');

        while(aux<linha.size())
        {
            while (linha[contLinha]!=',')
            {
                materia+=linha[contLinha];
                contLinha++;
                aux++;
            }

            if(verificaDisiciplina(vetorDisc,materia,contDisc,1))//se for true ele grava o nome e id da disciplina uma vez
            {
                vetorDisc[contDisc].nome=materia;
                vetorDisc[contDisc].id=contDisc;

                contDisc++;
            }
            vetorAlunos[contAlunos].facilidade[contFaci]=materia;

            materia="";
            contFaci++;
            contLinha++;
            aux++;
        }
        vetorAlunos[contAlunos].quantFac=contFaci;
        insereListaDisciplina(vetorDisc,vetorAlunos[contAlunos],contFaci,contDisc,1);
        contAlunos++;
    }
    reader.close();
}

int leDificuldades(Disciplina vetorDisc[], Aluno vetorAlunos[], int &contDisc)
{

    string linha, materia;
    int contAlunos=0;
    ifstream reader;

    reader.open("dificuldades2.txt");

    while(!reader.eof())
    {
        int contLinha=0, contDif=0, aux=0;
        materia="";
        getline(reader,linha,'\n');

        while(aux<linha.size())
        {
            while (linha[contLinha]!=',')
            {
                materia+=linha[contLinha];
                contLinha++;
                aux++;
            }
            if(verificaDisiciplina(vetorDisc,materia,contDisc,2))//se for true ele grava o nome e id da disciplina uma vez
            {
                vetorDisc[contDisc].nome=materia;
                vetorDisc[contDisc].id=contDisc;

                contDisc++;
            }
            vetorAlunos[contAlunos].dificuldade[contDif]=materia;

            materia="";
            contDif++;
            contLinha++;
            aux++;
        }
        vetorAlunos[contAlunos].quantDif=contDif;
        insereListaDisciplina(vetorDisc,vetorAlunos[contAlunos],contDif,contDisc,2);
        contAlunos++;
    }
    reader.close();
}

void leArquivo(Disciplina vetorDisc[], Aluno vetorAlunos[],int &contAlunos, int &contDisc)
{
    ifstream reader;
    reader.open("linkIF.txt");

    if(!reader)
    {
        cout << "\nImpossível encontrar o arquivo.";
        reader.close();
    }
    else
    {
        Aluno* alguem = new Aluno();
        string codigo, nome, ano, curso, email;

        while(!reader.eof())
        {
            getline(reader,codigo,';');
            codigo.erase(remove(codigo.begin(), codigo.end(), ' '), codigo.end());
            alguem->id=atoi(codigo.c_str());

            getline(reader,nome,';');
            alguem->nome=nome;

            getline(reader,ano,';');
            ano.erase(remove(ano.begin(), ano.end(), ' '), ano.end());
            alguem->ano=atoi(ano.c_str());

            getline(reader,curso,';');
            alguem->curso=curso;

            getline(reader,email,';');
            email.erase(remove(email.begin(), email.end(), ' '), email.end());
            alguem->email=email;

            vetorAlunos[contAlunos]=*alguem;

            contAlunos++;

        }

        reader.close();
        contAlunos--;

        leFacilidades(vetorDisc,vetorAlunos,contDisc);
        leDificuldades(vetorDisc,vetorAlunos,contDisc);

        contDisc--;

    }
}

void imprimirFacilidade(Aluno vetorAlunos[], int posicaoVetor)
{
    for(int j=0; j<10; j++)
    {
        cout<<"Facilidade "<<j+1<<": "<<vetorAlunos[posicaoVetor].facilidade[j]<<endl;
    }
}

void imprimirDificuldade(Aluno vetorAlunos[], int posicaoVetor)
{
    for(int j=0; j<10; j++)
    {
        cout<<"Dificuldade "<<j+1<<": "<<vetorAlunos[posicaoVetor].dificuldade[j]<<endl;
    }
}

void imprimir(Aluno vetorAlunos[], int tam)
{
    for(int i=0; i<tam; i++)
    {
        cout<<"Codigo : "<<vetorAlunos[i].id<<endl;
        cout<<"Nome : "<<vetorAlunos[i].nome<<endl;
        cout<<"Ano : "<<vetorAlunos[i].ano<<endl;
        cout<<"Curso : "<<vetorAlunos[i].curso<<endl;
        cout<<"E-mail : "<<vetorAlunos[i].email<<endl;
        cout<<"_______________________"<<endl;
        imprimirFacilidade(vetorAlunos,i);
        cout<<"_______________________"<<endl;
        imprimirDificuldade(vetorAlunos,i);
        cout<<endl;
    }
}

void gerarParceria(Disciplina vetorDisc[], Aluno vetorAlunos[], int tamAlunos, int tamDisc)
{

    for(int i=0; i<tamAlunos; i++)
    {
        for(int j=0; j<vetorAlunos[i].quantFac; j++)
        {
            for(int k=0; k<tamDisc; k++)
            {
                if(vetorDisc[k].totalDif!=0 && vetorDisc[k].totalFac!=0 && vetorAlunos[i].facilidade[j]==vetorDisc[k].nome)
                {
                    for(int indice=0; indice<vetorDisc[k].totalDif; indice++)
                    {
                        //cout<<"chegou "<<vetorDisc[k].idAlunosDif.pesquisarIndice(indice)<<" : "<<vetorDisc[k].nome<<endl;
                        Celula* c= new Celula();
                        c->id=vetorDisc[k].idAlunosDif.pesquisarIndice(indice);
                        c->nome=vetorDisc[k].nome;
                        vetorAlunos[i].indicadoPara.inserirAoFinal(c);
                        vetorAlunos[i].quantIndic++;

                    }
                }
            }
        }
    }

}

string getNomeAluno(Aluno vetorAlunos[],int tam, int id)
{

    for(int i=0; i<tam; i++)
    {
        if(vetorAlunos[i].id==id)
        {
            return vetorAlunos[i].nome;
        }
    }
}

int main()
{
    setlocale(LC_ALL,"Portuguese");

    int contDisc=0, contAlunos=0;

    Disciplina vetorDisc[100];
    Aluno vetorAlunos[138];

    ofstream gravar;
    gravar.open("Parceiros.txt");

    leArquivo(vetorDisc,vetorAlunos,contAlunos,contDisc);

    gerarParceria(vetorDisc,vetorAlunos,contAlunos,contDisc);

    for(int i=0; i<contAlunos; i++)
    {
        int cont=0;
        gravar<<"\nAluno:"<<vetorAlunos[i].nome;
        gravar<<"\nIndicado Para:\n\n";

        for(int j=0; j<vetorAlunos[i].quantIndic; j++)
        {
            gravar<<vetorAlunos[i].indicadoPara.pesquisarIndiceString(j)<<" :"<<getNomeAluno(vetorAlunos,contAlunos,vetorAlunos[i].indicadoPara.pesquisarIndice(j))<<"\n";
        }

    }








    return 0;
}
