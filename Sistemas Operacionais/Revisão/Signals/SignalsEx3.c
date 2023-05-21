#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void sig_handler(int signo)
{
    if(signo == SIGTERM)
    {
        printf("received SIGTERM.\n");
        printf("Eu deveria ter finalizado...");
    }

    if(signo == SIGALRM)
    {
        printf("received SIGALRM\n");
        kill(getpid(), SIGKILL);
    }
}


int main()
{
    if(signal(SIGTERM, sig_handler) == SIG_ERR) printf("\ncan't catch SIGTERM\n");
    if(signal(SIGALRM, sig_handler) == SIG_ERR) printf("\ncan't catch SIGALRM\n");

    alarm(10);
    printf("MY PID is %d\n", getpid());

    while(1) sleep(1);

    return 0;
}