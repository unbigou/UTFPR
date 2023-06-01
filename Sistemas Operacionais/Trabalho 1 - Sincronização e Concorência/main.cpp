#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <random>

using namespace std;

const int QTT_ALUNOS = 3;
const int QTT_MONITORES = 1;
const int TAM_DOS_GRUPOS = 2;

sem_t sala_vazia;
sem_t vagas_na_sala;
sem_t monitores_em_sala;

void* Alunos_de_SO(void* id)
{
    int id_aluno = *(int*) id;

    // Baguio de sinal aqui.......

    while(1)
    {
		sem_wait(&vagas_na_sala);	//Aluno espera por vaga na sala, ou subtrai a quandidade de vagas caso entre.
		
		printf("[Aluno %d entrou na sala]\n", id_aluno);
		while(1)
		{
			printf("[Aluno %d está estudando]\n", id_aluno);	 sleep(3);

			if(rand() % 5 == 1)	//Chance do aluno sair da sala
			{   
				sem_post(&vagas_na_sala);	printf("[Aluno %d saiu da sala]\n", id_aluno);
				break;
			}
		}
		break;
    }
    pthread_exit(NULL);
}


void* Estudantes_Monitores(void* id)
{
    int aux_mtr, aux_aln;
    int id_monitor = *(int*) id;
    
    // Aqui é pra ter o sinal......

    sem_post(&monitores_em_sala);   printf("[Monitor %d entrou na sala]\n", id_monitor);

	for(int i = 0; i < TAM_DOS_GRUPOS; i++) 
		sem_post(&vagas_na_sala);

    while(1)
    {
        //Monitor supervisionando alunos...
        printf("[Monitor %d está supervisionando os alunos]\n", id_monitor); sleep(3);

        if(rand() % 4 == 1 || aux_aln == TAM_DOS_GRUPOS * QTT_MONITORES)
        {
            sem_getvalue(&vagas_na_sala, &aux_aln);

            if(aux_aln >= TAM_DOS_GRUPOS)
            {
                sem_wait(&monitores_em_sala);	printf("[Monitor %d saiu da sala]\n", id_monitor);
                break;
            }
            else printf("[Monitor %d tentou sair, mas há muitos alunos]\n", id_monitor);
        }
    }
    //Testar se o professor já pode fechar a sala
    sem_getvalue(&monitores_em_sala, &aux_mtr);
    if(aux_mtr == 0)
	sem_post(&sala_vazia);

    pthread_exit(NULL);
}


void* Professor_Campiolo(void*)
{
    sem_init(&sala_vazia, 0, 0);	printf("[Professor Campiolo abriu a sala]\n");	sleep(3);

    // Avisar alunos...
    // Avisar monitores...

    sem_wait(&sala_vazia);			printf("[Professor Campiolo fechou a sala]\n");
    pthread_exit(NULL);
}


int main(void)
{
    pthread_t alunos[QTT_ALUNOS], monitores[QTT_MONITORES], professor;

    sem_init(&vagas_na_sala, 0, 0);
    sem_init(&monitores_em_sala, 0, 0);

    pthread_create(&professor, NULL, Professor_Campiolo, NULL);    

    for(int i = 0; i < QTT_MONITORES; i++)
    {
        pthread_create(&monitores[i], NULL, Estudantes_Monitores, &i);
    }

    for(int j = 0; j < QTT_ALUNOS; j++)
    {
        pthread_create(&(alunos[j]), NULL, Alunos_de_SO, &j);
    }

	pthread_join(professor, NULL);

    return 0;
}