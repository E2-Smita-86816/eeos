/**1. The child process send two numbers to the parent process via 
message queue. The parent process calculate the sum and return via 
same message queue. The child process print the result and exit. 
The parent process wait for completion of the child and then exit.**/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/msg.h>

typedef struct msg{
	long id;
	int d1;
	int d2;
}msg_t;

typedef struct resmsg{
	long id;
	int res;
}resmsg_t;

int main(){
	msg_t m1,m2;
	int ret,pid,s,mqid;
		mqid=msgget(0x1234,IPC_CREAT | 0600);
		if(mqid<0){
			perror("C:msgget fail");
			_exit(1);
		}
		pid=fork();
	if(pid==0){
		//msg_t m1;
		m1.id=101;
		printf("enter number1:");
		scanf("%d",&m1.d1);
		printf("enter number2:");
		scanf("%d",&m1.d2);
		ret=msgsnd(mqid, &m1, sizeof(msg_t)-sizeof(long), 0);
		if(ret<0){
			perror("C:msgsnd fail");
		}
		else{
			printf("msg sent by child\n");
		}

		resmsg_t m3;
		printf("waiting for addition of  numbers....\n");
		ret=msgrcv(mqid,&m3, sizeof(resmsg_t)-sizeof(long),102,0);
        if(ret<0){
			perror("msgrcv failed");
		}
		else{
			printf("sum is %d\n",m3.res);
			_exit(1);
		}

	}
	else{
		//msg_t m2;
		printf("waiting for 2 numbers....\n");
		ret=msgrcv(mqid,&m1, sizeof(msg_t)-sizeof(long),101,0);
        if(ret<0){
			perror("msgrcv failed");
		}
		else{
			printf("parent: recieved from child is %d,%d\n",m1.d1,m1.d2);
		

		resmsg_t m3;
		m3.id=102;
		m3.res=m1.d1+m1.d2;
		ret=msgsnd(mqid, &m3, sizeof(resmsg_t)-sizeof(long), 0);
		if(ret<0){
			perror("P:msgsnd fail");
		}
		
		waitpid(-1,&s,0);

		msgctl(mqid,IPC_RMID,0);
		}

	}
	return 0;
}
