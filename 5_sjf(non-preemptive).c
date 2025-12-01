#include <stdio.h>
#include <limits.h>
struct Process
{
    int id,at,bt,ct,tat,wt,done;
};
int main(int argc,char* argv[])
{
    int n,i,time = 0,completed = 0;
    printf("Enter no. of processes : ");
    scanf("%d",&n);
    struct Process p[n];
    float avg_tat=0,avg_wt = 0;
    for(i = 0;i < n;i++)
    {
        p[i].id = i+1;
        printf("Process %d Arrival Time : ",i+1);
        scanf("%d",&p[i].at);
        printf("Process : %d Burst Time : ",i+1);
        scanf("%d",&p[i].bt);

        p[i].done = 0;
    }
    while(completed < n)
    {
        int idx = -1,min_bt = INT_MAX;
        for(i = 0;i  < n ;i++)
        {
            if(!p[i].done &&p[i].at <= time && p[i].bt < min_bt)
            {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if(idx == -1)
        {
            time++;
            continue;
        }
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        avg_tat += p[idx].tat;
        avg_wt += p[idx].wt;
        p[idx].done = 1;
        completed++;
    }
    printf("\nSJF(Non Preemptive Scheduling)\n");
    printf("Prcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(i = 0;i < n;i++)
    {
        printf("P%d\t  %d \t %d\t %d \t %d \t %d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
    }
    printf("\nAverage Turnaround Time : %2f",avg_tat/n);
    printf("\nAverage Waiting Time : %2f",avg_wt/n);
    return 0;
}