#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


void sig_handler(int signal)
{
    if(signal == SIGINT)
    {
        printf("received SIGINT\n");
    }
}


int main()
{
    if(signal(SIGINT, sig_handler) == SIG_ERR)
    {
        printf("\ncan't catch SIGINT");
    }

    printf("My PID is %d\n", getpid());

    while(1) sleep(1);

    return 0;
}