#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <random>

const int QTT_ALUNOS = 11;
const int QTT_MONITORES = 3;
const int TAM_DOS_GRUPOS = 3;

sem_t em_sala;
sem_t sala_vazia;


void* Alunos_de_SO(void* id)
{
    int id_aluno = *(int*) id;
    
    sem_wait(&em_sala);

    
    pthread_exit(NULL);
}

void* Estudantes_Monitores(void* id)
{
    sem_wait(&em_sala);


    pthread_exit(NULL);
}


void* Professor_Campiolo(void*)
{
    sem_init(&em_sala, 0, 1);
    sem_init(&sala_vazia, 0, 0);
    printf("[Professor Campiolo abriu a sala]\n");

    sem_wait(&sala_vazia);  
    sem_destroy(&em_sala);
    printf("[Professor Campiolo fechou a sala]");

    pthread_exit(NULL);
}


int main(void)
{
    pthread_t alunos, monitores, professor;

    pthread_create(&professor, NULL, Professor_Campiolo, NULL);    

    for(int i = 0; i < QTT_MONITORES; i++)
    {
        pthread_create(&monitores, NULL, Estudantes_Monitores, &i);
    }

    for(int j = 0; j < QTT_ALUNOS; j++)
    {
        pthread_create(&alunos, NULL, Alunos_de_SO, &j);
    }

    return 0;
}