#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <random>

using namespace std;

const int QTT_ALUNOS = 11;
const int QTT_MONITORES = 3;
const int TAM_DOS_GRUPOS = 3;

sem_t sala_vazia;
sem_t alunos_em_sala;
sem_t monitores_em_sala;


void* Alunos_de_SO(void* id)
{
    int aux_mtr, aux_aln;
    int id_aluno = *(int*) id;

    // Baguio de sinal aqui.......

    while(1)
    {
        // Aluno tenta entrar na sala
        sem_getvalue(&monitores_em_sala, &aux_mtr);
        sem_getvalue(&alunos_em_sala, &aux_aln);
        
        if(aux_mtr * TAM_DOS_GRUPOS > aux_aln) // <- Condição (1)
        {
            sem_post(&alunos_em_sala);
            printf("Aluno %d entrou na sala\n", id_aluno);
            
            while(1)
            {
                // Aluno estudando...
                printf("[Aluno %d está estudando]\n", id_aluno);
                sleep(rand() % 5);

                if(rand() % 3 == 1) // Tenta sair aleatóriamente
                {   
                    printf("[Aluno %d saiu da sala]\n", id_aluno);
                    break;
                }
            }
            break; // <- Assim que o aluno sair uma vez da sala ele não tenta entrar de novo
        }
        else // Espera até poder tentar de novo
        {
            sleep(rand() % 5);
        }
    }

    sem_getvalue(&alunos_em_sala, &aux_aln);
    if(aux_aln == 0)
    {
        sem_post(&sala_vazia);
    }

    pthread_exit(NULL);
}


void* Estudantes_Monitores(void* id)
{
    int aux_mtr, aux_aln;
    int id_monitor = *(int*) id;
    
    // Aqui é pra ter o sinal......

    // Monitor entrou na sala
    sem_post(&monitores_em_sala);
    printf("[Monitor %d entrou na sala]\n", id_monitor);

    sem_wait(&alunos_em_sala);
    
    while(1)
    {
        // Monitor supervisionando alunos...
        printf("[Monitor %d está supervisionando os alunos]\n", id_monitor);
        sleep(3);

        if(rand() % 4 == 1)
        {
            sem_getvalue(&monitores_em_sala, &aux_mtr);
            sem_getvalue(&alunos_em_sala, &aux_aln);
        
            if(aux_mtr * TAM_DOS_GRUPOS > aux_aln) // <- Condição (1)
            {
                printf("[Monitor %d saiu da sala]\n", id_monitor);
                sem_wait(&monitores_em_sala);
                break;
            }
            else
            {
                printf("[Monitor %d tentou sair, mas há muitos alunos]\n", id_monitor);
            }
        }
    }
    pthread_exit(NULL);
}


void* Professor_Campiolo(void*)
{
    // Abrir sala
    sem_init(&sala_vazia, 0, 0);
    printf("[Professor Campiolo abriu a sala]\n");

    // Avisar alunos

    // Avisar monitores

    // Fechar sala
    sem_wait(&sala_vazia);  
    sem_destroy(&alunos_em_sala);
    printf("[Professor Campiolo fechou a sala :C]\n");

    pthread_exit(NULL);
}


int main(void)
{
    pthread_t alunos, monitores, professor;

    sem_init(&alunos_em_sala, 0, 0);
    sem_init(&monitores_em_sala, 0, 0);

    pthread_create(&professor, NULL, Professor_Campiolo, NULL);    

    for(int i = 0; i < QTT_MONITORES; i++)
    {
        pthread_create(&monitores, NULL, Estudantes_Monitores, &i);
        sleep(1);
    }

    for(int j = 0; j < QTT_ALUNOS; j++)
    {
        pthread_create(&alunos, NULL, Alunos_de_SO, &j);
        sleep(1);
    }

    sem_wait(&sala_vazia);
    sleep(5);
    return 0;
}