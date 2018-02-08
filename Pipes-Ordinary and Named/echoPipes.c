#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

int main()
{
        int fd1[2],fd2[2],nbytesc,nbytesp;
        pid_t childpid;
       // int input=0,output=0;
       // int readinput,numb,i,temp,rem,ans=0;
//	char a,num[8],readbuffer[20];
	char input[15]="Hello World!";
	char readbufferc[20],readbufferp[20];
	
        pipe(fd1);pipe(fd2);
        if((childpid=fork())==-1){ perror("fork"); exit(1);}

        if(childpid==0)
        {
		printf("In child\n");
                
		close(fd1[0]);close(fd2[1]);
                
		write(fd1[1],input,strlen(input)+1);

		nbytesc=read(fd2[0],readbufferc,sizeof(readbufferc));
//		printf("size is %d\n",(int)strlen(readbuffer));
//		printf("%s\n",readbuffer);
		printf("\nRead from the buffer%s\n",readbufferc);
		exit(0);
        }
        else
        {
		printf("\nIn Parent\n");
		close(fd1[1]);close(fd2[0]);
		nbytesp=read(fd1[0],readbufferp,sizeof(readbufferp));
		write(fd2[1],readbufferp,strlen(readbufferp)+1);
	//	printf("Writing %s\t",num);
	//	printf("%d\t\t",(int)strlen(num));		
        }
        return 0;
}

