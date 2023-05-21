#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


// sigset_t set;


// void sig_handler(int signo)
// {
//     printf("received a %d\n", signo);
// }


// int main(void)
// {
//     if(signal(SIGINT, sig_handler) == SIG_ERR) printf("\ncan't catch SIGINT");
//     if(signal(SIGQUIT, sig_handler) == SIG_ERR) printf("\ncan't catch SIGQUIT");
//     if(signal(SIGHUP, sig_handler) == SIG_ERR) printf("\ncan't catch SIGHUP");

//     sigemptyset(&set);

//     sigaddset(&set, SIGQUIT);
//     sigaddset(&set, SIGINT);
//     sigprocmask(SIG_SETMASK, &set, NULL);

//     printf("My PID is %d\n", getpid());

//     while(1) sleep(1);

//     return 0;
// }