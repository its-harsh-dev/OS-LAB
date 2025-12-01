#include <stdio.h>
int main()
{
    int n,time_quantum;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    int pid[n],arrival[n],burst[n],remaining[n],waiting[n],turnaround[n],completed[n];
    int gantt_pid[100],gantt_time[100];
    int gantt_index=0;
    for(int i = 0;i < n;i++)
    {
        pid[i] = i+1;
        printf("Enter arrival time for P%d : ",pid[i]);
        scanf("%d",&arrival[i]);
        printf("Enter burst time for P%d",pid[i]);
        scanf("%d",&burst[i]);
        remaining[i] = burst[i];
        waiting[i] = 0;
        turnaround[i] = 0;
        completed[i] = 0;
    }
    int t=0;//current time
    int done = 0;
    while(done < n)
    {
        int executed = 0;
        for(int i=0;i < n;i++)
        {
            if(remaining[i] > 0 && arrival[i] <= t)
            {
                executed = 1;
                gantt_pid[gantt_index] = pid[i];
                if(remaining[i] > time_quantum)
                {
                    gantt_time[gantt_index] = t;
                    t += time_quantum;
                    remaining[i] -= time_quantum;
                }
                else
                {
                    gantt_time[gantt_index] = t;
                    t += remaining[i];
                    remaining[i] = 0;
                    turnaround[i] = t_arrival[i];
                    waiting[i] = turnaround[i] - burst[i];
                    completed[i] = 1;
                    done++;
                }
                gantt_index++;
            }
        }
        if(!executed)t++; // If no process is ready,increment time
    
    printf("\nHorizontal Gantt Chart \n");
    for(int i = 0 ;i < gantt_index;i++)
    {
        printf("| P%d ",gantt_pid[i]);
    }
    printf("\n");
    for(int i = 0 ;i < gantt_index;i++)
    {
        printf("%d ",gantt_time[i]);
    }
    printf("%d\n",t);
    //process table
    printf("\nProcess\tArrival \t Burst \t Waiting \t Turnaround\n");
    for(int i = 0;i < n;i++)
    {
        printf("P%d\t %d \t %d \t %d \t %d\n",pid[i],arrival[i],burst[i],waiting[i],turnaround[i]);
    }
    float avg_waiting = 0,avg_turnaround = 0;
    for(int i = 0;i < n;i++)
    {
        avg_waiting += waiting[i];
        avg_turnaround += turnaround[i];
    }
    avg_waiting /= n;
    avg_turnaround /= n;
    printf("\nAverage Waiting Time : %.2f\n",avg_waiting);
    printf("\nAverage Turnaround Time : %.2f\n",avg_turnaround);
    return 0;
}