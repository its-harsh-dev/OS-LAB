#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <stdlib.h>

int global;

int main()
{
    pid_t child_pid;
    int status;
    int local = 0;
    child_pid = fork();
    if(child_pid >= 0)
    {
        if(child_pid == 0)
        {
            printf("Child Process\n");
            local++;
            global++;
            printf("Child Pid : %d\nParent Pid : %d\n",getpid(),getppid());
            printf("Child Local : %d,Child global : %d\n",local,global);
            char* cmd[] = {"whoami",(char*)0};
            return execv("/usr/bin/whoami",cmd);
        }
        else
        {
            wait(&status);
            printf("Parent process\n");
            printf("Parent pid : %d,Child pid : %d\n",getpid(),child_pid);
            printf("Parent local : %d,Parent global :  %d\n",local,global);
            printf("Child exit code : %d\n",WEXITSTATUS(status));
        }
    }
    else
    {
        perror(fork);
        exit(0);
    }
    return 0;
}