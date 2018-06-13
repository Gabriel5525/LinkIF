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


using namespace std;


struct Lista;

struct aluno
{
    int codigo;
    string nome;
    int ano;
    string curso;
    string email;
    string facilidade[10];
    string dificuldade[10];
    int quantIndic=0;
    Lista* indicado;
    string materiaIndica;

};

struct Celula
{
    aluno novo;
    Celula *prox;
};

struct Lista
{
    Celula* primeiro;

    bool vazia()
    {
        return (primeiro == NULL);
    }

    void inserirAoFinal(Celula* c)
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

    void imprimir()
    {
        Celula* aux = primeiro;
        while(aux != NULL)
        {
            cout<<aux->novo.nome<<endl;
            aux = aux->prox;
        }
    }

    Celula* pesquisar(aluno v)
    {
        if(vazia())
            return NULL;
        else
        {
            Celula* aux = primeiro;
            while(aux != NULL && aux->novo.codigo != v.codigo)
            {
                aux = aux->prox;
            }
            return aux;
        }
    }

    Celula* pesquisarIndice(int v)
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
            return aux;
        }
    }
};

struct disciplina
{
    int codigo;
    string nome;
    int rankFacilidade=0;
    Lista listaFac;
    int rankDificuldade=0;
    Lista listaDif;
    double proporcao=0.0;

};

void insereListaDisciplina(disciplina lista[], aluno novo, int tam, int id)
{

    if(id==1)
    {
        for(int i=0; i<10; i++)
        {
            for(int j=0; j<tam; j++)
            {
                if(novo.facilidade[i]==lista[j].nome)
                {
                    Celula* c= new Celula();
                    c->novo=novo;
                    lista[j].listaFac.inserirAoFinal(c);

                    break;
                }
            }
        }
    }
    else
    {
        for(int i=0; i<10; i++)
        {
            for(int j=0; j<tam; j++)
            {
                if(novo.dificuldade[i]==lista[j].nome)
                {
                    Celula* c= new Celula();
                    c->novo=novo;
                    lista[j].listaDif.inserirAoFinal(c);

                    break;
                }
            }
        }
    }

}

bool verifica(disciplina vetor[], string nome, int tam, int id)
{
    for(int i=0; i<tam; i++)
    {
        if(nome==vetor[i].nome)
        {

            if(id==1)
            {
                vetor[i].rankFacilidade++;
            }
            else
            {
                vetor[i].rankDificuldade++;
            }
            return false;
        }
    }

    if(id==1)
    {
        vetor[tam].rankFacilidade=1;
    }
    else
    {
        vetor[tam].rankDificuldade=1;
    }
    return true;
}

int leFacilidades(disciplina discip[],aluno vetor[], int tam)
{
    string linha, materia;
    int j=0;
    ifstream reader;

    reader.open("facilidades2.txt");

    while(!reader.eof())
    {
        int i=0, k=0, aux=0;
        materia="";
        getline(reader,linha,'\n');


        while(aux<linha.size())
        {
            while (linha[i]!=',')
            {
                materia+=linha[i];
                i++;
                aux++;
            }
            if(verifica(discip,materia,tam,1))
            {
                discip[tam].nome=materia;
                discip[tam].codigo=tam;

                tam++;
            }

            vetor[j].facilidade[k]=materia;
            materia="";

            k++;
            i++;
            aux++;
        }
        insereListaDisciplina(discip,vetor[j],tam,1);
        j++;
    }
    reader.close();
    return tam;
}

int leDificuldades(disciplina discip[], aluno vetor[], int tam)
{

    string linha, materia;
    int j=0;
    ifstream reader;

    reader.open("dificuldades2.txt");

    while(!reader.eof())
    {
        int i=0, k=0, aux=0;
        materia="";
        getline(reader,linha,'\n');

        while(aux<linha.size())
        {
            while (linha[i]!=',')
            {
                materia+=linha[i];
                i++;
                aux++;
            }
            if(verifica(discip,materia,tam,2))
            {
                discip[tam].nome=materia;
                discip[tam].codigo=tam;
                tam++;
            }

            vetor[j].dificuldade[k]=materia;
            materia="";

            k++;
            i++;
            aux++;
        }
        insereListaDisciplina(discip,vetor[j],tam,2);
        j++;
    }

    reader.close();
    return tam;
}

int leArquivo(disciplina discip[], aluno vetor[])
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
        aluno alguem;
        string codigo, nome, ano, curso, email, facilidade[9], dificuldade[9];
        int tam=0;

        while(!reader.eof())
        {
            getline(reader,codigo,';');
            codigo.erase(remove(codigo.begin(), codigo.end(), ' '), codigo.end());
            alguem.codigo=atoi(codigo.c_str());

            getline(reader,nome,';');
            alguem.nome=nome;

            getline(reader,ano,';');
            ano.erase(remove(ano.begin(), ano.end(), ' '), ano.end());
            alguem.ano=atoi(ano.c_str());

            getline(reader,curso,';');
            alguem.curso=curso;

            getline(reader,email,';');
            email.erase(remove(email.begin(), email.end(), ' '), email.end());
            alguem.email=email;

            vetor[tam]=alguem;

            tam++;
        }
        int tam2;
        reader.close();
        tam2=leFacilidades(discip,vetor,0);
        tam2=leDificuldades(discip,vetor,tam2);

        return tam2;
    }
}

void imprimirFacilidade(aluno vetor[], int tam, int i)
{
    for(int j=0; j<10; j++)
    {
        if(vetor[i].facilidade[j].size()>4)
        {
            cout<<"Facilidade "<<j+1<<": "<<vetor[i].facilidade[j]<<endl;
        }
    }
}

void imprimirDificuldade(aluno vetor[], int tam, int i)
{
    for(int j=0; j<10; j++)
    {
        if(vetor[i].facilidade[j].size()>4)
        {
            cout<<"Dificuldade "<<j+1<<": "<<vetor[i].dificuldade[j]<<endl;
        }
    }
}

void imprimir(aluno vetor[], int tam)
{
    for(int i=0; i<tam; i++)
    {
        cout<<"Codigo : "<<vetor[i].codigo<<endl;
        cout<<"Nome : "<<vetor[i].nome<<endl;
        cout<<"Ano : "<<vetor[i].ano<<endl;
        cout<<"Curso : "<<vetor[i].curso<<endl;
        cout<<"E-mail : "<<vetor[i].email<<endl;
        cout<<"_______________________"<<endl;
        imprimirFacilidade(vetor,tam,i);
        cout<<"_______________________"<<endl;
        imprimirDificuldade(vetor,tam,i);
        cout<<endl;
    }
}

void shellSortString(string materias[], int tam)
{

    int i = (tam- 1) / 2;
    int chave, k;
    string aux;

    while(i != 0)
    {
        do
        {
            chave = 1;
            for(k = 0; k < tam - i; ++k)
            {
                if(materias[k]> materias[k+i])
                {
                    aux = materias[k];
                    materias[k] = materias[k+i];
                    materias[k+i] = aux;
                    chave = 0;
                }
            }
        }
        while(chave == 0);
        i = i / 2;
    }
}

void shellSortNum(disciplina vetor[], int tam, int id)
{

    int i = (tam- 1) / 2;
    int chave, k;
    disciplina aux;

    if(id==1)  //rank de facilidades
    {
        while(i != 0)
        {
            do
            {
                chave = 1;
                for(k = 0; k < tam - i; ++k)
                {
                    if(vetor[k].rankFacilidade> vetor[k+i].rankFacilidade)
                    {
                        aux = vetor[k];
                        vetor[k] = vetor[k+i];
                        vetor[k+i] = aux;
                        chave = 0;
                    }
                }
            }
            while(chave == 0);
            i = i / 2;
        }
    }
    else if(id==2) //rank dificuldades
    {

        while(i != 0)
        {
            do
            {
                chave = 1;
                for(k = 0; k < tam - i; ++k)
                {
                    if(vetor[k].rankDificuldade> vetor[k+i].rankDificuldade)
                    {
                        aux = vetor[k];
                        vetor[k] = vetor[k+i];
                        vetor[k+i] = aux;
                        chave = 0;
                    }
                }
            }
            while(chave == 0);
            i = i / 2;
        }


    }
    else //rank proporção
    {

        while(i != 0)
        {
            do
            {
                chave = 1;
                for(k = 0; k < tam - i; ++k)
                {
                    if(vetor[k].proporcao> vetor[k+i].proporcao)
                    {
                        aux = vetor[k];
                        vetor[k] = vetor[k+i];
                        vetor[k+i] = aux;
                        chave = 0;
                    }
                }
            }
            while(chave == 0);
            i = i / 2;
        }


    }
}

void gravarDiscFaci(disciplina vetor[], int tam)
{

    ofstream gravar;
    gravar.open("RankFacilidades.txt");

    for(int i=tam-1; i>=0; i--)
    {
        if(vetor[i].nome.size()>3 && vetor[i].rankFacilidade!=0)
        {
            gravar<<vetor[i].nome<<" : "<<vetor[i].rankFacilidade<<"\n";
            vetor[i].proporcao=vetor[i].rankDificuldade/vetor[i].rankFacilidade;
        }
    }
    gravar.close();

}

void gravarDiscDif(disciplina vetor[], int tam)
{

    ofstream gravar;
    gravar.open("RankDificuldades.txt");

    for(int i=tam-1; i>=0; i--)
    {
        if(vetor[i].nome.size()>3  && vetor[i].rankDificuldade!=0)
        {
            gravar<<vetor[i].nome<<" : "<<vetor[i].rankDificuldade<<"\n";
        }
    }
    gravar.close();
}

void incrementaIndic(aluno vetor[], int tam, int id,string nome)
{

    for(int i=0;i<tam;i++){
        if(vetor[i].codigo==id){
            vetor[i].quantIndic++;
            vetor[i].materiaIndica=nome;
           /* Celula* c= new Celula();
            c->novo=indica;
            vetor[i].indicado->inserirAoFinal(c);*/
        }
    }
}

void gravarRank(disciplina vetorD[], int tam)
{
    shellSortNum(vetorD,tam,1);
    gravarDiscFaci(vetorD,tam);

    shellSortNum(vetorD,tam,2);
    gravarDiscDif(vetorD,tam);
}



void gerarParceria(disciplina vetorD[], aluno vetorA[], int tam)
{

    int cont=0, k=0, aux;

    for(int i=tam-1; i>=0; i--)
    {

        if(vetorD[i].rankFacilidade==0 || vetorD[i].rankDificuldade==0){

        }
        else{
            cout<<"\n--"<<vetorD[i].nome<<"--\n"<<endl;
        for(int j=0;j<vetorD[i].rankFacilidade;j++){



            cout<<"\nAluno: "<<vetorD[i].listaFac.pesquisarIndice(j)->novo.nome<<" : ";

                incrementaIndic(vetorA,141,vetorD[i].listaFac.pesquisarIndice(j)->novo.codigo,vetorD[i].nome);
                aux=vetorA[vetorD[i].listaFac.pesquisarIndice(j)->novo.codigo-1].quantIndic;
               // cout<<aux<<" -- "<<vetorA[i].materiaIndica<<endl;
                cout<<aux<<"\n"<<endl;

            k=cont;

            while(cont<vetorD[i].proporcao+k && cont!=vetorD[i].rankDificuldade){


                if(aux<3){

                    //incrementaIndic(vetorA,141,vetorD[i].listaFac.pesquisarIndice(j)->novo.codigo/*,vetorD[i].listaDif.pesquisarIndice(k)->novo*/);
                    cout<<"Indicados: "<<vetorD[i].listaDif.pesquisarIndice(cont)->novo.nome<<endl;
                        cont++;

                    }
                    else{
                        break;
                    }

                }
            }
            cont=0;
        }
    }


}

int main()
{
    setlocale(LC_ALL,"Portuguese");

    aluno vetor[150];
    int tam, cont=0;
    disciplina vetorD[100];


    tam=leArquivo(vetorD,vetor);
    gravarRank(vetorD,tam);

   //ofstream gravar;
   // gravar.open("test.txt");

    shellSortNum(vetorD,tam,3);

   /* for(int i=0; i<tam; i++)
    {
        cout<<endl;
        cout<<vetorD[i].nome<<":"<< vetorD[i].proporcao<<endl;
        cout<<"\nFacilidade:"<<endl;
        cout<<"___________________"<<endl;
        vetorD[i].listaFac.imprimir();
        cout<<"___________________"<<endl;
        cout<<"\nDificuldade:"<<endl;
        cout<<"___________________"<<endl;
        vetorD[i].listaDif.imprimir();


    }*/
    gerarParceria(vetorD,vetor,tam);

    for(int i=0;i<141;i++){
        //cout<<vetor[i].nome <<": "<<vetor[i].quantIndic<<endl;
    }



    //imprimir(vetor,141);


    return 0;
}
