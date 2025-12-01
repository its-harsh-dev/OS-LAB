#include <stdio.h>
int main()
{
    int n,m;
    printf("Enter number of processes : ");
    scanf("%d",&n);
    printf("Enter number of resource types : ");
    scanf("%d",&m);
    int allocation[n][m],max[n][m],need[n][m],available[m],finish[n],safeseq[n];
    printf("\nEnter allocation Matrix : \n");
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < m;j++)
        {
            scanf("%d",&allocation[i][j]);
        }
    }
    printf("\nEnter Max Matrix : \n");
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < m;j++)
        {
            scanf("%d",&max[i][j]);
        }
    }
    printf("\nEnter available array : \n");
    for(int j = 0;j < m;i++)
    {   
        scanf("%d",&available[i]);
    }
    //need matrix
    for(int i=0;i < n;i++)
    {
        for(int j = 0;j < m;j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    //initialize finish
    for(int i = 0;i < n;i++)
        finish[i] = 0;


    
    int count = 0;
    while(count<n)
    {
        int found=0;
        for(int i =0;i < n;i++)
        {
            if(finish[i] == 0)
            {
                int flag = 1;
                for(int j = 0;j < m;j++)
                {
                    if(need[i][j] > available[j])
                    {
                        flag = 0;
                        break;
                    }
                }
                if(flag)
                {
                    //allocate resources back,pretending process finished
                    for(int k = 0;k < m;k++)
                    {
                        available[k] += allocation[i][k];
                    }
                    safeseq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if(!found){
            printf("\nSystem is NOT in safe state\n");
            return 0;
        }
    }
    printf("\nSystem is in safe state\nSafe Sequence : ");
    for(int i = 0;i < n;i++)
    {
        printf("P%d",safeseq[i]);
    }
    printf("\n");
    return 0;
}
