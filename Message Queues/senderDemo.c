#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXSIZE 128

void die(char *s)
{
	perror(s);	
	exit(1);
}

struct msgbuf
{
	long mtype;
	char mtext[MAXSIZE];
};

int main()
{
	int msqid;
	int msgflg=IPC_CREAT|06666;
	key_t key;

	struct msgbuf sbuf;
	size_t buflen;
	
	key=1234;

	if((msqid=msgget(key,msgflg))<0)	die("msgget");
	sbuf.mtype=1;
	printf("Enter a message to add to msg queue");
	scanf("%[^\n]",sbuf.mtext);
	getchar();
	buflen=strlen(sbuf.mtext)+1;
	if(msgsnd(msqid,&sbuf,buflen,IPC_NOWAIT)<0)
	{	
		printf("%d,%ld,%s,%ld\n",msqid,sbuf.mtype,sbuf.mtext,buflen);
		die("msgnd");
	}
	else printf("message sent\n");
	
	exit(0);
}