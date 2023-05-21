#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    pid_t pid;
    int mypipe[2];
    char buffer[40];

    if(pipe(mypipe))
    {
        fprintf(stderr, "Falha ao criar o pipe.\n");

        return EXIT_FAILURE;
    }

    pid = fork();
    if(pid < (pid_t) 0)
    {
        fprintf(stderr, "Falha ao criar o fork.\n");

        return EXIT_FAILURE;
    }
    else if(pid == (pid_t) 0)
    {
        close(mypipe[1]);
        read(mypipe[0], buffer, sizeof(buffer));
        
        printf("FILHO:...%s\n", buffer);
        fflush(stdout);

        return EXIT_SUCCESS;
    }
    else
    {
        close(mypipe[0]);
        
        printf("PAI: Digite algo para enviar: ");
        scanf("%40[^\n]", buffer);
        write(mypipe[1], buffer, sizeof(buffer));

        wait(NULL);

        return EXIT_SUCCESS;
    }
}