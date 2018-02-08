#include<stdio.h>


struct job
{
        char jid[10];
        int bt;
        int wt;
        int tt;
}q[10];

void first_come_first_serve(int n, int time)
{
        int clk=0,i,curr_p=0;
        int j_time=q[0].bt;
        while(clk!=time)
        {
                if(j_time==0)
                {
                        curr_p++;
                        j_time=q[curr_p].bt;
                }
                for(i=curr_p+1;i<n;i++)
                        q[i].wt++;
                clk++;
                j_time--;
        }
}

int main()
{
        float avg_wt=0,avg_tt=0;
        int n=0,time=0,i;
        FILE *fp;

        fp=fopen("fcfsInput.txt","r");

        do
        {
                fscanf(fp,"%s%d\n",q[n].jid,&q[n].bt);
		q[n].wt=q[n].tt=0;
                time+=q[n].bt;
                n++;
        }
        while(!feof(fp));
        fclose(fp);
        first_come_first_serve(n,time);
        for(i=0;i<n;i++)
                q[i].tt=q[i].bt+q[i].wt;
        printf("JID\tBT\tWT\tTT\n");

        for(i=0;i<n;i++)
        {
                printf("%s\t%d\t%d\t%d\n",q[i].jid,q[i].bt,q[i].wt,q[i].tt);
                avg_wt+=q[i].wt;
                avg_tt+=q[i].tt;
        }
        printf("Average waiting time:%.2f\n",avg_wt/n);
        printf("Average turn around time:%.2f\n",avg_tt/n);

        return 0;
}

