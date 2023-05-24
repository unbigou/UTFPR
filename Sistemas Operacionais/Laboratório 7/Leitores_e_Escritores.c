#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>


typedef int semaphore; /* use sua imaginacao */
semaphore mutex = 1; /* controla o acesso a ‘rc’ */
semaphore db = 1; /* controla o acesso a base de dados */
int rc = 0;


void down(semaphore* sem)
{
    (*sem)--;
}

void up(semaphore* sem)
{
    (*sem)++;
}

void reader()
{
    while(1) 
    {
        down(&mutex); /* obtem acesso exclusivo a ‘rc’ */
        rc++; /* um leitor a mais agora */
        
        if (rc == 1) down(&db); /* se este for o primeiro leitor ... */

        up(&mutex); /* libera o acesso exclusivo a ‘rc’ */
        read_data_base( ); /* acesso aos dados */
        down(&mutex); /* obtem acesso exclusivo a ‘rc’ */
        rc--; /* um leitor a menos agora */
        
        if(rc == 0) up(&db); /* se este for o ultimo leitor ... */

        up(&mutex); /* libera o acesso exclusivo a ‘rc’ */
        use_data_read( ); /* regiao nao critica */
    }
}

void writer()
{
    while (1) 
    {
        think_up_data( ); /* regiao nao critica */
        down(&db); /* obtem acesso exclusivo */
        write_data_base( ); /* atualiza os dados */
        up(&db); /* libera o acesso exclusivo */
    }
}