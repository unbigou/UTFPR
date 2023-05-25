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

sem_t avisar_alunos;
sem_t avisar_monitores;


void* Alunos_de_SO(void* id)
{
    int aux_mtr, aux_aln;
    int id_aluno = *(int*) id;

    sem_wait(&avisar_alunos);

    while(1)
    {
        // Aluno tenta entrar na sala
        sem_getvalue(&monitores_em_sala, &aux_mtr);
        sem_getvalue(&alunos_em_sala, &aux_aln);
        if(aux_mtr * TAM_DOS_GRUPOS > aux_aln)
        {
            sem_post(&alunos_em_sala);
            cout << "[Aluno " << id_aluno << " entrou na sala]" << endl;
            
            while(1)
            {
                // Aluno estudando
                cout << "[Aluno " << id_aluno << " está estudando]" << endl;
                sleep(5);

                if(rand() % 5 == 1) // Tenta sair aleatóriamente
                {   
                    cout << "[Aluno " << id_aluno << " saiu da sala]" << endl;
                    break;
                }
            }
            break;
        }
        else // Espera até poder tentar de novo
        {
            sleep(3);
        }
    }
    
    pthread_exit(NULL);
}

void* Estudantes_Monitores(void* id)
{
    int id_monitor = *(int*) id;
    sem_wait(&avisar_monitores);


    pthread_exit(NULL);
}


void* Professor_Campiolo(void*)
{
    // Abrir sala
    sem_init(&sala_vazia, 0, 0);
    cout << "[Professor abriu a sala]" << endl;

    // Avisar alunos
    sem_init(&avisar_alunos, 0, 1);
    cout << "[Professor avisou os alunos]" << endl;
    
    // Avisar monitores
    sem_init(&avisar_monitores, 0, 1);
    cout << "[Professor avisou os monitores]" << endl;

    // Fechar sala
    sem_wait(&sala_vazia);  
    sem_destroy(&alunos_em_sala);
    cout << "[Professor fechou a sala]" << endl;

    pthread_exit(NULL);
}


int main(void)
{
    pthread_t alunos, monitores, professor;

    sem_init(&alunos_em_sala, 0, 0);
    sem_init(&monitores_em_sala, 0, QTT_MONITORES);

    for(int i = 0; i < QTT_MONITORES; i++)
    {
        pthread_create(&monitores, NULL, Estudantes_Monitores, &i);
    }

    for(int j = 0; j < QTT_ALUNOS; j++)
    {
        pthread_create(&alunos, NULL, Alunos_de_SO, &j);
    }

    pthread_create(&professor, NULL, Professor_Campiolo, NULL);    

    return 0;
}