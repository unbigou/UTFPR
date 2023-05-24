#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <random>

sem_t sala, qtt_monitores;


void* Alunos_de_SO(void*)
{
    sem_wait(&sala);

    
    pthread_exit(NULL);
}

void* Estudantes_Monitores(void*)
{
    sem_wait(&sala);
    sem_init(&qtt_monitores, 0, 0);


    pthread_exit(NULL);
}


void* Professor_Campiolo(void*)
{
    sem_init(&sala, 0, 0);
    printf("[Professor Campiolo abriu a sala]\n");

    sem_post(&sala);
    printf("[Professor Campiolo avisou os alunos]\n");
    printf("[Professor Campiolo avisou os monitores]\n");

    sem_wait(&sala);
    int quantity = 1;
    while(quantity)
    {
        sem_getvalue(&sala, &quantity);
    }

    sem_destroy(&sala);
    printf("[Professor Campiolo fechou a sala]");

    pthread_exit(NULL);
}


int main(void)
{
    pthread_t alunos, monitores, professor;

    pthread_create(&alunos, NULL, Alunos_de_SO, NULL);
    pthread_create(&monitores, NULL, Estudantes_Monitores, NULL);
    pthread_create(&professor, NULL, Professor_Campiolo, NULL);    

    return 0;
}