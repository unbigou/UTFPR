#include <semaphore.h>
#include <pthread.h>

class Professor
{
    private:
        void abrirSala(sem_t);
        void avisarAlunos();
        void avisarEstudantesMonitores();
        void fecharSala(sem_t);
};


void Professor::abrirSala(sem_t mutex)
{
    sem_init(&mutex, 0, 1);
};


void Professor::avisarAlunos()
{
    
};


void Professor::avisarEstudantesMonitores()
{

};


void Professor::fecharSala(sem_t mutex)
{
    sem_destroy(&mutex);
};  