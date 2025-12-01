#include <stdio.h>
#include <stdlib.h>
int main()
{
    int frames[10],recent[10],pages[30];
    int n,m,i,j,pos,counter=0;
    int hits = 0 , miss = 0,flag1,flag2,min;
    printf("Enter number of frames : ");
    scanf("%d",&n);
    printf("Enter number of pages : ");
    scanf("%d",&m);
    printf("Enter the page reference string : \n");
    for(i = 0;i < m;i++)
    {
        scanf("%d",&pages[i]);
    }
    for(i = 0;i < m;i++)
    {
        frames[i] = -1;
        recent[i] = 0;
    }
    printf("\nPage\tframes\t\tStatus\n");
    for(i = 0;i < m;i++)
    {
        flag1 = flag2 = 0;
        for(j = 0;j < n;j++)
        {
            if(frames[j] == pages[i])
            {
                counter++;
                recent[j] = counter;
                hits++;
                flag1 = flag2 = 1;
                break;
            }
        }
        if(flag1 == 0)
        {
            for(j = 0;j < n;j++)
            {
                if(frames[j] == -1)
                {
                    counter++;
                    hits++;
                    frames[j]  = pages[i];
                    recent[j] = counter;
                    flag2 = 1;
                    break;
                }

            }
        }
        if(flag2 == 0)
        {
            min = recent[0];
            pos = 0;
            for(j = 1;j< n;j++)
            {
                if(recent[j] < min)
                {
                    min = recent[j];
                    pos = j;
                }
            }
            counter++;
            miss++;
            frames[pos] = pages[i];
            recent[pos] = counter;
        }
        printf("%d\t",pages[i]);
        for(j = 0;j < n;j++)
        {
            if(frames[j] != -1)
            {
                printf("%d",frames[j]);
            }
            else{
                printf('-');
            }
            printf("\t\t%s\n",flag1?"Hit" : "Miss");
        }
        printf("\nTotal Hits  = %d\n",hits);
        printf("\nTotal misses = %d\n",miss);
        printf("Hit ratio = %.2f\n",(float)hits/m);
        printf("Miss ratio = %.2f\n",(float)miss/m);
        return 0;
    }
}