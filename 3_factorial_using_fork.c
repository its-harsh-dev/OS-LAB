#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <error.h>
#include <wait.h>
int main(int argc,char* argv[])
{
    int n = atoi(argv[1]);
    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        printf("Child Process of pid : %d\nFactorial of %d terms\n",getpid(),n);
        int fact = 1;
        for(int i = 1;i <= n;i++)
        {
            fact = fact*i;
            printf("%d\t",fact);
        }
        printf("\n");
    }
    else
    {
        wait(NULL);
        printf("Parent process PID : %d,Child Process finished execution\n",getpid());
    }
    return 0;
}