#include<stdio.h>

struct job
{
	char jid[10];
	int at;
	int bt;
	int wt;
	int tt;
}p[10],q[10];

int front=0,rear=0;

void sorting()
{
	int i,j;
	struct job temp;
	for(i=front;i<rear;i++)
	{
		for(j=front;j<rear-1;j++)
		{
			if(q[j].bt>q[j+1].bt)
			{
				temp=q[j];
				q[j]=q[j+1];	
				q[j+1]=temp;
			}
		}

	}
}
void shortest_job_first(int n,int time)
{
	int clk=0,i,t=0;
	int j_time=0;
	clk=p[0].at;
	while(clk!=time){
		for(i=0;i<n;i++)
			if(clk==p[i].at)
				q[rear++]=p[t++];
		if(j_time==0)
		{
			sorting();
			if(front==rear)	j_time=0;
			else 		j_time=q[front++].bt;
		}
		for(i=front;i<rear;i++)	q[i].wt++;
		clk++;
		j_time--;
	}
}
int main()
{
	float avg_wt=0,avg_tt=0;
	int n=0,time=0,i,j;
	FILE *fp;
	fp=fopen("inputSJF.txt","r");
	do{
		fscanf(fp,"%s%d%d\n",p[n].jid,&p[n].at,&p[n].bt);
		p[n].wt=p[n].tt=0;
		time+=p[n].bt;
		n++;
	}
	while(!feof(fp));
	fclose(fp);
	shortest_job_first(n,time);
	for(i=0;i<n;i++)	q[i].tt=q[i].bt+q[i].wt;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(strcmp(p[i].jid,q[j].jid)==0){
				p[i]=q[j];
				break;
			}
	printf("\nSCHEDULING\n");
	for(i=0;i<n;i++)
		if(i==n-1) printf("%s",q[i].jid);
		else       printf("%s-->",q[i].jid);
	printf("\n\nGANT CHART\n");
	for(i=0;i<n;i++)   printf("____*");
	printf("\n");
	for(i=0;i<n;i++)   printf("%s    ",q[i].jid);
	printf("\n");
	for(i=0;i<n;i++)   printf("____*");
	j=p[0].at;
	printf("\n");
	for(i=0;i<n;i++){
		printf("%d   ",j);
		j+=q[i].bt;
	}
	printf("%d  ",j);
	printf("\n\nJID\tAT\tBT\tWT\tTT\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t%d\t%d\t%d\t%d\n",p[i].jid,p[i].at,p[i].bt,p[i].wt,p[i].tt);
		avg_wt+=q[i].wt;
		avg_tt+=q[i].tt;
	}
	printf("Avg waiting time: %.2f\n",avg_wt/n);
	printf("Avg turnaround time: %.2f\n",avg_tt/n);
	return 0;
}
 	
	


