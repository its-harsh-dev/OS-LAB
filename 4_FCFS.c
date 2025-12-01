#include <stdio.h>
struct Process
{
    int id,at,bt,ct,tat,wt;
};
int main()
{
    int n,i,j;
    printf("Enter number of processes : ");
    scanf("%d",&n);
    struct Process p[n];
    float avg_tat = 0,avg_wt = 0;

    for(i = 0;i < n;i++)
    {
        p[i].id = i+1;
        printf("Process %d Arrival Time : ",i+1);
        scanf("%d",&p[i].at);
        printf("Process %d Burst Time : ",i+1);
        scanf("%d",&p[i].bt);
    }
    //sorting of the processes according to arrival time
    for(i = 0;i < n-1;i++)
    {
        for(j = i+1;j < n;j++)
        {
            if(p[i].at > p[j].at)
            {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    //calculation of completion time
    p[0].ct = p[0].at + p[0].bt;
    for(i = 1;i < n;i++)
    {
        if(p[i].at  > p[i-1].ct)
            p[i].ct = p[i].at + p[i].bt;
        else    
            p[i].ct = p[i-1].ct + p[i].bt;
    }
    for(i = 0;i < n;i++)
    {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }
    printf("\nFCFS Scheduling : \n");
    printf("Process \t AT \t BT \t CT \t TAT \t WT \n");
    for(i = 0;i < n;i++)
    {
        printf("P%d \t %d \t %d \t %d \t %d \t %d \t",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("\nAverage Turnaround Time : %2f",avg_tat/n);
    printf("\nAverage Waiting Time : %2f",avg_wt/n);
    return 0;
}