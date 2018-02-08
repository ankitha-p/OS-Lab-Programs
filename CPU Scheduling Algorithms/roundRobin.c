#include<stdio.h>

struct job
{
	char jid[10];
	int at,wt,bt,tt;
}jq[10],rq[100];

int front_jq=0,rear_jq=0;
int front_rq=0,rear_rq=0;
int rt[100];


void gantt_chart(int q)
{
	int i,k,val,j=rq[0].at;
	printf("\n\nGANTT CHART\n");
	for(i=0;i<rear_rq;i++)
	{
		for(k=0;k<rt[i];k++)	printf(" ");
		printf(" ");
	}
	printf("\n");
	for(i=0;i<rear_rq;i++)
	{
		printf("%s",rq[i].jid);
		for(k=0;k<rt[i]-1;k++)
			printf(" ");
		printf(" ");
	}
	printf("\n");
	for(i=0;i<rear_rq;i++)
	{
		for(k=0;k<rt[i];k++)	printf(" ");
		printf(" ");
	}
	printf("\n");
	for(i=0;i<rear_rq;i++)
	{
		if(j<10) printf("0 %d",j);
		else printf("%d",j);
		for(k=0;k<rt[i]-1;k++)	printf(" ");
		printf(" ");
		j+=rt[i];
	}
}

void rr_scheduling(int q,int n)
{
	int clk=jq[0].at,i,j;
	int jobs=0,burst_time=0;
	do{
		for(i=front_jq;i<rear_jq;i++)
			if(clk==jq[i].at)
				rq[rear_rq++]=jq[front_jq++];
		if(burst_time<=0)
		{
			if(rq[front_rq-1].bt!=0 && front_rq!=0)
				rq[rear_rq++]=rq[front_rq-1];
			if(front_rq==rear_rq) 	burst_time=0;
			else{
				if(rq[front_rq].bt<=q)
				{
					jobs++;
					burst_time=rq[front_rq].bt;
					rt[front_rq]=burst_time;
					rq[front_rq++].bt=0;
				}
				else{
					burst_time=q;
					rq[front_rq].bt=rq[front_rq].bt-q;
					rt[front_rq]=q;
					front_rq++;
				}
			}
		}
		for(i=front_rq;i<rear_rq;i++)
			for(j=0;j<n;j++)
				if(strcmp(jq[j].jid,rq[front_rq-1].jid)!=0 && strcmp(rq[i].jid,jq[j].jid)==0)
					jq[j].wt++;
				clk++;
				burst_time--;
	}while(jobs!=n);
}

int main()
{
	float avg_wt=0,avg_tt=0;
	int n=0,i,j,q;
	FILE *fp;
	fp=fopen("roundRobinInput.txt","r");
	fscanf(fp,"%d\n",&q);
	do{
		fscanf(fp,"%s\t%d\t%d\n",jq[n].jid,&jq[n].at,&jq[n].bt);
		jq[n].wt=0;jq[n].tt=0;n++;
	}while(!feof(fp));
	fclose(fp);
	rear_jq=n;
	rr_scheduling(q,n);
	for(i=0;i<n;i++)
		jq[i].tt=jq[i].bt+jq[i].wt;
	printf("\nSCHEDULING\n");
	for(i=0;i<rear_rq;i++)
	{
		if(i==rear_rq-1)
			printf("%s",rq[i].jid);
		else	printf("%s-->",rq[i].jid);
	}
	gantt_chart(q);	
	printf("\n\nJID\tAT\tBT\tWT\tTT\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t%d\t%d\t%d\t%d\n",jq[i].jid,jq[i].at,jq[i].bt,jq[i].wt,jq[i].tt);
		avg_wt+=jq[i].wt;
		avg_tt+=jq[i].tt;
	}
	printf("Avg waiting time:: %.2f\n",avg_wt/n);
	printf("Avg turnaround time:: %.2f\n",avg_tt/n);
	return 0;
}
