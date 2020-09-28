#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#define N 5
#define TAMRAND 5000 //Tempo de até 5s para aleatorio

DWORD resultEsperaGarfo;
HANDLE garfo[N];

//variáveis de controle de nível de fome
//tentativa de evitar/dificultar starvation e deadlock
int nvFome = 0;

//variáveis do nº do garfo na mesa
int esq;
int dir;

int aleatorio();
void comer();
void filosofar();

int main(int argc, char** argv)
{
    //variável numero do filosofo
    int nrFilosofo;

    //variavel definindo while
    int run = 1;

    //CRIANDO OS GARFOS
    for(int i = 0; i <= N; i++)
    {
        char str[8] = "garfo_";
        char val[3];
        itoa(i, val, 10);
        strcat(str, val);

        // criação dos garfos
        garfo[i] = CreateSemaphore(NULL,
        1, //valor inicial (vagas)
        1, //tamanho máximo
        str); //nome pra diferenciação
    }

    //Argumento de entrada e dando numero a filosofos
    if(argc>1)
	{
		if(strcmp(argv[1],"FILOSOFO1")==0)
			nrFilosofo = 0;

		if(strcmp(argv[1],"FILOSOFO2")==0)
			nrFilosofo = 1;

        if(strcmp(argv[1],"FILOSOFO3")==0)
			nrFilosofo = 2;

        if(strcmp(argv[1],"FILOSOFO4")==0)
			nrFilosofo = 3;

        if(strcmp(argv[1],"FILOSOFO5")==0)
			nrFilosofo = 4;

        //definindo valores dos garfos que o filosofo pode pegar
        esq = (nrFilosofo+4)%N;
        dir = (nrFilosofo+1)%N;
	}
	else
	{
		printf("Uso invalido. Informe o tipo [FILOSOFO1|FILOSOFO2|FILOSOFO3|FILOSOFO4|FILOSOFO5]\n");
		run = 0;
	}

    while(run)
    {
        //aqui que a mágica acontece
        filosofar();
        printf("O filosofo esta faminto...\n");
        comer();
    }

    return 0;
}

int aleatorio()
{
    srand(time(NULL));
    return rand()%TAMRAND - 1000; //aleatório de 1 a 5 segundos
    //return 1000;
}

void comer()
{
    printf("O filosofo esta tentando pegar o garfo da esquerda...\n");
    resultEsperaGarfo = WaitForSingleObject(garfo[esq], INFINITE);
    printf("O filosofo esta tentando pegar o garfo da direita\n");
    if(nvFome < 0)
    {

        resultEsperaGarfo = WaitForSingleObject(garfo[dir], INFINITE);
	    comendo();
    }
    else
    {
        resultEsperaGarfo = WaitForSingleObject(garfo[dir], 0);

        switch(resultEsperaGarfo)
        {
            case WAIT_OBJECT_0: //O filósofo comerá
                comendo();
                break;

            case WAIT_TIMEOUT: //O filósofo não está com tanta fome, vai voltar a filosofar por um tempo
                nvFome -= 1;
                ReleaseSemaphore(garfo[esq], 1, NULL);
                printf("O filosofo nao esta com tanta fome, vai soltar o garfo e vai tentar comer depois...\n");
                break;
        }
    }
}

void filosofar()
{
    printf("O filosofo esta filosofando...\n");
    Sleep(aleatorio()); //tempo que o filosofo estará filosofando antes de sentir fome
}

void comendo()
{
	nvFome += 1;
	printf("O filosofo esta comendo...\n");
	Sleep(aleatorio()); // valor aleatório pro filosofo comer
	ReleaseSemaphore(garfo[esq], 1, NULL);
	ReleaseSemaphore(garfo[dir], 1, NULL);	
}
