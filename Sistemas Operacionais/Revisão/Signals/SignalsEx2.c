#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


volatile sig_atomic_t keep_going = 1;


void catch_alarm(int sig)
{
    puts("Alarme!!!!");
    keep_going = 0;
    signal(sig, keep_going);
}


void do_stuff(void)
{
    puts("Fazendo algo...");
}


int main()
{
    signal(SIGALRM, catch_alarm);
    alarm(10);

    while(keep_going) do_stuff();
    puts("Terminou.");

    return EXIT_SUCCESS;
}